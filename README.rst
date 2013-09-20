Particles
==================

This is an amusing little program that lets you play with some particles. I
created this in high school and have left the code unchanged for the most part
so please don't judge me too hard for the mistakes of my past. This code isn't
exactly wonderful, but the result is pretty amazing.

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
necessary development headers. On Fedora, you can run
``yum install SDL SDL-devel`` to get everything. If you are on a different
Linux distribution you can just search your package index for SDL and you
should find the necessary packages (``yum search SDL`` or
``aptitude search SDL``).

If you are on Windows or Mac you may have a tougher time getting SDL on your
computer. If you'd like assistance with it feel free to email me at
jsull003@ucr.edu, though be warned that I don't often do C development on
either of those platforms and will be trying to figure it out alongside you.

License
-------------------

I dedicate this code to the public domain. Specific terms are described in the
`Unlicense <http://unlicense.org/>`_.
