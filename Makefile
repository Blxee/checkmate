CC = gcc
# CFLAGS = -Wall -Werror -Wextra -pedantic
CFLAGS = -Wall -Wextra -pedantic
DEBUG_FLAGS = -ggdb3
LIBS = -lncurses
TARGET = checkmate

.PHONY: clean

all:
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) *.c

debug:
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(LIBS) -o $(TARGET) *.c

clean:
	rm $(TARGET)
