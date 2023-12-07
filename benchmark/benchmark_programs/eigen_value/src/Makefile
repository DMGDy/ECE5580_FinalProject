CC = gcc
CFLAGS = -pedantic -Werror -Ofast
#CFLAGS = -pedantic -Werror -Ofast -g
LIBS = -mavx 
SRC = eigen_value.c
BIN = eigen_value

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean

clean:
	rm -f $(BIN)

