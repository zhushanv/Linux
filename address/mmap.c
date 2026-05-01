//建立虚拟内存到物理内存的映射
/**
 * #include <sys/mman.h>

     void *
     mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
    从内存空间中申请一块内存，用于虚拟内存到物理内存的映射。
    参数说明：
    - addr：建议的映射地址(即虚拟内存的起始地址)，通常设置为NULL，让系统选择合适的地址。
    - len：映射的长度，必须是页面大小的整数倍。
    - prot：映射区域的保护标志，常用的值包括：
        PROT_READ：映射区域可读。
        PROT_WRITE：映射区域可写。  
        PROT_EXEC：映射区域可执行。
        PROT_NONE：映射区域不可访问。
    - flags：映射区域的类型和选项，常用的值包括：
        MAP_SHARED：映射区域可被其他进程共享。
        MAP_PRIVATE：映射区域私有，修改不会影响其他进程。
        MAP_ANONYMOUS：映射区域不与任何文件关联，通常用于匿名映射。
    - fd：文件描述符，只有在映射文件时才需要，对于匿名映射，设置为-1。
    - offset：文件映射的偏移量，必须是页面大小的整数倍。
    返回值：成功时返回映射区域的起始地址，失败时返回MAP_FAILED（-1） ，并设置errno以指示错误原因。

    int munmap(void *addr, size_t len);
    解除之前通过mmap创建的内存映射。
    参数说明：
    - addr：要解除映射的内存区域的起始地址，必须是之前通过mmap返回的地址。
    - len：要解除映射的内存区域的长度，必须与mmap时指定的长度相同。
    返回值：成功时返回0，失败时返回-1，并设置errno以指示错误原因。
 */

 //内存映射的建立和解除
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void){
    //系统中一页的大小不一定是4096字节，可以通过sysconf(_SC_PAGESIZE)获取系统页面大小
    long page_size = sysconf(_SC_PAGESIZE);
    printf("System page size: %ld bytes\n", page_size);
    size_t length = page_size*2; // 映射长度，必须是页面大小的整数倍
    char* start = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,0,0);

    if(start == MAP_FAILED){
        perror("mmap");
        return -1;
    }

    //字符串拷贝
    strcpy(start, "Hello, mmap!");
    printf("Mapped memory content: %s\n", start);

    if(munmap(start, length/2) == -1){ //先释放一页的内存
        perror("munmap");
        return -1;
    }
    char * start2 = start + length/2;
    strcpy(start2, "This is the second half of the mapped memory.");
    printf("Mapped memory content after munmap: %s\n", start2);

    if(munmap(start2, length/2) == -1){
        perror("munmap");
        return -1;
    }

    //段错误
    // printf("Mapped memory content after munmap: %s\n", start2);
    
    return 0;
}