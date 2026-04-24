#include <stdio.h>
#include <stdlib.h>

// 常量/非常量 + 全局/局部 + 静态/非静态 + 初始化/未初始化变量
const int const_global = 10;
int init_global = 20; // 初始化全局变量
int uninit_global;    // 未初始化全局变量

static const int const_file_static = 15;
static int init_file_static = 25;
static int uninit_file_static;

void normal_func(void)
{
}

static void static_func(void)
{
}

void print_addr(const char *name, const void *addr, const char *area)
{
    printf("%-24s %p  %s\n", name, addr, area);
}

void show_proc_maps(void)
{
#ifdef __linux__
    char line[256];
    FILE *fp = fopen("/proc/self/maps", "r");

    if (fp == NULL) {
        perror("fopen /proc/self/maps");
        return;
    }

    puts("\n========== /proc/self/maps ==========");
    while (fgets(line, sizeof(line), fp) != NULL) {
        fputs(line, stdout);
    }

    fclose(fp);
#else
    puts("\n/proc/self/maps is Linux-specific. Run this program on Linux to see the process memory map.");
#endif
}

int main(int argc, char *argv[], char *envp[])
{
    const static int const_static = 30;
    static int init_static = 40; // 初始化静态变量
    static int uninit_static;    // 未初始化静态变量
    const int const_local = 45;
    int local_var = 50; // 局部变量

    char *string = "hello"; // 字符串常量
    int *heap_var = (int *)malloc(sizeof(int)); // 堆变量

    if (heap_var == NULL) {
        perror("malloc");
        return 1;
    }
    *heap_var = 60;

    puts("========== user space address sample ==========");
    print_addr("main", (const void *)main, "text/code segment");
    print_addr("normal_func", (const void *)normal_func, "text/code segment");
    print_addr("static_func", (const void *)static_func, "text/code segment");

    print_addr("string literal", string, "read-only data, usually .rodata");
    print_addr("&const_global", &const_global, "global const, usually .rodata");
    print_addr("&const_file_static", &const_file_static, "file-scope static const, usually .rodata");
    print_addr("&const_static", &const_static, "local static const, usually .rodata");

    print_addr("&init_global", &init_global, "initialized global, .data");
    print_addr("&init_file_static", &init_file_static, "initialized file-scope static, .data");
    print_addr("&init_static", &init_static, "initialized local static, .data");

    print_addr("&uninit_global", &uninit_global, "uninitialized global, .bss");
    print_addr("&uninit_file_static", &uninit_file_static, "uninitialized file-scope static, .bss");
    print_addr("&uninit_static", &uninit_static, "uninitialized local static, .bss");

    print_addr("heap_var", heap_var, "heap, allocated by malloc");
    print_addr("&heap_var", &heap_var, "stack, local pointer variable");
    print_addr("&local_var", &local_var, "stack, normal local variable");
    print_addr("&const_local", &const_local, "stack, const local variable");
    print_addr("&argc", &argc, "stack, function parameter");
    print_addr("argv", argv, "stack area, argument vector");
    print_addr("argv[0]", argv[0], "stack area, argument string");
    print_addr("envp", envp, "stack area, environment vector");
    print_addr("envp[0]", envp[0], "stack area, environment string");

    show_proc_maps();

    free(heap_var);
    return 0;
}
