# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "flashsdk"
  s.version = "1.1.36.pre"

  s.required_rubygems_version = Gem::Requirement.new("> 1.3.1") if s.respond_to? :required_rubygems_version=
  s.authors = ["Luke Bayes"]
  s.date = "2012-03-11"
  s.description = "The Flash SDK Rubygem is brought to you by Project Sprouts (http://projectsprouts.org)"
  s.email = "projectsprouts@googlegroups.com"
  s.executables = ["sprout-as3", "sprout-flex", "flashplayer", "flashlog"]
  s.files = ["bin/sprout-as3", "bin/sprout-flex", "bin/flashplayer", "bin/flashlog"]
  s.homepage = "http://www.adobe.com/products/flex"
  s.post_install_message = "++++++++++++++++++++++++++++++++\nYou have successfully installed the Project Sprouts Flash SDK!\n\nTo get started with a new ActionScript 3 project:\n\n  # Generate a project named 'SomeProject'\n  sprout-as3 SomeProject\n\n  # Change directory to the newly-created directory:\n  cd SomeProject\n\n  # Install whatever additional gems are required \n  # by this project Gemfile:\n  bundle install\n\n  # Use Rake to run the default task:\n  rake\n\n++++++++++++++++++++++++++++++++\nNext Steps:\n\n  # Generate a new class, test case and test suite:\n  sprout-class utils.MathUtil\n\n  # Compile and run the test harness:\n  rake test\n\n  # List available rake tasks:\n  rake -T\n\n  # List available generators:\n  sprout-\n  (followed by the TAB key)\n\n++++++++++++++++++++++++++++++++\nTo use FCSH, simply start the service,\nand call the fcsh task before any other\nmxmlc or compc task:\n\n  # Open a new terminal and from your project:\n  rake fcsh:start\n\n  # Open a new terminal and from your project:\n  rake fcsh test\n\n++++++++++++++++++++++++++++++++\nTo use FDB, simply call the fdb task\nbefore any flashplayer task:\n\n  # Run the default task with FDB:\n  rake fdb test\n\n  (type, 'help' for more info when prompted)\n\n++++++++++++++++++++++++++++++++\nYou can also launch any SWF file using\na debug Flash Player with:\n\n  flashplayer bin/SomeProject.swf\n\nOr run a SWF with FDB like:\n\n  flashplayer --fdb bin/SomeProject.swf\n\n++++++++++++++++++++++++++++++++\nYou can also tail your system's flashlog\nwhile running a SWF or HTML page with:\n\n  flashlog\n\n++++++++++++++++++++++++++++++++\nIssues or Questions? \n\n  Troubleshooting at:\n  http://projectsprouts.org/troubleshooting.html\n\n  Email us at:\n  projectsprouts@googlegroups.com\n\n"
  s.require_paths = ["lib", "lib"]
  s.rubygems_version = "1.8.15"
  s.summary = "Adobe Flash SDK including mxmlc, compc, asdoc, adl, adt, optimizer and fdb"

  if s.respond_to? :specification_version then
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<sprout>, [">= 1.1.18.pre"])
      s.add_development_dependency(%q<shoulda>, [">= 0"])
      s.add_development_dependency(%q<mocha>, [">= 0"])
    else
      s.add_dependency(%q<sprout>, [">= 1.1.18.pre"])
      s.add_dependency(%q<shoulda>, [">= 0"])
      s.add_dependency(%q<mocha>, [">= 0"])
    end
  else
    s.add_dependency(%q<sprout>, [">= 1.1.18.pre"])
    s.add_dependency(%q<shoulda>, [">= 0"])
    s.add_dependency(%q<mocha>, [">= 0"])
  end
end
