//
// Created by MooZV on 2021/4/23.
//

#ifndef ALGORITHM_DIFFICULT_H
#define ALGORITHM_DIFFICULT_H

#include <cstdlib>
#include "TicToc.h"
#include <cassert>
#include <vector>
#include <math.h>

struct wrongQuestion {
    std::string ques;
    int ans;
};


// 定义一个难易程度的结构体
class difficult {
    inline void generate(int &a, int &b) {
        std::srand(time(NULL));
        a = rand() % (rangeR - rangeL + 1) + rangeL;
        b = rand() % (rangeR - rangeL + 1) + rangeL;
    };

    inline int generate() {
        std::srand(time(NULL));
        return rand() % (rangeR - rangeL + 1) + rangeL;
    };

    int rangeL;
    int rangeR; // [rangl,rangeR]
    TicToc *t; // 计时器
public:
    int count; // 统计题目总数量
    size_t degree; // 标记等级
    bool flag; // 标记是否用乘除法
    std::vector<std::string> wrong;

    // 构造函数
    difficult() : t(new TicToc) {
        rangeL = 0;
        rangeR = 99;
        count = 10;
        flag = false;
        degree = 1;
    }

    ~difficult() = default;

    // 扩大范围
    void extenRange() {
        rangeL *= degree;
        rangeR *= degree;
    }

    // 是否使用乘除
    void multiplyAndDivide(char &c) {
        flag = (c == 'Y' || c == 'y') ? true : false;
    }

    // 做题
    void exercise() {
        for (size_t i = 0; i < count; ++i) {
            // 随机生成两个数字
            int _a, _b;
            generate(_a, _b);

            float outAns = 0.0f; // 正确答案
            std::string w; // 记录错题

            // 随机生成一个数，截取后两位/一位
            int temp = generate();
            if (flag) { // 用乘除就四个判断
                temp &= 0x11;
            } else {    // 不用乘除就两个判断
                temp &= 0x01;
            }


            if (temp == 0x00) {
                outAns = _a + _b;
                w.append(std::to_string(_a) + " + " + std::to_string(_b) + " = ");
            } else if (temp == 0x01) {
                outAns = _a - _b;
                w.append(std::to_string(_a) + " - " + std::to_string(_b) + " = ");
            } else if (temp == 0x10) {
                outAns = _a * _b;
                w.append(std::to_string(_a) + " * " + std::to_string(_b) + " = ");
            } else {
                assert(_b != 0);
                outAns = (float)_a / (float)_b;
                w.append(std::to_string(_a) + " / " + std::to_string(_b) + " = ");
            }
            std::cout << w << std::endl;
            printf("Please enter the calculation result:\n");
            float inAns = 0.0;

            t->tic();
            std::cin >> inAns;
            t->toc();

            float err = std::fabs((float)outAns - inAns);

            if (err < 0.01)
                printf("answering correctly\n\n");
            else{
                printf("answering wrongly\n\n");
                w.append(std::to_string(outAns));
                wrong.push_back(w);
            }

        }
        // 输出错题数量和正确数量
        std::cout << "wrong num:" << wrong.size() <<"\n"
                  "correct num:"<< count - wrong.size() << std::endl;

        // 输出错题和对应答案
        for(int i = 0; i < wrong.size();++ i)
            std::cout << " "<< i+1 << " " << wrong[i] <<std::endl;


        printf("shortest time %f s\n", TicToc::min);
        printf("average time %f s\n", TicToc::sum / count);

        delete t;
    }

};

#endif //ALGORITHM_DIFFICULT_H
