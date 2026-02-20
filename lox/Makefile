CC = gcc
# debug symbol here
CFLAGS = -Wall -Wextra -g -std=c99

TARGET = main

SRCS = main.c chunk.c compiler.c memory.c debug.c scanner.c value.c vm.c
OBJS = $(SRCS:.c=.o)
HDRS = chunk.h common.h compiler.h memory.h debug.h scanner.h value.h vm.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Optional: run with a file, e.g. make run file=test.beer or make run FILE=script.syn
FILE ?= $(file)

build: $(TARGET)

start: $(TARGET)
	@echo "--- Running Program ---"
	./$(TARGET)

run: $(TARGET)
	@echo "--- Running Program ---"
	@if [ -n "$(FILE)" ]; then ./$(TARGET) "$(FILE)"; else ./$(TARGET); fi

tokens: $(TARGET)
	@if [ -z "$(FILE)" ]; then echo "Usage: make tokens file=<path>"; exit 1; fi
	@./$(TARGET) --tokens "$(FILE)"

debug: $(TARGET)
	@echo "--- Running leak checker ---"
	@if [ "$$(uname)" = "Darwin" ]; then \
		if [ -n "$(FILE)" ]; then leaks --atExit -- ./$(TARGET) "$(FILE)"; else leaks --atExit -- ./$(TARGET); fi; \
	else \
		if [ -n "$(FILE)" ]; then valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET) "$(FILE)"; else valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET); fi; \
	fi

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean build start run tokens debug
