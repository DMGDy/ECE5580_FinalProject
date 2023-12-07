CC = gcc
CFLAGS = -pedantic -Werror -Ofast
#CFLAGS = -pedantic -Werror -Ofast -g
LIBS = -mavx 
SRC = matrix_mul2.c
BIN = matrix_mul2

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean

clean:
	rm -f $(BIN)

