//阻塞和非阻塞

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }
    if(pid == 0){
        printf("子进程将进入睡眠\n");
        sleep(5);
        return 0;
    }

    while(waitpid(pid, NULL, WNOHANG) != pid){
        printf("等待子进程结束\n");
        sleep(1);
    }
    printf("子进程结束\n");
    return 0;
}