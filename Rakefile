require 'bundler'
require 'bundler/setup'
require 'flashsdk'

host = 'i386-apple-darwin11.3'
configuration = 'debug'

flex4zip = 'flex4.zip'
flex4 = 'flex4'

air3tbz2 = 'air3.tbz2'
air3 = 'air3'
air3framework = "#{air3}/runtimes/air/mac/Adobe AIR.framework"

adt = "#{air3}/bin/adt"
mxmlc = "#{air3}/bin/mxmlc"

ane = "lib/#{configuration}/FlashRuby.ane"
extension_xml = 'FlashRuby/xml/extension.xml'
swc = "FlashRuby/bin-#{configuration}/FlashRuby.swc"

native = 'FlashRubyOSX'
framework_name = 'FlashRuby.framework'
framework = "lib/#{configuration}/#{framework_name}"
framework_binary = "#{framework}/FlashRuby"

rubinius = 'rubinius'
rubinius_config = "#{rubinius}/config.rb"
librubinius = "#{rubinius}/bin/librubinius.dylib"

bin = 'bin'
fruby = "#{bin}/#{configuration}/fruby.swf"
firb = "#{bin}/#{configuration}/firb.swf"
firb_src = 'firb/src'




file flex4zip do
  sh "wget http://download.macromedia.com/pub/flex/sdk/flex_sdk_4.6.zip -O #{flex4zip}"
end

file flex4 => flex4zip do
  sh "unzip #{flex4zip} -d #{flex4}"
end

file air3tbz2 do
  sh "wget http://airdownload.adobe.com/air/mac/download/latest/AdobeAIRSDK.tbz2 -O #{air3tbz2}"
end

file air3framework => [flex4, air3tbz2] do
  mv flex4, air3, force: true
  cd air3 do
    sh "tar -jxvf ../#{air3tbz2}"
  end
end

file adt => air3framework
file mxmlc => air3framework

file rubinius_config do
  cd rubinius do
    sh "BUILD_HOST='#{host}' CFLAGS='-m32' CPPFLAGS='-m32' LDFLAGS='-m32' ./configure --enable-version 19"
  end
end

file librubinius => rubinius_config do
  cd rubinius do
    cd 'vendor/libffi' do
      sh 'CFLAGS="-m32" CPPFLAGS="-m32" LDFLAGS="-m32" ./configure --disable-builddir --enable-portable-binary'
    end
    cd 'vendor/libtommath' do
      sh 'CFLAGS="-m32" CPPFLAGS="-m32" LDFLAGS="-m32" make'
    end
    cd 'vendor/libgdtoa' do
      sh 'CFLAGS="-m32" CPPFLAGS="-m32" LDFLAGS="-m32" make'
    end
    cd 'vendor/udis86' do
      sh 'CFLAGS="-m32" CPPFLAGS="-m32" LDFLAGS="-m32" ./configure'
    end
    sh 'rake lib:shared'
  end
end

file framework_binary => librubinius do
  cd native do
    sh "xcodebuild -configuration #{configuration}"
  end
end

file ane => [adt, framework] do
  Dir.mktmpdir do |tmpdir|
    sh "unzip -uo #{swc} library.swf -d #{tmpdir}"
    cp_r framework, "#{tmpdir}/."
    old_path = Dir.pwd
    cd tmpdir do
      sh "#{File.join old_path, adt} -package -target ane #{File.join old_path, ane} #{File.join old_path, extension_xml} -swc #{File.join old_path, swc} -platform MacOS-x86 library.swf #{framework_name}"
    end
  end
end

file fruby => ane do
end

file firb => ane do
  "#{mxmlc} -load-config+=firb/src/firb-app.xml -debug=#{configuration == 'debug'}"
end

desc 'Start up a FlashRuby console'
task :console => firb do
  sh firb
end

task :default => :console

namespace :rubinius do
  desc 'Set up Rubinius to be built'
  task :configure do
    cd 'rubinius' do
      sh "BUILD_HOST='#{host}' CFLAGS='-m32' CPPFLAGS='-m32' LDFLAGS='-m32' ./configure --enable-version 19"
      cd 'vendor/libffi' do
        sh 'CFLAGS="-m32" CPPFLAGS="-m32" LDFLAGS="-m32" ./configure --disable-builddir --enable-portable-binary'
      end
      cd 'vendor/libtommath' do
        sh 'CFLAGS="-m32" CPPFLAGS="-m32" LDFLAGS="-m32" make'
      end
      cd 'vendor/libgdtoa' do
        sh 'CFLAGS="-m32" CPPFLAGS="-m32" LDFLAGS="-m32" make'
      end
      cd 'vendor/udis86' do
        sh 'CFLAGS="-m32" CPPFLAGS="-m32" LDFLAGS="-m32" ./configure'
      end
    end
  end

  namespace :build do
    namespace :only do
      task :shared do
        cd 'rubinius' do
          sh 'rake lib:only:shared'
        end
      end

      task :static do
        cd 'rubinius' do
          sh 'rake lib:only:static'
        end
      end
    end
  end

  desc 'Build Rubinius'
  task :build do
    cd 'rubinius' do
      sh 'rake lib:only:static'
    end
  end

  desc 'Clean intermediate Rubinius files'
  task :clean do
    cd 'rubinius' do
      sh 'rake vm:clean'
    end
  end

  namespace :llvm do
    desc 'Clean intermediate LLVM files'
    task :clean do
      cd 'rubinius/vendor/llvm' do
        sh 'make clean'
      end
    end

    desc 'Build LLVM'
    task :build do
      cd 'rubinius/vendor/llvm' do
        ENV["REQUIRES_RTTI"] = "1"
        ENV["REQUIRES_EH"] = "1"
        llvm_config_flags = "--build=#{host} --host=#{host} " \
                            "--enable-optimized --disable-assertions "\
                            " --enable-targets=host,cpp"
        sh "./configure #{llvm_config_flags}"
        sh 'make'
      end
    end
  end
end

desc "Extract library.swf from FlashRubyCore.swc"
task :library_swf do
  sh "unzip -uo FlashRuby/bin-debug/FlashRuby.swc library.swf"
end

desc "Copy framework file to work directory"
task :framework do
  framework = Dir["#{Dir.home}/Library/Developer/Xcode/DerivedData/FlashRuby-*/Build/Products/Debug/FlashRuby.framework"].max_by do |file|
    File.new(file).mtime
  end
  sh "rm -rf FlashRuby.framework"
  sh "cp -r '#{framework}' FlashRuby.framework"
end

desc "Build the ANE file"
task :ane => [:library_swf] do
  sh "AdobeAIRSDK/bin/adt -package -target ane FlashRuby.ane FlashRuby/xml/extension.xml -swc FlashRuby/bin-debug/FlashRuby.swc -platform MacOS-x86 library.swf FlashRuby.framework"
end

task :default => [:framework, :ane]

mxmlc 'FlashRubyHost/bin-debug/FlashRubyHost.swf' do |t|
  t.input = 'src/FlashRubyHost.as'
end

flashplayer :test => 'FlashRubyHost/bin-debug/FlashRubyHost.swf'
