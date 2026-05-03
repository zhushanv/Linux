#include <stdio.h>
#include <unistd.h> //getpid
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

struct msgbuf{
    long mytype;
    char text[1024];
};

int main(){
    key_t key = ftok(".", 100);
    if(key == -1){
        perror("ftok");
        return 1;
    }

    int msgid = msgget(key, 0);
    if(msgid == -1){
        perror("msgget");
        return 1;
    }

    for(;;){
        struct msgbuf buf = {};
        // 接收消息
        ssize_t res = msgrcv(msgid, &buf, sizeof(buf.text) - 1, 1, 0);
        if(res == -1){
            if(errno == EIDRM){
                printf("消息队列被删除\n");
                return 0;
            }else if(errno == E2BIG){
                printf("消息太大，接收缓冲区不够\n");
                return 1;
            }else{
                perror("msgrcv");
                return 1;
            }
           
        }
        buf.text[res] = '\0';
        printf("%d进程获取到消息队列数据: %s", getpid(), buf.text);
    }
    return 0;
}
