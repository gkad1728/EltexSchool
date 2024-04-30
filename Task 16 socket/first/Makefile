.PHONY : all clean

all : #inet_tcp_client inet_tcp_server inet_udp_client inet_udp_server local_tcp_client local_tcp_server local_udp_client local_udp_server
		gcc inet_tcp_client.c -o inet_tcp_client -g
		gcc inet_tcp_server.c -o inet_tcp_server -g
		gcc inet_udp_client.c -o inet_udp_client -g
		gcc inet_udp_server.c -o inet_udp_server -g
		gcc local_tcp_client.c -o local_tcp_client -g
		gcc local_tcp_server.c -o local_tcp_server -g
		gcc local_udp_client.c -o local_udp_client -g
		gcc local_udp_server.c -o local_udp_server -g
clean :
		rm -rf inet_tcp_client inet_tcp_server inet_udp_client inet_udp_server local_tcp_client local_tcp_server local_udp_client local_udp_server
