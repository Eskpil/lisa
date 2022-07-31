#!/bin/sh

set -ex

mkdir -p build/

as --32 src/boot.s -o build/boot.o

#compile kernel.c file
gcc -m32 -c src/kernel.c -o build/kernel.o -std=c11 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector
gcc -m32 -c src/vga.c -o build/vga.o -std=c11 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector

#linking the kernel with kernel.o and boot.o files
ld -m elf_i386 -T src/linker.ld build/*.o -o build/lisa.bin -nostdlib

#check MyOS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot build/lisa.bin

#building the iso file
mkdir -p isodir/boot/grub
cp build/lisa.bin isodir/boot/lisa.bin
cp meta/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o build/lisa.iso isodir
