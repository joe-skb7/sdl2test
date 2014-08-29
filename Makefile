CC = gcc
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LDFLAGS = $(shell sdl2-config --libs)
CPPFLAGS = -Iinclude
CFLAGS = -Wall -O2
BIN = sdl2test
OBJS =				\
	src/main.o		\
	src/window.o

default: $(BIN)

%.o: %.c
	$(CC) $(SDL2_CFLAGS) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(SDL2_LDFLAGS) $^ -o $@

clean:
	-rm -f $(BIN) $(OBJS)

.PHONY: default clean
