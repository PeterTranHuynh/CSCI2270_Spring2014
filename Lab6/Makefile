# Make file for Lab5, CSCI2270
# WRITTEN BY: Elizabeth White
#
# This makefile is used as follows to regenerate files for the Aligner program:
#   make Aligner.o   --  Regenerates Aligner.o by compiling
#   make TestAligner.o   --  Regenerates TestAligner.o by compiling
#   make TestAligner --  Regenerates the executable TestAligner file by compiling
#   make              --  Same as "make TestAligner" (since TestAligner is 
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
EXPENDABLES = Aligner.o TestAligner.o TestAligner

# make all is listed first, which lets you type "make" to recompile 
# anything that has changed in either your class, your test code, 
# or my test code.
all:
	@make $(EXPENDABLES)

# this compiles your test program and your Aligner class together
TestAligner: TestAligner.o Aligner.o
	g++ -Wall -g Aligner.o TestAligner.o -lm -o TestAligner 

# this compiles your Aligner class, which isn't executable (no main)
Aligner.o: Aligner.h Aligner.cxx
	g++ -Wall -g -c Aligner.cxx -o Aligner.o

# this compiles your test program, which is executable
TestAligner.o: Aligner.h TestAligner.cxx
	g++ -Wall -g -c TestAligner.cxx -o TestAligner.o

# this deletes all the output files
clean:
	rm $(EXPENDABLES)
