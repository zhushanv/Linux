#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig){
    printf("%d process catch signal %d\n", getpid(), sig);
    printf("alarmed!\n");
}

int main(){
    if(signal(SIGALRM, handler)){
        perror("signal error");
        return -1;
    }
    
    int res = alarm(10); // 3秒后发送SIGALRM信号
    printf("alarm1 return %d\n", res);
    getchar();
    res = alarm(3);
    printf("alarm2 return %d\n", res);
    while(1);
    return 0;
}