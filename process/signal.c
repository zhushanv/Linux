//信号处理
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int signo){
    printf("%d process get signal %d\n",getpid() ,signo);
}
int main(){
    //忽略信号
    if(signal(SIGINT, SIG_IGN) == SIG_ERR){
        perror("signal error");
        return -1;
    } 
    //自定义信号处理函数
    if(signal(SIGINT, handler) == SIG_ERR){
        perror("signal error");
        return -1;
    } 
    //恢复默认信号
    if(signal(SIGINT, SIG_DFL) == SIG_ERR){
        perror("signal error");
        return -1;
    } 
    for(;;);
    return 0;
}