//实现退出处理函数
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_handler(){
    printf("我是先注册的退出处理函数\n");
}

void exit_handler2(int status, void *arg){
    printf("status  = %d\n", status);
    printf("arg = %p\n", arg);
}

int fun(){
    printf("我是fun函数\n");
    // exit(0);
    return 10;
}
int main(){
    atexit(exit_handler);
    on_exit(exit_handler2, "我是后注册的退出处理函数");
    printf("fun函数%d\n",fun());
    return 0;
}