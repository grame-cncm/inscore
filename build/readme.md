INScore build system
======================================================================

[Grame](http://www.grame.fr) - Centre National de Création Musicale
----------------------------------------------------------------------

---

Status: ![CI](https://github.com/grame-cncm/inscore/workflows/CI/badge.svg)

---

INScore build system is based on [CMake](https://cmake.org/). 
This folder contains configuration files for setting up the different compilation targets with CMake.

Although you could directly use `cmake` to build and compile the project, a Makefile is provided as a high level interface to cover the various options to build the project.

By default, you can simply run the command
~~~
make
~~~
It generates the INScore library and INScoreViewer application.


To get the various `make` options, simply run the command
~~~
make help
~~~
 
### Note for Windows 
A `Make.bat` script is provided to generate the INScore library and INScoreViewer application.  


