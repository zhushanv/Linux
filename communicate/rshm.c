#include <stdio.h> 
#include <sys/shm.h>


int main(){
    key_t key = ftok(".", 123);
    if(key == -1){
        perror("ftok");
        return 1;
    }
    //获取共享内存, 获取·的时候参数size为0
    int shmid = shmget(key, 0, 0);
    if(shmid == -1){
        perror("shmget");
        return -1;
    }

    //共享内存映射到当前进程的地址空间
    printf("加载共享内存\n");
    getchar();
    char* p = shmat(shmid, NULL, SHM_RDONLY);
    if(p == (void*)-1){
        perror("shmat");
        return -1;
    }

    //读取共享内存
    printf("shared memory: %s\n", p);

    //解除映射
    if(shmdt(p) == -1){
        perror("shmdt");
        return -1;
    }
    return 0;
}