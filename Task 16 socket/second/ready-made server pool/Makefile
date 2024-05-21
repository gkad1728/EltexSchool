.PHONY : all clean

all : tcp_client tcp_server #udp_client udp_server

tcp_client : tcp_client.c
		gcc tcp_client.c -o tcp_client -g

tcp_server : tcp_server.c
		gcc tcp_server.c -o tcp_server -g 
		
clean :
		rm -rf tcp_client tcp_server 
