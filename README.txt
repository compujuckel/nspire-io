+----------------------+
|    Nspire I/O 3.1    |
+----------------------+


Installation
------------
Nspire: Just copy the "lib" and "include" directories over
to your .ndless directory located at the userpath, for example
C:\Users\Name\.ndless or /home/name/.ndless
Prizm: Make sure you set the FXCGSDK environment variable, for example
export FXCGSDK=/home/name/PrizmSDK

Building the code
-----------------
make lib             - Compiles Nspire I/O
make demo            - Compiles demos (Install first!)
make install         - Install Nspire I/O
make uninstall       - Uninstall Nspire I/O
make clean           - Deletes binaries
make ARCH=prizm lib  - Compiles Nspire I/O for Prizm

Usage
-----
Add "-lnspireio" to LDFLAGS in your Makefile and include
<nspireio.h> in your code.

Demos
-----
adv	            - Implements a small CLI where you can test
                  several features of Nspire I/O.
compatibility   - Hello World with Nspire I/O 2.0 Syntax
                  (interesting for developers).
hello           - Hello World
replace-stdio   - Hello World with stdio syntax (interesting for
                  developers).
splitscreen	    - Old Nspire I/O demo. Enter text in 1st console
                  and it will be printed to 2nd console.
tests           - Tests almost all functions of Nspire I/O.

Migrate from 2.0 to 3.x
-----------------------
For the lazy people:
Change "-lnspireio2" in you Makefile to "-lnspireio".
Programs that include nspireio2.h will compile in compatibility
mode (old syntax).

To use the new syntax, include nspireio.h instead of nspireio2.h 
and replace the function calls with their new names.

Nspire I/O is not compatible to versions < 2.0.

Documentation
-------------
An auto-generated documentation can be found in the "doc/html"
directory, just open "index.html" (if something is unclear,
please contact me and I will try to help you ;)
The code of the demo application can be found in "src/demo".

Contact
-------
Julian Mackeben (compu)
E-Mail: compujuckel@googlemail.com
Discussion topic: http://www.omnimaga.org/index.php?topic=6871.0
