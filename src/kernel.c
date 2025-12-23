/** 
 * I will organize this 
*/
#include <hal.h>
#include <vga.h>
#include <mem.h>
#include <stdint.h>
#include <multiboot.h>
#include <pic.h>
#include <idt.h>
#include <irq.h>
#include <heap.h>
#include <paging.h>
#include <ramfs.h>
#include <kbd.h>
#include <gdt.h>
#include <bshell.h>
#include <pit.h>
#include <vbe.h>
#include <serial.h>

typedef enum{
    KERNEL_SUCCESS,
    KERNEL_FAULT
} KernelStatus;

const char kernel_version[] = "nikakrnl-generic:052c2";

/**
 * A kernel initialization function
 */
KernelStatus kernel_init(multiboot_info_t* mbd, uint32_t magic){
    x86Cli();

    InitStdio();

    __serial();

    if(Hal_init() == HAL_ERROR){
        gdl_print("Error to initializing the HAL\n");
        return KERNEL_FAULT;
    }

    gdt_init();
    idt_init();
    pic_init();

    pit_init();

    if(pmm_init(mbd, magic) != 0){
       gdl_print("Error to initialize the PMM\n");
       return KERNEL_FAULT;
    }

    init_pages();

    gd_init(mbd, magic);

    heap_init();

    kybrd_init();

    x86Sti();

    /**
     * Now init a basic fork
     */ 
    __fork();

    /**
     * Initialize the RAM FileSystem
     */
    __initramfs();



    return KERNEL_SUCCESS;
}

/**
 * Main of kernel
 */
void kmain(multiboot_info_t* mbd, uint32_t magic){ 
    if(kernel_init(mbd, magic) == KERNEL_FAULT){
        gdl_print("[SYSBOOT] Fault to init kernel\n");
        return;
    }

    gdl_print("Kernel Booted!\n");

    for(;;){
        schedule();
        Halt();
    }
}