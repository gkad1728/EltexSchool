
.PHONY : all clean

main : obj/main.o obj/print.o obj/dir.o test/testoutput test/testinput
		gcc obj/main.o obj/print.o obj/dir.o -o main -g -lncurses 

test/testoutput : test/testoutput.c
		gcc test/testoutput.c -o test/testoutput -g
		
test/testinput : test/testinput.c
		gcc test/testinput.c -o test/testinput -g
	
obj/dir.o : src/dir.c
		gcc src/dir.c -c -o obj/dir.o -g
		
obj/main.o : src/main.c
		gcc src/main.c -c -o obj/main.o -g
		
obj/print.o : src/print.c
		gcc src/print.c -c -o obj/print.o -g

clean :
		rm -rf obj/main.o obj/print.o obj/dir.o main test/testinput test/testoutput
		
