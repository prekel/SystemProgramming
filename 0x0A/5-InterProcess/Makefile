CC = clang-9

SOURCES = $(wildcard *.c)
OUTFILES = $(SOURCES:.c=)

all : $(OUTFILES)

% : %.c
	$(CC) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILES)
