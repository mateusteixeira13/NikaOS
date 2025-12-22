#ifndef VBE_H
#define VBE_H

#include <stdint.h>
#include <multiboot.h>

typedef enum{
    GSUCCESS,
    GERROR
} GD_STATUS;

void put_pixel(uint32_t x, uint32_t y, uint32_t color);
void draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
void clear(uint32_t color);
GD_STATUS gd_init(multiboot_info_t* mbd, uint32_t magic);

#endif