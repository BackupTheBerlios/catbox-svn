PARAMETERS=-g

catboxd:	main.c  daemon.o files.o
	gcc $(PARAMETERS) -o catboxd main.c daemon.o files.o  
daemon.o:	daemon.c daemon.h
	gcc $(PARAMETERS) -o daemon.o -c daemon.c
files.o:
	gcc $(PARAMETERS) -o files.o -c files.c
clean:
	rm -rf *.o
