# Installing 32-bit Ruby

run:
  rvm_archflags="-arch i386" CFLAGS="-arch i386" LDFLAGS="-arch i386" rvm install 1.9.3-p194 --patch osx-arch-fix

# TODO

* Figure out how to influence mkmf-generated CFLAGS during Rubinius bootstrap so syck, psych, and json/parser build with -m32
