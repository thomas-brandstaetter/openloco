# openloco - The open logic controller

openloco is an open source implementation of IEC 61131-3 languages - espacially STL.
Take a look at the develop branch for recent features.

## Make IEC 61131-3 great again

Goals:

* Multiplatform:  Linux, macOS. FreeBSD
* Implement the full Standard (based on IEC:2003)
* Postscript for vector graphics output of graphical languages
* Just-In-Time compiling of STL and IL code.
* Compiles into LLVM 7 IL to support as many target platforms as possible
    * take a look at [LLVM Targets](https://llvm.org/devmtg/2014-04/PDFs/LightningTalks/2014-3-31_ClangTargetSupport_LighteningTalk.pdf)
* Bindings for popular languages
    * Python, C++, C#, Java, ... 
* Virtual PLC
    * Virtual Raspberry Pi
    * Virtual Arduino
    * Virtual PLC
* Configurations files for various systems to use it with conformance
    * Raspberry Pi
    * Arduino
* Package manager for programs and modules

## Current Status 
    
* Implement the standard
* use LLVM to
    * generate code 
    * prepare JIT
 
## Development

Tools used in this project

* C++ 17, Boost
* python
* cmake, ninja
* ~~bison/flex~~ antlr4 (we live in the 21th century)
* postscript
* LLVM
* sqlite
