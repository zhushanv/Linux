//fork + exec

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    //创建子进程·
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error");
        return 1;
    }
    //子进程变身为new
    if(pid == 0){
        char* const envp[] = {"NAME=zhushan","AGE=18", NULL};
        if(execle("./new","new",NULL, envp) == -1){
            perror("execlp error");
            return -1;
        }
        return 0;
    }
    //父进程等待子进程结束
    int status;
    wait(&status);
    if(WIFEXITED(status)){
        printf("child process exited with %d\n", WEXITSTATUS(status));
    }else{
        printf("child process exited abnormally\n", WTERMSIG(status));
    }
    return 0;
}