Particles
==================

This is an amusing little program that lets you play with some particles. I
created this in high school and have left the code unchanged.

Among some small things that I did modify from the original code... I moved
some constants to the top of the ``main.c`` file that you can change to alter
the behavior of the program slightly.

Building
-------------------

To build, run ``build.sh`` from the top level directory of the repo (or
in other terms, the directory that contains ``build.sh``). The command the
build script runs is simply ``gcc `find . -name "*.c"` -lSDL``, so you can run
that directly if you prefer.

You need to make sure SDL 1.x is installed on your system along with the
necessary development headers.

License
-------------------

I dedicate this code to the public domain. Specific terms are described in the
`Unlicense <http://unlicense.org/>`_.
