//进程的终止
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }

    if(pid == 0){
        printf("I am child process, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(3);
        exit(0);
    }
    int status;
    int childpid = wait(&status);
    printf("I am parent process, pid = %d, ppid = %d\n", getpid(), getppid());
    printf("childpid = %d, status = %d\n", childpid, status);

    //由状态码判断状态
    if(WIFEXITED(status)){
        printf("child process exited normally, exit code = %d\n", WEXITSTATUS(status));
    }else{
        printf("child process exited abnormally, signal = %d\n", WTERMSIG(status));
    }
    return 0;
}