.PHONY : all clean

all : main

main : obj/lib.o obj/main.o
		gcc obj/main.o obj/lib.o -o main -g -pthread

obj/main.o : src/main.c
		gcc src/main.c -c -o obj/main.o -g 

obj/lib.o : src/lib.c
		gcc src/lib.c -c -o obj/lib.o -g

clean :
		rm -rf obj/lib.o obj/main.o main
