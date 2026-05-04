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
#include <errno.h> //errno

//父进程收到子进程退出的信号时，调用该函数回收子进程资源，信号机制可以使其高效地处理收尸的过程
void sig_handler(int singo){
    //回收多个子进程，采用非阻塞循环收尸
    while(1){
        int res = waitpid(-1, NULL, WNOHANG);
        if(res == -1){
            if(errno == ECHILD){
                printf("子进程全部回收完毕\n");
                return;
            }else{
                perror("waitpid");
                return;
            }
        }
        if(res == 0){
            printf("没有子进程退出\n");
            return;
        }
        printf("回收了一个子进程，pid = %d\n", res);
    }
}
int main(){

    if(signal(SIGCHLD, sig_handler) == SIG_ERR){
        perror("signal");
        return -1;  
    }
    
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

    while(1){
        printf("服务器：等待客户端连接\n");
        struct sockaddr_in cli; //客户端地址结构
        socklen_t len = sizeof(cli); //客户端地址结构大小
        int conn = accept(sk, (struct sockaddr*)&cli, &len); //阻塞等待客户端连接
        if(conn == -1){
            perror("accept");
            return -1;
        }

        printf("服务器接收到收到%s:%hu的客户端的连接, 创建子进程连接\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
        //创建子进程处理客户端的请求
        pid_t pid = fork();
        if(pid == -1){
            perror("fork");
            return -1;
        }
        if(pid == 0){
            close(sk); //子进程不需要监听socket
            while(1){
                //接收客户端发送的小写数据串
                char buf[1024] = {0};
                ssize_t res = read(conn, buf, sizeof(buf) - 1);
                if(res == -1){
                    perror("read");
                    return -1;
                }
                if(res == 0){
                    printf("客户端断开连接\n");
                    break;
                }
                //转大写
                for(int i = 0; i < res; i++){
                    buf[i] = toupper(buf[i]);
                }
                //回传给客户端
                if(write(conn, buf, res) == -1){
                    perror("write");
                    return -1;
                }
            }
            return 0; //子进程退出
        }
        close(conn); //父进程不需要处理客户端的请求
    }

    close(sk);
    return 0;
}