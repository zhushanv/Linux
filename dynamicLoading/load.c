//动态库的动态加载
#include <stdio.h>
#include <dlfcn.h>

int main(){
    //加载动态库
    void* handle = dlopen("../math/shared/libmath.so", RTLD_LAZY);
    if(handle == NULL){
        //用标准错误输出打印错误信息，可以避免因为缓冲区的原因看不到错误信息
        fprintf(stderr, "dlopen: %s\n", dlerror());
        return -1;
    }

    //获取函数的地址, 函数指针必须与函数的类型匹配，否则会导致未定义行为
    int (*add)(int, int) = dlsym(handle, "add");
    if(add == NULL){
        fprintf(stderr, "dlsym add: %s\n", dlerror());
        dlclose(handle);
        return -1;
    }

    int (*sub)(int, int) = dlsym(handle, "sub");
    if(sub == NULL){
        fprintf(stderr, "dlsym sub: %s\n", dlerror());
        dlclose(handle);
        return -1;
    }

    void (*show)(int, char, int, int) = dlsym(handle, "show");
    if(show == NULL){
        fprintf(stderr, "dlsym show: %s\n", dlerror());
        dlclose(handle);
        return -1;
    }
    //调用函数
    int a = 10, b = 5;
    show(a, '+', b, add(a, b));
    show(a, '-', b, sub(a, b));
    
    //关闭动态库, 释放内存资源
    dlclose(handle);
    return 0;
}