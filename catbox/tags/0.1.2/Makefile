PARAMETERS=-g -Wall
COMPILER=gcc
OBJECTS=files.o daemon.o #parser.o

catboxd:	main.c  $(OBJECTS)
	$(COMPILER) $(PARAMETERS) -o catboxd main.c daemon.o files.o  
daemon.o:	daemon.c daemon.h
	$(COMPILER) $(PARAMETERS) -o daemon.o -c daemon.c
files.o:
	$(COMPILER) $(PARAMETERS) -o files.o -c files.c
clean:
	rm -rf *.o
