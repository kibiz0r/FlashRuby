require 'bundler'
require 'bundler/setup'

require 'flashsdk'

desc "extracts library.swf from FlashRubyCore.swc"
task :library_swf do
  sh "unzip -uo FlashRuby/bin-debug/FlashRuby.swc library.swf"
end

desc "copies framework file to work directory"
task :framework do
  framework = Dir["#{Dir.home}/Library/Developer/Xcode/DerivedData/FlashRuby-*/Build/Products/Debug/FlashRuby.framework"].max_by do |file|
    File.new(file).mtime
  end
  sh "rm -rf FlashRuby.framework"
  sh "cp -r '#{framework}' FlashRuby.framework"
end

desc "builds the ANE file"
task ane: [:library_swf] do
  sh "AdobeAIRSDK/bin/adt -package -target ane FlashRuby.ane FlashRuby/xml/extension.xml -swc FlashRuby/bin-debug/FlashRuby.swc -platform MacOS-x86 library.swf FlashRuby.framework"
end

task default: [:framework, :ane]

mxmlc 'FlashRubyHost/bin-debug/FlashRubyHost.swf' do |t|
  t.input = 'src/FlashRubyHost.as'
end

flashplayer test: 'FlashRubyHost/bin-debug/FlashRubyHost.swf'
