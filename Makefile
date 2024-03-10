CC = gcc
# CFLAGS = -Wall -Werror -Wextra -pedantic
CFLAGS = -Wall -Wextra -pedantic
DEBUG_FLAGS = -ggdb3
LIBS = -Iinclude -lncurses
TARGET = bin/checkmate

.PHONY: clean

all:
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) src/*.c

debug:
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(LIBS) -o $(TARGET) *.c

clean:
	rm $(TARGET)
