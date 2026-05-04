//基于TCP的服务器
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//网络通信相关
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(){
    printf("客户端：创建socket\n");
    int sk = socket(AF_INET, SOCK_STREAM, 0);
    if(sk == -1){
        perror("socket");
        return -1;
    }
    //客户端的地址信息由操作系统自动分配
    printf("客户端：组织服务器的地址结构");
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(9999);
    ser.sin_addr.s_addr = inet_addr("192.168.43.144");

    printf("客户端：连接服务器\n");
    if(connect(sk, (struct sockaddr*)&ser, sizeof(ser)) == -1){
        perror("connect");
        return -1;
    }

    printf("客户端：发送数据\n");
    while(1){
        char buf[1024] = {};
        printf("请输入：");
        fgets(buf, sizeof(buf), stdin);
        if(strcmp(buf, "\n") == 0){
            printf("客户端：退出\n");
            break;
        }
        if(send(sk, buf, strlen(buf), 0) == -1){
            perror("send");
            return -1;  
        }

        if(recv(sk, buf, sizeof(buf) - 1, 0) == -1){
            perror("recv");
            return -1;
        }
        printf("服务器回复：%s\n", buf);
    }
    
    printf("客户端：关闭socket\n");
    close(sk);
    return 0;
}
