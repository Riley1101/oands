CC = gcc
# debug symbol here
CFLAGS = -Wall -Wextra -g -std=c99

TARGET = main

SRCS = main.c chunk.c memory.c debug.c value.c vm.c
OBJS = $(SRCS:.c=.o)
HDRS = chunk.h common.h memory.h debug.h value.h vm.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

build: $(TARGET)

start: $(TARGET)
	@echo "--- Running Program ---"
	./$(TARGET)

debug: $(TARGET)
	@echo "--- Running Valgrind ---"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean build start debug
