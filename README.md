# 💽 Tiny Programming Language Parser 💽

This was one of the last projects I had for one of my two compilers classes that I needed to graduate for my Bachelors.

The other project was to write a Constrainer and Code Generator for this same language that outputs Bytecode for the professors VM, but since the professor wrote the VM and that is a major part of the code I won't publish that.

The project was to Lexically Analyze & to Parse a subset of C call Subc/Tiny. It was supposed to be a semester long project, but college me felt confident it could be done in 5 days, I only worked on it for 4. Check the history for proof. 😉😅

## Build/Install

The application is standalone, it only runs off of the C++11 Standard Libraries. It simply needs to be compiled with g++ 4.8+ using the included Makefile in the root project directory, example:

```shell
git clone git@github.com:husseinm/Tiny_Language_Parser.git
cd ./Tiny_Language_Parser
make
```

The result will be an executable named `subc` in the root directory that can be directly executed.

## Usage

The program takes either one or two arguments, the action & the directory to the program to lex/parse. Below is the help output:

```shell
HELP:
         subc (-ast | -lex) PATH_TO_TINY_PROGRAM
```

As should be evident, only one option can be supplied, either `-ast` or `-lex`

`-ast` = Will print the full AST of the supplied Tiny program to StdOut.  
`-lex` = Will print all lexical tokens of the supplied Tiny program to StdOut.

If no flags are supplied then the program will output nothing for a syntactically correct program or an error if not correct.

## Tests

There are 25 test programs with 25 reference ASTs supplied in the `tiny_test_progs` directory. You can use them to test the parser OR test the whole thing with the `test.sh` shell script provided, example:

```shell
mahdi@MAHDI-DESKTOP:/mnt/c/Users/mahdi/Code/COP4020$ make && ./test.sh
make: 'subc' is up to date.
Tiny Program #01 matched the reference AST! ✅
Tiny Program #02 matched the reference AST! ✅
Tiny Program #03 matched the reference AST! ✅
Tiny Program #04 matched the reference AST! ✅
Tiny Program #05 matched the reference AST! ✅
Tiny Program #06 matched the reference AST! ✅
Tiny Program #07 matched the reference AST! ✅
Tiny Program #08 matched the reference AST! ✅
Tiny Program #09 matched the reference AST! ✅
Tiny Program #10 matched the reference AST! ✅
Tiny Program #11 matched the reference AST! ✅
Tiny Program #12 matched the reference AST! ✅
Tiny Program #13 matched the reference AST! ✅
Tiny Program #14 matched the reference AST! ✅
Tiny Program #15 matched the reference AST! ✅
Tiny Program #16 matched the reference AST! ✅
Tiny Program #17 matched the reference AST! ✅
Tiny Program #18 matched the reference AST! ✅
Tiny Program #19 matched the reference AST! ✅
Tiny Program #20 matched the reference AST! ✅
Tiny Program #21 matched the reference AST! ✅
Tiny Program #22 matched the reference AST! ✅
Tiny Program #23 matched the reference AST! ✅
Tiny Program #24 matched the reference AST! ✅
Tiny Program #25 matched the reference AST! ✅
```

## To Do

Fix the pointers to use smart pointers...
