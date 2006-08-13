CFLAGS = -Wall -g
main:	socket	main.cpp network clientsocket
	g++ -o main main.cpp socket.o network.o serversocket.o clientsocket.o $(CFLAGS)
socket:	socket.cpp
	g++ -c socket.cpp $(CFLAGS)
network:	network.cpp
	g++ -c network.cpp $(CFLAGS)
clientsocket:	clientsocket.h clientsocket.cpp 
	g++ -c clientsocket.cpp $(CFLAGS)
serversocket:	serversocket.h serversocket.cpp
	g++ -c serversocket.cpp $(CFLAGS)