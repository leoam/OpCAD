# Makefile for the socket programming example
#

#CXX=g++-3.3
CXX=g++
simple_server_objects = ServerSocket.o Socket.o IOGenetic.o
#simple_client_objects = ClientSocket.o Socket.o #simple_client_main.o

%.o : %.cpp
	$(CXX) -g -c $< -o $@

all : simple_server #simple_client

simple_server: $(simple_server_objects)
	#g++-3.3 -o simple_server $(simple_server_objects) -lsocket -lnsl
	$(CXX) -g -o simple_server $(simple_server_objects) -lnsl
	#g++ -o simple_server $(simple_server_objects) -lnsl

#simple_client: $(simple_client_objects)
#	g++ -o simple_client $(simple_client_objects) -lsocket -lnsl


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
#ClientSocket: ClientSocket.cpp
simple_server_main: IOGenetic.cpp
#simple_client_main: simple_client_main.cpp


clean:
	rm -f *.o simple_server #simple_client
