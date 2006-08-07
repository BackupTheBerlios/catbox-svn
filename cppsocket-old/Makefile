CFLAGS = -Wall -g
main:	socket	main.cpp network client
	g++ -o main main.cpp socket.o network.o client.o $(CFLAGS)
socket:	socket.cpp
	g++ -c socket.cpp $(CFLAGS)
network:	network.cpp
	g++ -c network.cpp $(CFLAGS)
client:	client.cpp
	g++ -c client.cpp $(CFLAGS)
	