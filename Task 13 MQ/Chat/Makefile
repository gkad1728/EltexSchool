.PHONY : all clean

all : server client

server : obj/Server.o obj/libServ.o
		gcc obj/Server.o obj/libServ.o -o server -g -lncurses 

client : obj/Client.o obj/libCli.o
		gcc obj/Client.o obj/libCli.o -o client -g -lncurses 

obj/Server.o : src/Server.c
		gcc src/Server.c -c -o obj/Server.o -g

obj/Client.o : src/Client.c
		gcc src/Client.c -c -o obj/Client.o -g

obj/libServ.o : src/libServ.c
		gcc src/libServ.c -c -o obj/libServ.o -g

obj/libCli.o : src/libCli.c
		gcc src/libCli.c -c -o obj/libCli.o -g
		
clean :
		rm -rf obj/libCli.o obj/libServ.o obj/Client.o obj/Server.o client server
