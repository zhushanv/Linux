//基于tcp的服务器
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//网络通信相关
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <ctype.h> //toupper
#include <signal.h> //signal
#include <sys/wait.h> //waitpid

int main(){
    printf("服务器：创建socket\n");
    int sk = socket(AF_INET, SOCK_STREAM, 0);
    if(sk == -1){
        perror("socket");
        return -1;
    }
    printf("服务器：组织地址结构\n");
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    //存储时用的是小端存储方式，网络协议用的是大端的拿法，所以要转换
    ser.sin_port = htons(9999);
    //inet_addr()将点分十进制的IP地址字符串转换成网络字节序的整数
    ser.sin_addr.s_addr = inet_addr("192.168.43.144");

    printf("服务器：绑定创建的socket和地址\n");
    if(bind(sk, (struct sockaddr*)&ser, sizeof(ser)) == -1){
        perror("bind");
        return -1;
    }

    printf("服务器：监听\n");
    if(listen(sk, 5) == -1){
        perror("listen");
        return -1;
    }

    return 0;
}