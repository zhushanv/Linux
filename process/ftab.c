//子进程和父进程会操纵同一个文件表
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    //父进程打开文件
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    //父进程向文件中写入hello world,文件的读写位置为12
    write(fd, "hello world", sizeof("hello world"));
    //创建子进程
    int a = fork();
    //子进程修改读写位置为6
    if(a == 0){
        lseek(fd, 6, SEEK_SET);
        return 0;
    }
    //父进程向文件中写入linux,并打印内容
    sleep(1);
    write(fd, "linux", sizeof("linux"));
    char buf[20];
    read(fd, buf, sizeof(buf));
    printf("%s\n", buf);
    return 0;
}