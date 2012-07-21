namespace :ruby do
  task :autoconf do
    cd "ruby" do
      sh "autoconf"
    end
  end

  task :configure do
    cd "ruby" do
      sh "./configure --with-gcc=gcc-4.2 --with-arch=i386"
    end
  end

  task :make do
    cd "ruby" do
      sh "make"
    end
  end
end

task :ruby => ["ruby:autoconf", "ruby:configure", "ruby:make"]

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
task :ane => [:library_swf] do
  sh "AdobeAIRSDK/bin/adt -package -target ane FlashRuby.ane FlashRuby/src/extension.xml -swc FlashRuby/bin-debug/FlashRuby.swc -platform MacOS-x86 library.swf FlashRuby.framework"
end

task :default => [:framework, :ane]
