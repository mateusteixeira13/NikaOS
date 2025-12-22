#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <multiboot.h>

typedef enum {
    HAL_SUCESS,
    HAL_ERROR
} HAL_Status;

// CPU Operations
void x86Cli();
void x86Sti();
void Halt();

// Port x86 Operations
void x86write(uint16_t port, uint8_t val);
uint8_t x86read(uint16_t port);
void x86IO_wait();

void x86IRQ_setmask(uint32_t irq_line);      
void x86IRQ_clearmask(uint32_t irq_line);     

/**
 * HAL initialization
 */
HAL_Status Hal_init();


#endif