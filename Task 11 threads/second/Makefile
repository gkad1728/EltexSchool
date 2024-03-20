.PHONY : all clean test

all: mutex.c nonmutex.c nonthread.c
		gcc mutex.c -o mutex -pthread
		gcc nonmutex.c -o nonmutex -pthread
		gcc nonthread.c -o nonthread

test :  
		/usr/bin/time --verbose ./mutex  
		/usr/bin/time --verbose ./nonmutex  
		/usr/bin/time --verbose ./nonthread 
		echo result ninmutes WIN
		
clean :
		rm -rf nonmutex mutex nonthread
