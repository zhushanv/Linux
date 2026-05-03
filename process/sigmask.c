//演示信号屏蔽
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void updatedb(){
    printf("update database\n");
    sleep(8);
    printf("update database success\n");
}

void sig_handler(int signo){
    printf("%dprocess is handling signal %d\n", getpid(), signo);
}

int main(){
    int sigint = 50;
    if(signal(38, sig_handler) == SIG_ERR){
        perror("signal error");
        return -1;
    }
    //对2号信号屏蔽
    printf("屏蔽信号SIGINT\n");
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, 38);
    if(sigprocmask(SIG_BLOCK, &set, NULL) == -1){
        perror("sigprocmask error");
        return -1;
    }
    //调用子进程发送信号
    pid_t pid = fork();
    if(pid == 0){
        sleep(1);
        for(int i = 0; i < 3; i++){
            printf("%d process is sending signal %d\n", getpid(), 38);
            if(kill(getppid(), 38) == -1){
                perror("kill error");
                return -1;
            }
        }
        return 0;
    }
    updatedb();
    //解除屏蔽
    printf("解除屏蔽\n");
    if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1){
        perror("sigprocmask error");
        return -1;
    }
    //收尸
    wait(NULL);
    return 0;
}