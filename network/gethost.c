#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("usage: %s hostname\n", argv[0]);
        return 1;
    }

    struct hostent *host = gethostbyname(argv[1]);
    if(host == NULL){
        herror("gethostbyname");
        return 1;
    }

    if(host->h_addrtype != AF_INET || host->h_length != sizeof(struct in_addr)){
        printf("只支持IPv4地址\n");
        return 1;
    }

    printf("主机名: %s\n", host->h_name);
    printf("主机别名表：\n");
    for(char**p = host->h_aliases; *p != NULL; p++){
        printf("\t%s\n", *p);
    }
    printf("IP地址表：\n");
    for(char** p = host->h_addr_list; *p != NULL; p++){
        struct in_addr addr;
        char ip[INET_ADDRSTRLEN];

        memcpy(&addr, *p, sizeof(addr));
        if(inet_ntop(AF_INET, &addr, ip, sizeof(ip)) != NULL){
            printf("\t%s\n", ip);
        }
    }

    return 0;
}
