//理解子进程对父进程信号的处理
//父子进程公共终端
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signo){
    printf("get signal %d\n", signo);
}

int main(){
    if(signal(SIGINT, SIG_IGN)){
        perror("signal");
        exit(1);
    }
    if(signal(SIGQUIT, sig_handler)){
        perror("signal");
        exit(1);
    }

    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        exit(1);
    }

    if(pid == 0){
        printf("child process: %d\n", getpid());
        for(;;);
    }else{
        sleep(1);
        printf("parent process: %d\n", getpid());
    }
    printf("结束运行\n");
    return 0;
}