PARAMETERS=-g -Wall
COMPILER=gcc
OBJECTS=#files.o daemon.o #parser.o
all:	catboxd catboxc
	make catboxc && make catboxd
catboxd:	catboxd.c  
	$(COMPILER) $(PARAMETERS) -o catboxd catboxd.c
catboxc:	catboxc.c
	$(COMPILER) $(PARAMETERS) -o catboxc catboxc.c 
#daemon.o:	daemon.c daemon.h
#	$(COMPILER) $(PARAMETERS) -o daemon.o -c daemon.c
#files.o:
#	$(COMPILER) $(PARAMETERS) -o files.o -c files.c#
clean:
	rm -rf *.o catboxd catboxc
