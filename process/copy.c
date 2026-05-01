//父进程是子进程的不完全副本
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global = 10;  //数据区

int main(){
    int local = 20; //栈区
    int * heap = malloc(sizeof(int));
    *heap = 30; //堆区
    printf("%d进程：%p:%d, %p:%d, %p:%d\n", getpid(), &global, global, &local, local, heap, *heap);
    pid_t pid = fork();

    if(pid == -1){
        perror("fork error");
        return -1;
    }
    if(pid == 0){
        printf("%d子进程：%p:%d, %p:%d, %p:%d\n", getpid(), &global, ++global, &local, 
                    ++local, heap, ++*heap);
        return 0;
    } 

    sleep(1); //控制父进程在子进程之后执行
    printf("%d子进程：%p:%d, %p:%d, %p:%d\n", getpid(), &global, global, &local, 
                local, heap, *heap);
    return 0;
}