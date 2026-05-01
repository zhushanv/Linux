#include <stdio.h>
#include <fcntl.h> //open
#include <unistd.h> //read, close
#include <string.h> //strlen

int main(){
    //打开文件
    int fd = open("./out.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    //向文件写入数据 hello world!
    write(fd, "hello world!\n", strlen("hello world!\n"));
    //修改文件读写位置--空格后
    lseek(fd, 6, SEEK_SET);
    //再次向文件写入数据linux!
    write(fd, "linux!\n", strlen("linux!\n")); //覆盖hello
    //往前移动读写指针
    if(lseek(fd, -10, SEEK_SET) == -1){
        perror("lseek");
        return -1;
    }
    write(fd, "Youhhhhhhhhhhhhhhh", strlen("You"));
    //关闭文件
    close(fd);
    return 0;
}