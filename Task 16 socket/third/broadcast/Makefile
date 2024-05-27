.PHONY : all clean

all : client server

client : client.c
		gcc client.c -o client -g
		
server : server.c
		gcc server.c -o server -g
		
clean : 
		rm -rf client server
