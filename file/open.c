#include <stdio.h>
#include <fcntl.h> //open
#include <unistd.h> //close


int main(){
    int fd = open("./open.txt", O_RDWR | O_CREAT, 0777);
    if(fd == -1){
        perror("open");
        return -1;
    }

    printf("文件描述符：%d\n", fd);
    close(fd);
    return 0;
}