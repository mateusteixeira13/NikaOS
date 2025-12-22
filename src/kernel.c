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

typedef enum{
    KERNEL_SUCCESS,
    KERNEL_FAULT
} KernelStatus;

#define RELEASE "v0.52b"

/**
 * A kernel initialization function
 */
KernelStatus kernel_init(multiboot_info_t* mbd, uint32_t magic){
    x86Cli();

    InitStdio();

    if(Hal_init() == HAL_ERROR){
        Stdout("Error to initializing the HAL\n");
        return KERNEL_FAULT;
    }

    gdt_init();
    idt_init();
    pic_init();

    if(pmm_init(mbd, magic) != 0){
       Stdout("Error to initialize the PMM\n");
       return KERNEL_FAULT;
    }

    init_pages();

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
        Stdout("[SYSBOOT] Fault to init kernel\n");
        return;
    }

    Stdout_color("\nNika Kernel booted!\n", 0x0B);
    Stdout("Nika Kernel info:\n");
    kprintf("Version: %s", RELEASE);

    __bshell();
   
    for(;;){
        schedule();
        Halt();
    }
}