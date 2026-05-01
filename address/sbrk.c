#include <unistd.h>
#include <stdio.h>
#include <stdint.h> 
int main(){
    printf("当前堆尾：%p\n", sbrk(0)); // 获取当前堆尾地址
    int *ptr1 = sbrk(sizeof(int)); // 分配一个整数大小的内存
    printf("分配一个整数后位置：%p\n", ptr1); // 获取新的堆尾地址
    *ptr1 = 100;
    double* ptr2 = sbrk(sizeof(double)); // 分配一个双精度浮点数大小的内存
    printf("分配一个双精度浮点数后的位置：%p\n", ptr2); // 获取新的堆尾地址
    *ptr2 = 3.14;

    printf("%d, %f\n", *ptr1, *ptr2);

    //手动释放内存
    sbrk(-(intptr_t)(sizeof(int) + sizeof(double))); // 将堆尾回退到初始位置，释放之前分配的内存
    printf("释放内存后堆尾：%p\n", sbrk(0)); // 获取新的堆尾地址
}