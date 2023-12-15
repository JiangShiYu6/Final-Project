#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int a, b;
    double d = 3.14159;

    printf("请输入半径和高度\n");
    scanf("%d %d", &a, &b); // 注意 scanf 的参数是字符串，应该将 &a 和 &b 放在双引号内

    printf("圆周长     ：%.2lf\n", a * 2 * d); // 修正输出格式控制符 %.2lf
    printf("圆面积     ：%.2lf\n", a * a * d); // 修正输出格式控制符 %.2lf
    printf("圆球表面积 ：%.2lf\n", 4 * d * a * a); // 修正输出格式控制符 %.2lf
    printf("圆球体积   : %.2lf\n", 4 * d * a * a * a / 3); // 修正输出格式控制符 %.2lf
    printf("圆柱体积   ：%.2lf\n", d * a * a * b); // 修正输出格式控制符 %.2lf

    return 0;
}