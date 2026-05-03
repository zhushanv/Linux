//exec创建的新进程的可执行文件
#include <stdio.h> 
#include <unistd.h>

int main(int argc, char *argv[], char* envp[]){
    printf("This is a new process\n");
    printf("PID: %d\n", getpid());
    printf("命令行参数:\n");
    for(int i = 0; argv[i] != NULL; i++){
        printf("%s\n", argv[i]);
    }
    printf("环境变量:\n");
    for(int i = 0; envp[i] != NULL; i++){
        printf("%s\n", envp[i]);
    }


    return 0;
}