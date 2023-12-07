CC = gcc
CFLAGS = -pedantic -Werror -Ofast
#CFLAGS = -pedantic -Werror -Ofast -g
LIBS = -mavx 
SRC = matrix_mul.c
BIN = matrix_mul

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean

clean:
	rm -f $(BIN)

