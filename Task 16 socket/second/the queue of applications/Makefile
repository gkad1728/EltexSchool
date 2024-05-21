.PHONY : all clean

all : udp_client udp_server client_test
		
udp_client : udp_client.c
		gcc udp_client.c -o udp_client -g
		
udp_server : udp_server.c
		gcc udp_server.c -o udp_server -g

client_test : client_test.c
		gcc client_test.c -o client_test
		
clean :
		rm -rf udp_client udp_server client_test
