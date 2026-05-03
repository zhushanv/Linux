#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_handler(int sig){
    printf("%d进程收到信号%d\n", getpid(), sig);
    sleep(3);
    printf("%d进程恢复运行\n", getpid());
}
int main(){
    if(signal(SIGINT, sig_handler) == SIG_ERR){
        perror("signal error");
        return 1;
    }
    printf("%d进程开始pause\n", getpid());
    int res = sleep(10);
    printf("%d进程pause返回%d\n", getpid(), res);
    return 0;
}