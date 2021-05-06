##
# @file      makefile
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
# @brief     @EOL
# @Keywords  
# @Std       GNUmake BSDmake SYSVmake GenericMake
#
#            Notes here
#            


# Fix for local needs
CC       = gcc
CFLAGS   = -Wall -O3

GMPIPATH  = -I/opt/local/include
GMPLIB    = -lgmp
GMPLPATH  = -L/opt/local/lib

# Uncomment to build all when make file changes
SPECDEP=makefile

# Put targets here
TARGETS = fndFactor gmpLCG gmpRandEx piWallis randPi

all : $(TARGETS)
	@echo Make Complete

clean :
	rm -rf a.out *~ *.bak $(TARGETS)
	@echo Make Complete

fndFactor : fndFactor.c $(SPECDEP)
	$(CC) $(CFLAGS) $(GMPIPATH) fndFactor.c $(GMPLPATH) $(GMPLIB) -o fndFactor

gmpLCG : gmpLCG.c $(SPECDEP)
	$(CC) $(CFLAGS) $(GMPIPATH) gmpLCG.c $(GMPLPATH) $(GMPLIB) -o gmpLCG

gmpRandEx : gmpRandEx.c $(SPECDEP)
	$(CC) $(CFLAGS) $(GMPIPATH) gmpRandEx.c $(GMPLPATH) $(GMPLIB) -o gmpRandEx

piWallis : piWallis.c $(SPECDEP)
	$(CC) $(CFLAGS) $(GMPIPATH) piWallis.c $(GMPLPATH) $(GMPLIB) -o piWallis

randPi : randPi.c $(SPECDEP)
	$(CC) $(CFLAGS) $(GMPIPATH) randPi.c $(GMPLPATH) $(GMPLIB) -o randPi
