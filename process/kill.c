//用kill函数对相应的进程发送信号
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

void handler(int sig){
    printf("%d进程捕获到%d信号\n", getpid(), sig);
}
int main(){
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }

    if(pid == 0){
        printf("%d进程创建成功\n", getpid());
        // signal(SIGINT, handler);
        while(1);
        return 0;
    }

    getchar();
    if(kill(pid, SIGINT) == -1){
        perror("kill error");
        exit(1);
    }
    //之后被收尸之后，进程才会不存在，否则为僵尸
    wait(NULL);
    if(kill(pid, 0) == -1){
        if(errno == ESRCH){
            printf("进程%d不存在\n", pid);
        }else{
            perror("kill error");
            return -1;
        }
    }else{
        printf("进程%d存在\n", pid);
    }
    return 0;
}
