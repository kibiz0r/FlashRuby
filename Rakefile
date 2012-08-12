require 'bundler'
require 'bundler/setup'
require 'flashsdk'

host = 'i386-apple-darwin11.3'
configuration = 'debug'

flex4zip = 'flex4.zip'
air3incomplete = 'air3incomplete'
air3tbz2 = 'air3.tbz2'

air3 = 'air3'
air3runtime = "#{air3}/runtimes/air/mac"
air3framework = "#{air3}/runtimes/air/mac/Adobe AIR.framework"

adl = "#{air3}/bin/adl"
adt = "#{air3}/bin/adt"
mxmlc = "#{air3}/bin/mxmlc"
compc = "#{air3}/bin/compc"

extdir = "lib/#{configuration}"
ane = "#{extdir}/FlashRuby.ane"

unpacked_extdir = "#{extdir}/unpacked"
ane_dir = "#{unpacked_extdir}/FlashRuby.ane"

native = 'FlashRubyOSX'
native_source = FileList["#{native}/FlashRuby/**/*"].to_a

flashruby = 'FlashRuby'
flashruby_source = FileList["#{flashruby}/src/**/*.as"].to_a
flashruby_xml = "#{flashruby}/xml/extension.xml"
flashruby_swc = "#{flashruby}/bin/#{configuration}/FlashRuby.swc"
flashruby_config = 'FlashRuby/src/FlashRuby-app.config'

framework_name = 'FlashRuby.framework'
framework = "lib/#{configuration}/#{framework_name}"
framework_binary = "#{framework}/FlashRuby"

rubinius = 'rubinius'
rubinius_config = "#{rubinius}/config.rb"
librubinius = "#{rubinius}/bin/librubinius.dylib"

fruby = "fruby/bin/#{configuration}/fruby.swf"

firb_bin = "firb/bin/#{configuration}"
firb = "#{firb_bin}/firb.swf"
firb_app = "#{firb_bin}/firb-app.xml"
firb_config = 'firb/src/firb-app.config'
firb_source = FileList["firb/src/**/*.as"].to_a
firb_main = "firb/src/firb.as"




file air3framework do
  sh "wget http://download.macromedia.com/pub/flex/sdk/flex_sdk_4.6.zip -O #{flex4zip}"
  sh "unzip #{flex4zip} -d #{air3incomplete}"
  sh "wget http://airdownload.adobe.com/air/mac/download/latest/AdobeAIRSDK.tbz2 -O #{air3tbz2}"
  cd air3incomplete do
    sh "tar -jxvf ../#{air3tbz2}"
  end
  mv air3incomplete, air3, force: true
  rm flex4zip, air3tbz2
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
    sh 'rake lib:shared --trace'
  end
end

file framework_binary => librubinius do
  cd native do
    sh "xcodebuild -configuration #{configuration}"
  end
end

file flashruby_swc => [*flashruby_source, compc] do
  sh "#{compc} +configname=air -load-config+=#{flashruby_config} -debug=#{configuration == 'debug'} -output #{flashruby_swc}"
end

file ane => [adt, flashruby_swc, framework_binary] do
  Dir.mktmpdir do |tmpdir|
    sh "unzip -uo #{flashruby_swc} library.swf -d #{tmpdir}"
    cp_r framework, "#{tmpdir}/."
    old_path = Dir.pwd
    cd tmpdir do
      sh "#{File.join old_path, adt} -package -target ane #{File.join old_path, ane} #{File.join old_path, flashruby_xml} -swc #{File.join old_path, flashruby_swc} -platform MacOS-x86 library.swf #{framework_name}"
    end
  end
end

file ane_dir => ane do
  rm_rf ane_dir
  mkdir_p ane_dir
  sh "unzip #{ane} -d #{ane_dir}"
end

file fruby => ane do
end

file firb => [:wipe, mxmlc, *firb_source, ane] do
  sh "#{mxmlc} +configname=air -load-config+=#{firb_config} -debug=#{configuration == 'debug'} -output #{firb} -- #{firb_main}"
end

desc 'Start up a FlashRuby console'
task :console => [firb, ane_dir] do
  sh "#{adl} -runtime #{air3runtime} -profile extendedDesktop -extdir #{unpacked_extdir} #{firb_app} #{firb_bin}"
end

task :wipe do
  rm_rf "#{Dir.home}/.rbx"
end

task :default => :console

task :fixfb do
  sh "fixfb"
end

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
