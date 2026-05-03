//向共享内存写入数据
#include <stdio.h> //printf
#include <string.h> //strcpy
// #include <unistd.h> 
#include <sys/shm.h> //shmget, shmat, shmdt, shmctl

int main(){
    //合成键
    printf("合成键\n");
    key_t key = ftok(".", 123);
    if(key == -1){
        perror("ftok error");
        return 1;
    }
    //创建共享内存
    printf("创建共享内存\n");
    int shmid = shmget(key, 4096, IPC_CREAT| IPC_EXCL| 0664);
    if(shmid == -1){
        perror("shmget error");
        return 1;
    }

    //加载共享内存
    printf("加载共享内存\n");
    getchar();
    char* p = shmat(shmid, NULL, 0);
    if(p == (void*)-1){
        perror("shmat error");
        return 1;
    }
    //写入数据
    printf("写入数据\n");
    strcpy(p, "hello, world");
    //释放共享内存
    printf("释放共享内存\n");
    getchar();
    if(shmdt(p) == -1){
        perror("shmdt error");
        return 1;
    }
    //销毁共享内存
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
        perror("shmctl error");
        return 1;
    }
    return 0;
}