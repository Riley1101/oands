#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/gideon.kernel isodir/boot/gideon.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "gideon" {
	multiboot /boot/gideon.kernel
}
EOF
grub-mkrescue -o gideon.iso isodir
