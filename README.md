# helgarahi
basic library for converting xlsx to sqlite3 db or csv file

## requirements
- C/C++ compiler
- unix-like OS
- glibc or equivalent
- sqlite3 (for sql exporting)
- csv (for csv exporting)
- libxml2
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
- add csv support
- add merge function for tables

## long term todo
- rewrite to C from C++ for full portability
- test on windows with vs studio/mingw
- add an interpreter to convert back to xlsx