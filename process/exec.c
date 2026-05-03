//创建新进程，取代旧进程
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("hello world from %d\n", getpid());
    // if(execl("./new", "new", "hello", "1222", NULL) == -1){
    //     perror("execl");
    //     exit(1);
    // }

    // if(execlp("ls", "ls", "-l", "--color=auto", NULL) == -1){
    //     perror("execlp");
    //     exit(1);
    // }

    char* const envp[] = {"NAME=ZHANGSAN", "AGE=18", NULL};
    if(execle("./new", "new", "hello", "1222", NULL, envp) == -1){
        perror("execle");
        exit(1);
    }
    //这一句不会被执行，因为上面已经替换了进程
    printf("hello world from %d\n", getpid());
    return 0;
}