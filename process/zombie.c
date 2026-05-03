//验证僵尸进程，父进程不回收子进程资源

#include <stdio.h>
#include <unistd.h>

int main(){
    int a = fork();
    if(a == 0){
        printf("child pid = %d\n",getpid());
        return 0;
    }   

    sleep(10);
    return 0;
}