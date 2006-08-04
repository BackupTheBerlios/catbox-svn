CFLAGS = -Wall -g
main:	socket	main.cpp network
	g++ -o main main.cpp socket.o network.o $(CFLAGS)
socket:	socket.cpp
	g++ -c socket.cpp $(CFLAGS)
network:	network.cpp
	g++ -c network.cpp $(CFLAGS)

	