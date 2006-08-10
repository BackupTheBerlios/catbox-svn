CFLAGS = -Wall -g
main:	socket	main.cpp network client clientsocket
	g++ -o main main.cpp socket.o network.o client.o clientsocket.o $(CFLAGS)
socket:	socket.cpp
	g++ -c socket.cpp $(CFLAGS)
network:	network.cpp
	g++ -c network.cpp $(CFLAGS)
client:	client.cpp
	g++ -c client.cpp $(CFLAGS)
clientsocket:	clientsocket.h clientsocket.cpp 
	g++ -c clientsocket.cpp $(CFLAGS)
serversocket:	serversocket.h serversocket.cpp
	g++ -c serversocket.cpp $(CFLAGS)