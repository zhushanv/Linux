//建立虚拟地址到文件的映射
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int main(){
    //打开文件
    int fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(fd == -1){
        perror("open");
        return 1;
    }

    if(ftruncate(fd, 4096) == -1){
        perror("ftruncate");
        close(fd);
        return 1;
    }
 
    //建立映射，addr返回虚拟内存首地址
    char *addr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED){
        perror("mmap");
        close(fd);
        return 1;
    }

    //修改映射内容
    strcpy(addr, "hello, mmap!");
    printf("addr: %s\n", addr);

    //解除映射
    munmap(addr, 4096);

    //关闭文件  
    close(fd);
    return 0;
}
