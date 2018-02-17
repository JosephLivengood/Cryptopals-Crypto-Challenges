# Cryptopals-Crypto-Challenges
C++ set of solutions to the renowned Cryptopals Crypto Challenges on https://cryptopals.com


## Building

This project uses `make` to build. So to run, just type `make` in the shell.

If you want to create an executable bundled with stdlib (to increase portability) you can run `make bin/dist/yourbinary`

## Tests

Tests are organized to replicate the sets/challenges structure but also includes edge cases/error testing.

Easy testing with `make test` for verbose test building and running with timings.

## Folder structure

```
|-- apps/
|    | # Executable files
|    | # Each file here will generate a correspondent exec file in bin/
|-- bin/
|    | # Compiled binaries
|-- include/
|    | # Header files
|-- src/
|    | # Class files
|-- test/
|    |-- main.cpp # Main Catch test executable
|    | # Test files
|-- Makefile
|-- README.md
+-- run_tests
```
