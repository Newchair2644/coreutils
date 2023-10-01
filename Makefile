CC = gcc
CFLAGS = -Wall -Wextra

SOURCES = $(wildcard *.c)

BINARIES = $(patsubst %.c,bin/%,$(SOURCES))

all: $(BINARIES)

bin/%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BINARIES)
