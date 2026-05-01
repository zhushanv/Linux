#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd = open("./trunc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        perror("open");
        return -1;
    }
    char* buf = "abcde";
    if(write(fd, buf, strlen(buf)) == -1){
        perror("write");
        return -1;
    }

    
    close(fd);
    return 0;
}