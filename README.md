# Index of Coincidence

> Disclaimer: This is a small side project

This codebase provides a simple C implementation fo the __Index of Coincidence__ computation. Simply put, the __index of coincidence__ is a metric for non-random the distributions of the letter in a text are. For instance in english, the letter `e` is more common than most others.

The __index of coincidence__ has some implications in cryptography. More information can be found in [the dedicated Wikipedia article](https://en.wikipedia.org/wiki/Index_of_coincidence).

This code was inspired by the great video from great video from [Computerphile](https://www.youtube.com/user/Computerphile) titled [Cracking the Enigma in 2021 - Computerphile](https://www.youtube.com/watch?v=RzWB5jL5RX0).

# Installation

To install the tool, go into the main directory and run `make install`. The code is written in C and depends entirely on the standard library, so the compilation only requires three elements:

 - A GNU/Linux installation, with glibc installed and various coreutils tools present like __rm__, __install__ etc... :penguin:
 - A recent C compiler, like __gcc__ or __clang__ :robot:
 - The __make__ compilation tool, part of __build-essentials__ :toolbox:

# Usage

To get help from the tool, just run `index-of-coincidence -h`. That command should output the help message reproduced below.

```
Usage: index-of-coincidence [options]

Description
===========
Computes the Index of Coincidence of the lowercase ASCII text from stdin.

Options
=======
 -i
   Output the Index of Coincidence of the input (the default).

 -k
   Output the kappa plaintext of the input.

 -l
   Tries to guess the input language of the input from the index of coincidence.

 -h
   Prints this help message and exits

Note
====
Only the last specified option will be considered.
```

:bulb: Note that the tool is __ASCII only__ and reads its text from __stdin__.

### METADATA

Field | Value
--- | ---
:pencil: Contributors | roadelou
:email: Contacts | 
:date: Creation Date | 2021-04-16
:bulb: Language | Markdown Document

### EOF
