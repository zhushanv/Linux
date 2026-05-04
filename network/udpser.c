//基于udp的服务器
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(){
    printf("服务器：创建socket\n");
    int sk = socket(AF_INET, SOCK_DGRAM, 0);
    if(sk == -1){
        perror("socket");
        return 1;
    }

    printf("服务器：绑定端口\n");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = inet_addr("192.168.43.144");

    if(bind(sk, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        perror("bind");
        return 1;
    }

    while(1){
        //UDP是无连接的，所以不需要accept，直接recvfrom就可以了
        char buf[1024] = {};
        struct sockaddr_in cli;
        //不初始化cli，会报错，准备缓冲区
        socklen_t len = sizeof(cli);
        int n = recvfrom(sk, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&cli, &len);
        if(n == -1){
            perror("recvfrom");
            return 1;
        }

        for(int i = 0; i < n; i++){
            buf[i] = toupper(buf[i]);
        }

        if(sendto(sk, buf, n, 0, (struct sockaddr*)&cli, len) == -1){
            perror("sendto");
            return 1;
        }
    }

    close(sk);
    return 0;
}