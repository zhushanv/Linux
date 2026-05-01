#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> //open
#include <string.h> //strlen

int main(){
    int fd = open("./shared.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    const char* str = "Hello, World!\n";
    //返回有符号long， size_t为无符号·long
    ssize_t size = write(fd, str, strlen(str)); // 将字符串写入文件
    if(size == -1){
        perror("write");
        close(fd);
        return -1;
    }
    printf("成功写入 %ld 字节\n", size);
    return 0;
}