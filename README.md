**This version of Nspire I/O is not maintained anymore. Please use the fork at https://github.com/Vogtinator/nspire-io/**

Nspire I/O 3.1
==============

Installation
------------
**Nspire**  
Just copy the "lib" and "include" directories over to your .ndless directory located at the userpath, for example `C:\Users\Name\.ndless` or `/home/name/.ndless`  
**Prizm**  
Make sure you set the FXCGSDK environment variable, for example `export FXCGSDK=/home/name/PrizmSDK`  

Building the code
-----------------
* `make all` - compiles Nspire I/O with demos
* `make lib` - compiles Nspire I/O
* `make demo` - compiles demos
* `make install` - install Nspire I/O
* `make uninstall` - uninstall Nspire I/O
* `make clean` - deletes binaries
* `make ARCH=prizm lib` - compiles Nspire I/O for Prizm (probably broken or unstable)

Usage
-----
Add `-lnspireio` to LDFLAGS in your Makefile and include `nspireio/nspireio.h` (for C programs) or `nspireio/console.hpp`/`nspireio/uart.hpp` (for C++ programs) in your code.

Demos
-----
* adv - Implements a small CLI where you can test several features of Nspire I/O.
* compatibility - Hello World with Nspire I/O 2.0 Syntax.
* hello - Hello World
* replace-stdio - Hello World with stdio syntax.
* splitscreen - Old Nspire I/O demo. Enter text in 1st console and it will be printed to 2nd console.
* tests - Tests almost all functions of Nspire I/O.
* cplusplus - Perform several tests in C++.

Migrate from 2.0 to 3.x
-----------------------
For the lazy people:  
Change `-lnspireio2` in you Makefile to `-lnspireio`.  
Programs that include nspireio2.h will compile in compatibility mode (old syntax).

To use the new syntax, include `nspireio/nspireio.h` instead of `nspireio2.h` and replace the function calls with their new names.

Nspire I/O is not compatible to versions < 2.0.

Documentation
-------------
An auto-generated documentation can be found in the "doc/html" directory, just open "index.html" (if something is unclear, please contact me and I will try to help you ;)  
The code of the demo application can be found in "src/demo".

Contact
-------
Julian Mackeben (compu) (for Nspire-related things)  
E-Mail: <compujuckel@googlemail.com>

Julien Savard (Juju) (for Prizm-related things)  
E-Mail: <juju2143@gmail.com>

Discussion board: [Omnimaga](http://www.omnimaga.org/index.php?board=209.0)  
Homepage: [nspforge](http://nspforge.unsads.com/p/nspireio)
