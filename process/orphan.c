//验证孤儿进程会被孤儿院进程回收

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int a = fork();
    if(a == -1){
        perror("fork error");
        return -1;
    }
    if(a == 0){
        printf("My father: %d\n", getppid());
        sleep(2);
        printf("My father: %d\n", getppid());
        return 0;
    }

    sleep(1);
    printf("father process exit\n");
    return 0;
}