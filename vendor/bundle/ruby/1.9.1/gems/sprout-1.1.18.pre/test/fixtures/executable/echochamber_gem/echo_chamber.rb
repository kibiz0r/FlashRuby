
Sprout::Specification.new do |s|
  s.name = 'echo_chamber'
  s.version = '1.0.pre'

  s.add_file_target do |t|
    t.add_executable :echos, 'bin/echochamber'
  end
end

