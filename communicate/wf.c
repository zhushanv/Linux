#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    printf("%d进程创建管道文件\n", getpid());
    if(mkfifo("./fifo", 0664)){
        perror("mkfifo");
        return -1;
    }
    printf("%d进程打开管道文件\n", getpid());
    int fd = open("./fifo", O_WRONLY);
    if(fd == -1){
        perror("open");
        return -1;
    }
    printf("%d进程写入管道文件\n", getpid());
    char buf[64] = {};
    while(fgets(buf, sizeof(buf), stdin)){
        if(strcmp(buf, "q\n") == 0){
            break;
        }
        write(fd, buf, sizeof(buf));
    }
    
    printf("%d进程关闭管道文件\n", getpid());
    close(fd);
    printf("%d进程删除管道文件\n", getpid());
    if(unlink("./fifo") == -1){
        perror("unlink");
        return -1;
    }
    return 0;
}