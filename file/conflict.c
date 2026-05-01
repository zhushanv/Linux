#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h> //errno
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "usage: %s <text>\n", argv[0]);
        return -1;
    }

    int fd = open("./conflict.txt", O_WRONLY | O_CREAT | O_APPEND,0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    //写入之前加锁
    //F_WRLCK--非阻塞加锁； F_WRLCKW--阻塞加锁
    struct flock lock = {0};
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_start = 0;
    //加锁有阻塞加锁和非阻塞加锁
    while(fcntl(fd, F_SETLK, &lock) == -1){
       //利用全局错误errno区分出错原因
        if(errno == EACCES || errno == EAGAIN){
            printf("文件被锁定，等待....\n");
            sleep(2);
        }else{
            perror("fcntl");
            return -1;
        }
    }
    for(int i = 0; i < strlen(argv[1]); i++){
        if(write(fd, &argv[1][i], sizeof(argv[1][i])) == -1){
            perror("wirte");
            return -1;
        }
        sleep(1);
    }
    //解锁
    struct flock unlock = {0};
    unlock.l_type = F_UNLCK;
    unlock.l_whence = SEEK_SET;
    unlock.l_len = 0;
    unlock.l_start = 0;

    if(fcntl(fd, F_SETLK, &unlock) == -1){
        perror("unlock");
        return -1;
    }
    close(fd);
    return 0;
}
