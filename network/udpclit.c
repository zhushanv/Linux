//基于udp的服务端
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <string.h>
#include <unistd.h>

int main(){
    int sk = socket(AF_INET, SOCK_DGRAM, 0);
    if(sk == -1){
        perror("socket");
        return 1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = inet_addr("192.168.43.144");

    while(1){
        char buf[1024] = {};
        printf("请输入要发送的内容：");
        fgets(buf, sizeof(buf), stdin);

        if(strcmp(buf, "\n") == 0){
            break;
        }
        if(sendto(sk, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr)) == -1){
            perror("sendto");
            return 1;
        }

        if(recv(sk, buf, sizeof(buf) - 1, 0) == -1){
            perror("recvfrom");
            return 1;
        }
        printf("服务器回复：%s\n", buf);
    }
    close(sk);
    return 0;
}




