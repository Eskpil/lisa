#include "kernel.h"
#include "vga.h"

void init()
{
    struct kernel kernel = { 0 };

    kernel_append_vga(&kernel);    

    kprint(&kernel, "Hello, World!");
}
