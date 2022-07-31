#!/bin/sh

set -ex

mkdir -p build/

as --32 src/boot.s -o build/boot.o

#compile kernel.c file
gcc -m32 -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#linking the kernel with kernel.o and boot.o files
ld -m elf_i386 -T linker.ld build/kernel.o build/boot.o -o build/lisa.bin -nostdlib

#check MyOS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot build/lisa.bin

#building the iso file
mkdir -p isodir/boot/grub
cp build/lisa.bin isodir/boot/lisa.bin
cp meta/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o build/lisa.iso isodir

#run it in qemu
qemu-system-x86_64 -cdrom build/lisa.iso
