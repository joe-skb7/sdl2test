CC = gcc
CPPFLAGS = -Iinclude
CFLAGS = $(shell pkg-config --cflags sdl2 SDL2_image)
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_image)
CFLAGS += -Wall -O2
BIN = sdl2test
OBJS =				\
	src/main.o		\
	src/window.o

default: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	-rm -f $(BIN) $(OBJS)

index:
	@find . -name '*.[ch]' >cscope.files
	@cscope -b -q
	@ctags -L cscope.files
	@-rm -f cscope.files

clean-index:
	@-rm -f cscope.out cscope.in.out cscope.po.out tags

.PHONY: default clean index clean-index
