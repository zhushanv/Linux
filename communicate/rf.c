#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    printf("%d进程向管道读取数据\n", getpid());
    int fd = open("./fifo", O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(1);
    }
    printf("%d进程读取数据\n", getpid());
    char buf[64] = {};
    while(1){
        ssize_t res = read(fd, buf, sizeof(buf) - 1) ;
        if(res == -1){
            perror("read");
            return -1;
        } 
        if(res == 0){
            printf("%d进程：对方已关闭\n", getpid());
            break;
        }
        printf("%s",  buf);
    }
    printf("%d进程读取结束, 关闭管道文件\n", getpid());
    close(fd);
    return 0;
}