#include <vga.h>
#include <stdint.h>
#include <stddef.h>
#include <lib.h>

char cmdbuf[250];
size_t cmd_len = 0;

void shell_exec(const char* cmd){
    if (strcmp(cmd, "sysinfo") == 0){
        Stdout("\nKernel name: Nika Kernel\n");
        Stdout("Model: nikakrnl-generic:052b\n");
        Stdout("Version v0.52-b\n");
        return;
    } 

    else if(strcmp(cmd, "info") == 0){
        Stdout("\nbshell - Basic Shell v0.1\n");
        return;
    }

    else if(strcmp(cmd, "clear") == 0){
        StdioClean();
        return;
    }

    else if(strcmp(cmd, "whoami") == 0){
        Stdout("\nUser\n");
        return;
    }
    
    else if(strcmp(cmd, "help") == 0){
        Stdout("\nAll commands:\n");
        Stdout("sysinfo - system info\n");
        Stdout("info - shell info\n");
        Stdout("clear - clear screen\n");
        Stdout("whoami - print the user\n");
        return;
    }
    
    kprintf("\nUnknown command\n");
}

void __bshell(){
    StdioClean();
    Stdout("user/ ~ ");
}