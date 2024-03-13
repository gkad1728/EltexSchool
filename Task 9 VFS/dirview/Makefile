
.PHONY : all clean

main : obj/main.o obj/print.o obj/dir.o
		gcc obj/main.o obj/print.o obj/dir.o -o main -g -lncurses 
		
obj/dir.o : src/dir.c
		gcc src/dir.c -c -o obj/dir.o -g
		
obj/main.o : src/main.c
		gcc src/main.c -c -o obj/main.o -g
		
obj/print.o : src/print.c
		gcc src/print.c -c -o obj/print.o -g

clean :
		rm -rf obj/main.o obj/print.o obj/dir.o main
		
