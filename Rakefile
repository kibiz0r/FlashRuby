require 'bundler'
require 'bundler/setup'
require 'flashsdk'

HOST = 'i386-apple-darwin11.3'

namespace :rubinius do
  desc 'Set up Rubinius to be built'
  task :configure do
    cd 'rubinius' do
      sh "BUILD_HOST='#{HOST}' CFLAGS='-m32' CPPFLAGS='-m32' LDFLAGS='-m32' ./configure --enable-version 19"
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

  desc 'Build Rubinius'
  task :build do
    cd 'rubinius' do
      sh 'rake lib:static'
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
        llvm_config_flags = "--build=#{HOST} --host=#{HOST} " \
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
