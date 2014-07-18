#------------------------------------------------------------------------------
# Bundler Setup
#------------------------------------------------------------------------------
require "bundler"
begin
  Bundler.setup(:default, :development)
rescue Bundler::BundlerError => e
  raise LoadError.new("Unable to Bundler.setup(): You probably need to run `bundle install`: #{e.message}")
end
require 'rscons'
require 'rbconfig'

#------------------------------------------------------------------------------
# Envrionment Definitions
#------------------------------------------------------------------------------
# Detect the windows platform and provide a task to force posix
is_windows = (Object.const_get('RUBY_PLATFORM') =~ /mswin|mingw|cygwin/)
task(:posix){ is_windows = false }

# Define the compiler environment
Env = Rscons::Environment.new do |env|
  #env["CFLAGS"] += ['-Wall', '-Werror']
  env['CXXSUFFIX'] = '.cpp'
end

# Define the test environment
TestEnv = Env.clone  do |env|
  env['CPPPATH'] += Dir['tools/UnitTest++/src/', 'source/**/']
end

# Make sure the environment is processed before we quit
at_exit { Env.process; TestEnv.process}

#------------------------------------------------------------------------------
# Main Build Targets
#------------------------------------------------------------------------------
task :default => [:test, :build]

desc "Build the OPTS static library"
task :build do
    Env.Library('build/libcds.a', Dir['source/**.{c,cpp}'])
end

#------------------------------------------------------------------------------
# Unit Testing Targets
#------------------------------------------------------------------------------
desc "Run all unit tests"
task :test => [:unittest_pp] do
    TestEnv.Program('build/test_libcds',
                    Dir[ 'source/**/*.{c,cpp}', 'tests/**/*.{c,cpp}', 'build/libUnitTest++.a' ])
    TestEnv.process
    sh "build/test_libcds"
end

task :unittest_pp do
  TestEnv.Library('build/UnitTest++.a', Dir[
    'tools/UnitTest++/src/*.{c,cpp}',
    "tools/UnitTest++/src/#{(is_windows ? 'Win32' : 'Posix')}/*.{c,cpp}"
  ])
end

#------------------------------------------------------------------------------
# Cleanup Target
#------------------------------------------------------------------------------
desc "Clean all generated files and directories"
task(:clean) { Rscons.clean }

