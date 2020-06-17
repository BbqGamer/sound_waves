Sound Waves

C++ Educational Project about sound files

Technikum Komunikacji Poznań Polska



File FileHandling.h contains classes to simplify using files written in Little Endian
It provides one base File object, and two children FileReader and FileWriter

FileReader contains method readLittleEndianToBuffor which is used to some number of bytes
to a buffor. You can specify a size of a buffor with generate Buffor.
(ReadLittleEndian() automatically, reads some bytes and returns value from buffor)

FileWriter contains method writeLittleEndian which is used to write certain word to a file,
size of a word depends on a size of variable type (can be also assigned explicitly).
It supports integer values, BUT NOT FLOAT values.


