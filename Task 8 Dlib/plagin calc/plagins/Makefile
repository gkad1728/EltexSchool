CC := gcc

.PHONY : all clean 

all : libaddsub.so libmul.so libdiv.so

libaddsub.so : AddSub.o
		$(CC) -shared $^ -o libaddsub.so
AddSub.o : AddSub.c
		$(CC) $^ -fPIC -c

libmul.so : mul.o
		$(CC) -shared $^ -o libmul.so
mul.o : mul.c
		$(CC) $^ -fPIC -c

libdiv.so : div.o
		$(CC) -shared $^ -o libdiv.so
div.o : div.c
		$(CC) $^ -fPIC -c
		
clean:
		rm -rf div.o AddSub.o mul.o libaddsub.so libmul.so libdiv.so
