#ifndef VGA_H
#define VGA_H


void InitStdio();
void Stdout_color(const char *str, unsigned int color);
void Stdout(const char *str);
void StdioClean_color();
void StdioClean();
int kprintf(const char *fmt, ...);
void putchar(char c);
void Stdioback(void);
int atoi(const char* str);

#define panic(str) Stdout_color(str, 0x04)
#define INFO(str) kprintf("[INFO] " str);
#define WARN(str) kprintf("[WARN] ", str);
#endif