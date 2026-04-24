#include <stdio.h>
#include "math.h"//接口头文件
int main() {
    int a = 10, b = 5;
    int sum = add(a, b);
    int difference = sub(a, b);

    show(a, '+', b, sum);
    show(a, '-', b, difference);

    return 0;
}