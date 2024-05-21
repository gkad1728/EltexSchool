.PHONY : all clean

all : udp_client tcp_client server client_test
		
udp_client : udp_client.c
		gcc udp_client.c -o udp_client -g
		
server : server.c
		gcc server.c -o server -g

client_test : client_test.c
		gcc client_test.c -o client_test
		
tcp_client : tcp_client.c
		gcc tcp_client.c -o tcp_client -g
		
clean :
		rm -rf udp_client tcp_client server client_test
