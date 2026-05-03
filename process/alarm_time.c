#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

void handler(int sig){
    //打印当前时间
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    //每次打印之前，清空缓冲区输出
    // if(system("clear") == -1){
    //     perror("system error");
    //     exit(-1);
    // }
    char buff[20];
    strftime(buff, sizeof(buff), "%H:%M:%S", t);
    printf("\r%s", buff); //\r表示回车，回到行首
    alarm(1);
}

int main(){
    //关输出缓冲区，所以就算不用换行符就能打印输出
    setbuff(stdout, NULL);
    if(signal(SIGALRM, handler)){
        perror("signal error");
        return -1;
    }
    handler(SIGALRM);
    while(1);
    return 0;
}