#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t a = fork();
    if(a == 1){
        printf("fork error\n");
        return -1;
    }
    if(a == 0){
        printf("%d进程 :child process\n", getpid());
    }else{
        printf("%d进程 :parent process\n", getpid());
    }
    return 0;
}