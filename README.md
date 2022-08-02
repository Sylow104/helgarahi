# helgarahi
basic library for converting xlsx to sqlite3 db or csv file

## requirements
- C/C++ compiler
- unix-like OS
- glibc or equivalent
- libexpat
- libzip
- cmake v3.10

## building
```
mkdir build;
cd build;
cmake ../ ;
make;
// optionally
make install ;
```

## short term todo
- ~~add csv support~~ will be done in another library
- ~~add merge function for tables~~ ditto
- ~~add header/headerless option~~ ditto
- ~~rewrite using sax parser~~ expat covers this

## long term todo
- ~~rewrite to C from C++ for full portability~~ done
- ensure unix functions are replaced in windows with equivalent functions
- test on windows with vs studio/mingw
- add an interpreter to convert back to xlsx