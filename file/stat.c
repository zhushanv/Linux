#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

//通过stat()函数拿到hello.c的元数据，存储进变量struct stat st中
//其中有成员变量st.st_mode, 变量类型为整数，不便于理解
//mtos（）函数将其转换为可读性强的字符串

//如果程序想返回局部变量，避免返回空指针的方法是在局部变量前加static
//static延长生命周期
/**
 * 将文件模式(mode_t)转换为字符串表示
 * @param m 文件模式，包含文件类型和权限信息
 * @return 返回一个静态字符串，表示文件类型的权限，格式如"drwxr-xr-x"
 */
char* mtos(mode_t m){
    static char s[11];  // 静态字符数组，用于存储结果字符串，长度为10个字符+1个结束符

    
    // 判断文件类型并设置第一个字符
    if(S_ISDIR(m)){      // 如果是目录
        s[0] = 'd';
    }else if(S_ISLNK(m)){ // 如果是符号链接
        s[0] = 'l';
    }else if(S_ISSOCK(m)){ // 如果是套接字
        s[0] = 's';
    }else if(S_ISBLK(m)){ // 如果是块设备
        s[0] = 'b';
    }else if(S_ISFIFO(m)){ // 如果是命名管道
        s[0] = 'p';
    }else if(S_ISCHR(m)){ // 如果是字符设备
        s[0] = 'c';
    }else{               // 其他情况（普通文件）
        s[0] = '-';
    }



    // 添加用户权限位（rwx）
    strcat(s, (m & S_IRUSR) ? "r" : "-");  // 用户读权限
    strcat(s, (m & S_IWUSR) ? "w" : "-");  // 用户写权限
    strcat(s, (m & S_IXUSR) ? "x" : "-");  // 用户执行权限

    
    // 添加组权限位（rwx）
    strcat(s, (m & S_IRGRP) ? "r" : "-");  // 组读权限
    strcat(s, (m & S_IWGRP) ? "w" : "-");  // 组写权限
    strcat(s, (m & S_IXGRP) ? "x" : "-");  // 组执行权限

    
    // 添加其他用户权限位（rwx）
    strcat(s, (m & S_IROTH) ? "r" : "-");  // 其他用户读权限
    strcat(s, (m & S_IWOTH) ? "w" : "-");  // 其他用户写权限
    strcat(s, (m & S_IXOTH) ? "x" : "-");  // 其他用户执行权限
    return s;  // 返回生成的权限字符串
}

//时间转换
char* ttos(time_t t){
    static char time[20];
    struct tm* p = localtime(&t);
    //sprintf将格式化的数据写入字符串
    sprintf(time, "%d-%02d-%02d %02d:%02d:%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    return time;  // 添加返回语句
}

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "用法：./stat <文件名>\n");
        return -1;
    }
    
    struct stat st; //用来输出文件的元数据
    if(stat(argv[1], &st) == -1){
        perror("stat");
        return -1;
    }

    printf("     设备ID：%d\n", st.st_dev);
    printf("    硬链接数：%hd\n", st.st_nlink);
    printf("    文件大小：%lld\n", st.st_size);
    printf("     用户ID：%u\n", st.st_uid);
    printf("       组ID：%u\n", st.st_gid);
    printf("    文件权限：%s\n", mtos(st.st_mode));
    printf("  IO字节块数：%d\n", st.st_blksize);
    printf("  文件块数量：%lld\n", st.st_blocks);
    printf(" 最后访问时间：%s\n", ttos(st.st_atime));
    printf(" 最后修改时间：%s\n", ttos(st.st_mtime));
    printf("最后状态改变时间：%s\n", ttos(st.st_ctime));
    
    return 0;
}