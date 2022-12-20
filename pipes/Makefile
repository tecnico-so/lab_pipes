CC=gcc
LD=gcc
CFLAGS=-fsanitize=address -std=c17 -g
LDFLAGS=-fsanitize=address

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)
TARGETS := $(SOURCES:.c=)

.PHONY: all clean fmt

all: $(TARGETS)

pipes: pipes.o

named_pipes_sender: named_pipes_sender.o

named_pipes_receiver: named_pipes_receiver.o

fmt: $(SOURCES)
	clang-format -i $^

clean:
	@rm -f $(OBJECTS) $(TARGETS)
