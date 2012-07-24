# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "sprout"
  s.version = "1.1.18.pre"

  s.required_rubygems_version = Gem::Requirement.new(">= 1.3.6") if s.respond_to? :required_rubygems_version=
  s.authors = ["Luke Bayes"]
  s.date = "2012-03-11"
  s.description = "Project Sprouts gives you access to beautiful generators and easily customized templates, automated build scripts, distributed libraries and simple system configuration"
  s.email = "projectsprouts@googlegroups.com"
  s.executables = ["sprout", "sprout-generator", "sprout-class", "sprout-test", "sprout-suite", "sprout-ruby"]
  s.files = ["bin/sprout", "bin/sprout-generator", "bin/sprout-class", "bin/sprout-test", "bin/sprout-suite", "bin/sprout-ruby"]
  s.homepage = "http://projectsprouts.org"
  s.require_paths = [["lib"]]
  s.rubyforge_project = "sprout"
  s.rubygems_version = "1.8.15"
  s.summary = "Software development - evolved"

  if s.respond_to? :specification_version then
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<bundler>, [">= 0.9.19"])
      s.add_runtime_dependency(%q<rake>, [">= 0.9.2"])
      s.add_runtime_dependency(%q<rubyzip>, ["= 0.9.4"])
      s.add_runtime_dependency(%q<archive-tar-minitar>, ["= 0.5.2"])
      s.add_runtime_dependency(%q<open4>, [">= 0.9.6"])
      s.add_development_dependency(%q<yard>, [">= 0"])
      s.add_development_dependency(%q<shoulda>, [">= 0"])
      s.add_development_dependency(%q<mocha>, [">= 0"])
      s.add_development_dependency(%q<flay>, [">= 0"])
      s.add_development_dependency(%q<flog>, [">= 0"])
      s.add_development_dependency(%q<heckle>, [">= 0"])
    else
      s.add_dependency(%q<bundler>, [">= 0.9.19"])
      s.add_dependency(%q<rake>, [">= 0.9.2"])
      s.add_dependency(%q<rubyzip>, ["= 0.9.4"])
      s.add_dependency(%q<archive-tar-minitar>, ["= 0.5.2"])
      s.add_dependency(%q<open4>, [">= 0.9.6"])
      s.add_dependency(%q<yard>, [">= 0"])
      s.add_dependency(%q<shoulda>, [">= 0"])
      s.add_dependency(%q<mocha>, [">= 0"])
      s.add_dependency(%q<flay>, [">= 0"])
      s.add_dependency(%q<flog>, [">= 0"])
      s.add_dependency(%q<heckle>, [">= 0"])
    end
  else
    s.add_dependency(%q<bundler>, [">= 0.9.19"])
    s.add_dependency(%q<rake>, [">= 0.9.2"])
    s.add_dependency(%q<rubyzip>, ["= 0.9.4"])
    s.add_dependency(%q<archive-tar-minitar>, ["= 0.5.2"])
    s.add_dependency(%q<open4>, [">= 0.9.6"])
    s.add_dependency(%q<yard>, [">= 0"])
    s.add_dependency(%q<shoulda>, [">= 0"])
    s.add_dependency(%q<mocha>, [">= 0"])
    s.add_dependency(%q<flay>, [">= 0"])
    s.add_dependency(%q<flog>, [">= 0"])
    s.add_dependency(%q<heckle>, [">= 0"])
  end
end
