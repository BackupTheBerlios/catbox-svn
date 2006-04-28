CC=g++
main:	network.o main.o
	$(CC) -o main main.o network.o -g
network.o:	network.cpp network.h
	$(CC) -c network.cpp -g
main.o:	main.cpp 
	$(CC) -c main.cpp -g
