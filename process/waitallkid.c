//回收多个子进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
    pid_t pid;
    for(int i = 0; i < 5; i++){
        pid = fork();
        if(pid == -1){
            perror("fork error");
            exit(1);
        }
        if(pid == 0){
            sleep(1 + i);
            printf("child %d exit\n", getpid());
            return 0;
        }
    }

    for(;;){
        int status;
        pid_t wpid = wait(&status);
        if(wpid == -1){
            //判断还有没有子进程
            if(errno == ECHILD){
                printf("no child\n");
                break;
            }
            perror("wait error");
            return -1;
        }
        printf("parent wait child %d exit\n", wpid);
    }
    return 0;
}