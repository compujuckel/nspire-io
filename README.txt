+----------------------+
|    Nspire I/O 2.0    |
+----------------------+

Installation
------------
To install it, just copy the "lib" and "include" directories over
to your .ndless directory located at the userpath, for example
C:\Users\Name\.ndless or /home/name/.ndless
or build the code yourself from the "src" directory.

Usage
-----
Add "-lnspireio2" to LDFLAGS in your Makefile and include
"nspireio2.h" in your code.
Nspire I/O 2.0 is not compatible to older versions.

A color support for CX is currently not implemented, but it
will work fine on CXes with the LCD set to grayscale mode
by using "lcd_ingray()".

Documentation
-------------
An auto-generated documentation can be found in the "doc/html"
directory, just open "index.html" (if something is unclear,
please contact me and I will try to help you ;)
The code of the demo application can be found in "src/demo".

Contact
-------
Julian Mackeben aka compu
E-Mail: compujuckel@googlemail.com
Discussion topic: http://www.omnimaga.org/index.php?topic=6871.0