#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//一个char八个字节
void printByte(char byte){
    for(int i = 7; i >= 0; i--){
        printf("%d", byte & (1 << i) ? 1 : 0);
    }
    printf(" ");
}
//打印一块存储区里所有比特位打印出来
//为了函数更加通用， 函数的参数不但要有存储区首地址(void* 接任意类型指针)，
//还要有存储区的长度（字节为单位）
void printm(void* buff , size_t len){
    //倒序打印，因为存储区是从低地址到高地址存储的
    for(int i = len - 1; i >= 0; i--){
        //把 buff 转成 char *，也就是“字符指针”或“字节指针”。
        //这样就能一次只访一个字节的内容了
        printByte(((char*)buff)[i]);
        if((len - i) % 8 == 0){
            printf("\n");
        }
    }
    printf("\n");
}
/*
 * 主函数
 * 功能：演示信号集的基本操作
 */
int main(){
    sigset_t set;
    //初始化信号集
    sigemptyset(&set);
    //打印set集合, macos上是4字节的set
    printm(&set, sizeof(set));

    //将信号 SIGINT 添加到信号集 set 中
    sigaddset(&set, SIGINT);
    //打印set集合
    printm(&set, sizeof(set));
    return 0;
}