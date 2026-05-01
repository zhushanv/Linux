//获取错误信息的三种方法
#include <stdio.h>
#include <stdlib.h> //malloc
#include <errno.h> //errno
#include <string.h> //strerror

int main(){
    // int* p = (int*)malloc(0xffffffffffff);
    // if(p == NULL){
    //     //方法一：直接输出错误码
    //     printf("Error code: %d\n", errno);
    //     //方法二：使用strerror函数获取错误信息
    //     printf("Error message: %s\n", strerror(errno));
    //     //方法三：使用perror函数直接输出错误信息
    //     perror("malloc:");
    // }
    // free(p);

    FILE* fp = fopen("textt.txt", "r");
    if(fp == NULL){
        perror("fopen:");
    }
    return 0;
}