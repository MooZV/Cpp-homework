//
// Created by MooZV on 2021/4/23.
//
#include "difficult.h"

int main() {
    // 随机生成数字

    difficult d;

    // 用户交互
    printf("please input number of questions\n");
    std::cin >> d.count;
    assert(d.count > 0);

    printf("please input degree of difficulty,[1~9]\n");
    std::cin >> d.degree;

    char ch;
    printf("Do you use multiplication and division?,[Y/N]\n");
    std::cin >> ch;
    d.multiplyAndDivide(ch);

    // 开始做题
    d.exercise();

    return 0;
}