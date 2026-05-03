//父进程利用信号17（SIGCHLD）来处理子进程的退出
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

//如果在信号处理函数处理期间， 如果有多个相同的信号
//到达， 只保留一个，其余t统统丢弃。
void sigchild(int signo){
    //模拟信号处理函数处理周期长
    sleep(2);  // 休眠2秒，模拟信号处理函数执行时间较长的情况
    int cnt = 0;
    while(1){
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        if(pid == -1){
            if(errno == ECHILD){
                break;
            }else{
                perror("wait error");
                exit(1);
            }
        }else if(pid == 0){
            printf("no child process exit\n");
            break;
        }
        cnt++;
    }
    printf("%d process recycles %d children\n", getpid(), cnt);  // 打印父进程PID和被回收的子进程PID
}
int main(){
    if(signal(SIGCHLD, sigchild) == SIG_ERR){
        perror("signal error");
        return -1;
    }
    for(int i = 0; i < 6; i++){
        pid_t pid = fork();
        if(pid == -1){
            perror("fork error");
            return -1;
        }
        if(pid == 0){
            printf("child pid = %d\n", getpid());
            sleep(1);
            if(i == 5){
                sleep(5); ///模拟有一个子进程执行时间过长
            }
            exit(0);
        }
    }

    while(1){
        sleep(1);
        printf("waiting child process exit\n");
    }
    return 0;
}