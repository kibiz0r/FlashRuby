desc "prints notes about AIR 3.0 Beta setup"
task :air3beta do
  steps = <<-END
  go to Flash Builder prefs -> Flash Builder
  Installed Flex SDKs -> Add...
  location: #{Dir.pwd}/air3beta
  name: Air 3.0 Beta
  Debug -> Standalone Flash Player: #{Dir.pwd}/air3beta/bin/adl
  END
  steps.each_line do |line|
    puts line
  end
end

desc "extracts library.swf from FlashRubyCore.swc"
task :library_swf do
  sh "unzip -uo FlashRuby/bin-debug/FlashRuby.swc library.swf"
end

desc "copies framework file to work directory"
task :framework do
  framework = Dir["#{Dir.home}/Library/Developer/Xcode/DerivedData/FlashRuby-*/Build/Products/Debug/FlashRuby.framework"].max_by do |file|
    File.new(file).mtime
  end
  p framework
  sh "rm -rf FlashRuby.framework"
  sh "cp -r '#{framework}' FlashRuby.framework"
end

desc "builds the ANE file"
task :ane => [:library_swf] do
  sh "air3beta/bin/adt -package -target ane FlashRuby.ane FlashRuby/src/extension.xml -swc FlashRuby/bin-debug/FlashRuby.swc -platform MacOS-x86 library.swf FlashRuby.framework"
end

task :default => [:framework, :ane]
