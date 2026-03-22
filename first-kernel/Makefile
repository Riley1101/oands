# --- OS Detection ---
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	# macOS Configuration
	CC = i686-elf-gcc
	AS = i686-elf-as
	QEMU = qemu-system-i386
	
	# The command to launch the VNC viewer on Mac
	# (You can also change this to 'open vnc://127.0.0.1:5900' to use Mac's built-in viewer)
	# VNC_VIEWER = open 127.0.0.1:10002
	
	# Mac run behavior (Direct Kernel Boot)
	DEFAULT_TARGET = $(BIN)
	RUN_DEP = $(BIN)
	RUN_CMD = $(QEMU) -kernel $(BIN)
else
	# Linux Configuration
	CC = i686-elf-gcc
	AS = i686-elf-as
	MKRESCUE = grub-mkrescue
	QEMU = qemu-system-i386
	VNC_VIEWER = vncviewer 127.0.0.1:10002
	
	# Linux run behavior (ISO Boot)
	DEFAULT_TARGET = $(ISO)
	RUN_DEP = $(ISO)
	RUN_CMD = $(QEMU) -cdrom $(ISO)
endif

# --- Flags ---
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

# --- Files ---
OBJS = boot.o kernel.o
BIN = myos.bin
ISO = myos.iso

# --- Targets ---
.PHONY: all run run-vnc clean check-tools

all: check-tools $(DEFAULT_TARGET)

check-tools:
	@which $(CC) > /dev/null || (echo "ERROR: $(CC) not found!" && exit 1)
	@which $(AS) > /dev/null || (echo "ERROR: $(AS) not found!" && exit 1)

boot.o: boot.s
	$(AS) $< -o $@

kernel.o: kernel.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJS) linker.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(ISO): $(BIN) grub.cfg
	mkdir -p iso/boot/grub
	cp $(BIN) iso/boot/myos
	cp grub.cfg iso/boot/grub/grub.cfg
	$(MKRESCUE) -o $@ iso

# Standard Run Target (Pops open standard QEMU window)
run: $(RUN_DEP)
	$(RUN_CMD)

# VNC Run Target (Starts QEMU in background, launches TigerVNC)
run-vnc: $(RUN_DEP)
	-killall $(QEMU) 2>/dev/null || true
	@echo "Starting QEMU VNC server on 127.0.0.1:5900..."
	$(RUN_CMD) -vnc 127.0.0.1:0

clean:
	rm -f $(OBJS) $(BIN) $(ISO)
	rm -rf iso/boot/myos iso/boot/grub/grub.cfg
