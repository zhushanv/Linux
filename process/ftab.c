//子进程和父进程会操纵同一个文件表
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    //父进程打开文件
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("open");
        return -1;
    }
    //父进程向文件中写入hello world,文件的读写位置为12
    //sizeof会包含字符串末尾的结尾符号'\0'， 该用strlen，读取有效字符串的长度
    if(write(fd, "hello world", strlen("hello world")) == -1){
        perror("write");
        return -1;
    }
    //创建子进程
    int a = fork();
    if(a == -1){
        perror("fork");
        close(fd);
        return -1;
    }
    //子进程修改读写位置为6
    if(a == 0){
        if(lseek(fd, 6, SEEK_SET) == -1){
            perror("lseek");
            close(fd);
            return -1;
        }
        close(fd);
        return 0;
    }
    //父进程向文件中写入linux,并打印内容
    wait(NULL);
    if(write(fd, "linux", strlen("linux")) == -1){
        perror("write");
        close(fd);
        return -1;
    }
    char buf[20];
    if(lseek(fd, 0, SEEK_SET) == -1){
        perror("lseek");
        close(fd);
        return -1;
    }

    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if(n == -1){
        perror("read");
        close(fd);
        return -1;
    }
    buf[n] = '\0';
    printf("%s\n", buf);
    close(fd);
    return 0;
}
