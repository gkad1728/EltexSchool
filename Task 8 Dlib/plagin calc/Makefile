BIN := main
OBJ := main.o lib.o
SRC := main.c lib.c

CC := gcc
CFLAGS := -Wl,-rpath,./plagins -g

.PHONY : all clean

all : $(BIN)

$(BIN) : $(OBJ)
		$(CC) $(OBJ) -o $(BIN) $(CFLAGS)
		
$(OBJ) : $(SRC)
		$(CC) $(SRC) -c

clean : 
		rm -rf $(BIN) $(OBJ)
