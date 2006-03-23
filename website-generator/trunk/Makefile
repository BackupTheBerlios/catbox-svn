generator:	main.c main.h website.o files.o 
	gcc -g -o webgen main.c files.o
files:		files.c files.h
	gcc -g -o files.o -c files.c
website:	
clean:		*.o
		rm -rf *.o
