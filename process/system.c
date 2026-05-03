//运用system函数
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int s;
    s = system("ls -l");
    if(s == -1){
        perror("system error");
        exit(1);
    }
    if(WIFSIGNALED(s)){
        printf("command error, error signal:%d\n", WTERMSIG(s));
    }else{
        printf("command success\n");
    }
    return 0;
}