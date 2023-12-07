CC = gcc
CFLAGS = -pedantic  -Werror -g
#CFLAGS = -pedantic -Werror -Ofast -g
LIBS = -mavx
SRC = iaxpy.c
BIN = iaxpy

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean

clean:
	rm -f $(BIN)

