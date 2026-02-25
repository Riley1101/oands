CC = gcc
UNAME_S := $(shell uname -s)

# --- Platform Specific Configurations ---
ifeq ($(UNAME_S), Darwin)
    # macOS Settings
    DEBUGGER = lldb
    # gdwarf-4 is specific for Darwin debuggers (GDB/LLDB)
    CFLAGS = -Wall -Wextra -g -std=c99 -gdwarf-4
    # Command to bundle debug symbols on Mac
    POST_BUILD = dsymutil $(TARGET)
else
    # Linux/Other Settings
    DEBUGGER = gdb
    CFLAGS = -Wall -Wextra -g -std=c99
    POST_BUILD = @true
endif

TARGET = main
SRCS = main.c chunk.c compiler.c memory.c debug.c scanner.c value.c vm.c object.c
OBJS = $(SRCS:.c=.o)
HDRS = chunk.h common.h compiler.h memory.h debug.h scanner.h value.h vm.h object.h

FILE ?= $(file)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	$(POST_BUILD)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

build: $(TARGET)

run: $(TARGET)
	@echo "--- Running Program ---"
	@if [ -n "$(FILE)" ]; then ./$(TARGET) "$(FILE)"; else ./$(TARGET); fi

# --- Adaptive Debug Target ---
debug: $(TARGET)
	@echo "--- Starting Debugger ($(DEBUGGER)) ---"
	@if [ "$(UNAME_S)" = "Darwin" ]; then \
		if [ -n "$(FILE)" ]; then $(DEBUGGER) -- ./$(TARGET) $(FILE); else $(DEBUGGER) ./$(TARGET); fi; \
	else \
		if [ -n "$(FILE)" ]; then $(DEBUGGER) --args ./$(TARGET) $(FILE); else $(DEBUGGER) ./$(TARGET); fi; \
	fi

tokens: $(TARGET)
	@if [ -z "$(FILE)" ]; then echo "Usage: make tokens file=<path>"; exit 1; fi
	@./$(TARGET) --tokens "$(FILE)"

leaks: $(TARGET)
	@echo "--- Running leak checker ---"
	@if [ "$(UNAME_S)" = "Darwin" ]; then \
		if [ -n "$(FILE)" ]; then leaks --atExit -- ./$(TARGET) "$(FILE)"; else leaks --atExit -- ./$(TARGET); fi; \
	else \
		if [ -n "$(FILE)" ]; then valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET) "$(FILE)"; else valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET); fi; \
	fi

help:
	@echo "--- Makefile Usage ---"
	@echo "  make build          - Compiles the project"
	@echo "  make run file=x     - Runs program with a specific file"
	@echo "  make debug file=x   - Starts $(DEBUGGER) with the specified file"
	@echo "  make leaks file=x   - Checks for memory leaks"
	@echo "  make clean          - Removes binaries and object files"

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(TARGET).dSYM

.PHONY: all clean build run tokens debug leaks help
