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
  sh "unzip FlashRubyCore/bin/FlashRubyCore.swc library.swf"
end

desc "builds the ANE file"
task :ane do
  sh "air3beta/bin/adt -package -target ane FlashRuby.ane FlashRuby-extension.xml -swc FlashRubyCore/bin/FlashRubyCore.swc -platform MacOS-x86 library.swf FlashRuby.framework"
end
