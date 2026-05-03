//父子进程间的无名管道通信
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
//不要忘记关闭管道的读端和写端
int main(){
    int pipefd[2];

    if(pipe(pipefd) == -1){
        perror("pipe1");
        exit(1);
    }

    printf("pipefd[0]:%d,pipefd[1]:%d\n", pipefd[0],pipefd[1]);
    //父进程写，子进程读
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){
      close(pipefd[1]); // 关闭写端
      printf("%d进程：接收数据:\n", getpid());

      while(1){
          char buf[64] = {};
          int res = read(pipefd[0], buf, sizeof(buf) - 1);

          if(res == -1){
              perror("read");
              return -1;
          }

          if(res == 0){
              printf("%d进程：写端已经关闭\n", getpid());
              break;
          }

          buf[res] = '\0';
          printf("%d进程收到数据：%s", getpid(), buf);
      }

      close(pipefd[0]);
      printf("%d进程：读端已经关闭\n", getpid());
      return 0;
  }

    
    close(pipefd[0]); //关闭读端
    printf("%d进程：发送数据:\n", getpid());

    while(1){
        //初始化buffer, 避免上次的数据残留造成影响
        char buf[64] = {};
        fgets(buf, sizeof(buf), stdin);
        if(write(pipefd[1], buf, sizeof(buf)) == -1){
            perror("write");
            return -1;
        }
        if(strcmp(buf, "q\n") == 0){
            break;
        }
    }
    close(pipefd[1]);
    printf("%d进程：写端已经关闭\n", getpid());
    //等待子进程退出
    wait(NULL);
    return 0;
    }
