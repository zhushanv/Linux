//重定向操作
#include <stdio.h>
#include <unistd.h> //close
#include <fcntl.h> //open

int main(){
    //修改文件描述符1（标准输出），将其重定向到一个文件
    close(STDOUT_FILENO); // 关闭标准输出
    int fd = open("./out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664); // 打开或创建文件
    printf("fd = %d\n", fd); // 输出文件描述符，应该是1
    return 0;
}