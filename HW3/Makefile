# Make file for HW3, CSCI2270
# WRITTEN BY: Elizabeth White
#
# This makefile is used as follows to regenerate files for the BigNum program:
#   make BigNum.o   --  Regenerates BigNum.o by compiling
#   make TestBigNum.o   --  Regenerates TestBigNum.o by compiling
#   make TestBigNum --  Regenerates the executable TestBigNum file by compiling
#   make              --  Same as "make TestBigNum" (since TestBigNum is 
#                     --  the 1st target)
#
# Two special targets may also be used with this makefile:
#   make all          --  Regenerates all files listed above
#   make clean        --  Erases all files listed above
#
# All compilations occur with -Wall and -g.
# The clean command uses rm to remove all expendable files.

# define the different outputs of all g++ commands
# on Ubuntu, the .exe suffix disappears
EXPENDABLES = BigNum.o TestBigNum.o TestBigNum

# make all is listed first, which lets you type "make" to recompile 
# anything that has changed in either your class, your test code, 
# or my test code.
all:
	@make $(EXPENDABLES)

# this compiles your test program and your BigNum class together
TestBigNum: TestBigNum.o BigNum.o
	g++ -std=c++0x -Wall -g BigNum.o TestBigNum.o -lm -o TestBigNum 

# this compiles your BigNum class, which isn't executable (no main)
BigNum.o: BigNum.h BigNum.cxx
	g++ -std=c++0x -Wall -g -c BigNum.cxx -o BigNum.o

# this compiles your test program, which is executable
TestBigNum.o: BigNum.h TestBigNum.cxx
	g++ -std=c++0x -Wall -g -c TestBigNum.cxx -o TestBigNum.o

# this deletes all the output files
clean:
	rm $(EXPENDABLES)
