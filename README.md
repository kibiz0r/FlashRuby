# FlashRuby

FlashRuby is a Ruby 1.9 environment for Flash Player and AIR. Use Ruby and all of your favorite gems (with native extensions on AIR), mix and match AS3, and deploy anywhere since it compiles down to ActionScript Bytecode.

## Download

No releases yet, not even an early exclusive closed prealpha test build? :(

### RVM
Once there's a release here, this needs to work as soon as possible:
    rvm use flashruby-0.0.1.pre

## Development

### Setup

1. `clone` it
1. `cd` it
1. `./configure` it
1. `rake` it

#### Known gotchas

##### Error: No developer directory found at /Developer. Run /usr/bin/xcode-select to update the developer directory path.

See [this StackOverflow post](http://stackoverflow.com/questions/9621706/how-can-i-resolve-error-no-developer-directory-found-at-developer)

#### Installing 32-bit Ruby

run:
  rvm_archflags="-arch i386" CFLAGS="-arch i386" LDFLAGS="-arch i386" rvm install 1.9.3-p194 --patch osx-arch-fix

### TODO

* Figure out how to influence mkmf-generated CFLAGS during Rubinius bootstrap so syck, psych, and json/parser build with -m32
