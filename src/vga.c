#include "types.h"
#include "colors.h"
#include "kernel.h"
#include "vga.h"

// static const int digit_ascii_codes[10] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher :
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/
uint16_t vga_entry(unsigned char ch, uint8_t fore_color, uint8_t back_color)
{
    uint16_t ax = 0;
    uint8_t ah = 0, al = 0;

    ah = back_color;
    ah <<= 4;
    ah |= fore_color;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

// clear video buffer array
void clear_vga_buffer(uint16_t** buffer, uint8_t fore_color, uint8_t back_color)
{
    uint32_t i;
    for (i = 0; i < 4096; i++) {
        (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
    }
}

// initialize vga buffer
void init_vga(struct kernel *kernel, uint8_t fore_color, uint8_t back_color)
{
    kernel->vga.buf = (uint16_t*)VGA_ADDRESS;
    clear_vga_buffer(&kernel->vga.buf, fore_color, back_color);
}

uint32_t strlen(const char* str)
{
    uint32_t length = 0;
    while (str[length])
        length++;
    return length;
}

uint32_t digit_count(int num)
{
    uint32_t count = 0;
    if (num == 0)
        return 1;
    while (num > 0) {
        count++;
        num = num / 10;
    }
    return count;
}

void itoa(int num, char* number)
{
    int dgcount = digit_count(num);
    int index = dgcount - 1;
    char x;
    if (num == 0 && dgcount == 1) {
        number[0] = '0';
        number[1] = '\0';
    } else {
        while (num != 0) {
            x = num % 10;
            number[index] = x + '0';
            index--;
            num = num / 10;
        }
        number[dgcount] = '\0';
    }
}

void kprint(struct kernel *kernel, const char* message)
{
    uint32_t index = 0;
    while (message[index]) {
        kernel->vga.buf[kernel->vga.idx++] = vga_entry(message[index], CYAN, BLACK);
        index++;
    }
}

void kprint_int(struct kernel *kernel, int num)
{
    char str_num[digit_count(num) + 1];
    itoa(num, str_num);
    kprint(kernel, str_num);
}

void kernel_append_vga(struct kernel* kernel)
{
    init_vga(kernel, WHITE, BLACK);
}
