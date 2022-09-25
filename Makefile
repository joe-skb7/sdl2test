CC = gcc
CPPFLAGS = -Iinclude
CFLAGS = $(shell pkg-config --cflags sdl2 SDL2_image)
LIBS = $(shell pkg-config --libs sdl2 SDL2_image)
CFLAGS += -Wall -O2
BIN = sdl2test
OBJS =				\
	src/main.o		\
	src/window.o

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

clean:
	-rm -f $(OBJS)

distclean: clean clean-index
	-rm -f $(BIN)

include Makefile.index
include Makefile.check

.PHONY: all clean
