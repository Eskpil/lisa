#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "types.h"

struct kernel {
    struct {
        uint16_t* buf;
        size_t idx;
    } vga;
};

#endif // KERNEL_KERNEL_H_
