#ifndef KERNEL_VGA_H_
#define KERNEL_VGA_H_

#include "kernel.h"

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

void kprint(struct kernel *kernel, const char *message);
void kprint_int(struct kernel *kernel, int num);

void kernel_append_vga(struct kernel *kernel);

#endif // KERNEL_VGA_H_
