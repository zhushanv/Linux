#include <stdio.h>
#include <fcntl.h> //open
#include <unistd.h> //read, close
#include <string.h> //strlen

int main(){
    int fd = open("./shared.txt", O_RDONLY);
    if(fd == -1){
        perror("open");
        return -1;
    }
    char buffer[100];
    //单独的指针变量没有分配内存空间，无法存储数据，导致段错误
    // char* buffer; 
    //预留一位存'\0'
    //strlen(buffer)计算的是buffer中有效字符串的长度，初始为0
    //sizeof计算的是buffer所占的内存大小
    ssize_t size = read(fd, buffer, sizeof(buffer) - 1); // 从文件中读取数据到缓冲区
    printf("实际读取的字符串长度：%ld\n", size);
    printf("读取的字符串：%s", buffer);
    return 0;
}