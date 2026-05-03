//消息队列发送消息
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

struct msgbuf{
    long mytype;
    char text[1024];
};
int main(){
    //合成键
    printf("%d进程合成键\n", getpid());
    key_t key = ftok(".", 100);
    if(key == -1){
        perror("ftok");
        return 1;
    }
    //创建消息队列
    printf("%d进程创建消息队列\n", getpid());
    int msgid = msgget(key, IPC_CREAT| IPC_EXCL | 0664);
    if(msgid == -1){
        perror("msgget");
        return 1;
    }

    //发送消息
    printf("%d进程发送消息\n", getpid());
    for(;;){
        struct msgbuf msg = {1, " "};
        printf("请输入要发送的消息：");
        //因为fgets不经过缓冲区，所以会包含换行符
        fgets(msg.text, sizeof(msg.text), stdin);
        if(strcmp(msg.text, "\n") == 0){
            break;
        }
        //加1是为了算上‘\0’
        if(msgsnd(msgid, &msg, strlen(msg.text) + 1, 0) == -1){
            perror("msgsnd");
            return 1;
        }
    }

    //删除消息队列
    printf("%d进程删除消息队列\n", getpid());
    if(msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        return 1;
    }
    return 0;
}
