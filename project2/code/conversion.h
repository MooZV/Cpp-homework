//
// Created by MooZ V on 2021/8/13.
//

#ifndef ALGORITHM_CONVERSION_H
#define ALGORITHM_CONVERSION_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
using namespace std;


class convertion{

    // 输入 、输出进制
    int in;
    int out;

    // 计算结果
    char flag; // 存储ans符号
    string ans;

    // 判断相加（true） 相减（false）
    bool same(string &s1,string &s2);

    // 去头部的0
    void headZero(string & s);

    char getChar(int n);

    int getInt(char ch);

    // 任意进制输入（in）加法计算
    string addXStrings(string &num1, string &num2);

    // 输入任意进制（in）减法
    string minusXStrings(string &num1, string &num2);


    // 任意进制（in）翻译成任意进制（out）
    string res;
    string inToOut(string & num);

public:

    convertion(int baseIn,int baseOut):in(baseIn),out(baseOut){};

    ~convertion(){
        cout<<flag;
        if(in != out)
            ans = inToOut(ans);
        cout<<ans<<endl;
    }


    // 判断加减 -- 求和
    void compute(string &s1,string &s2);

};

#endif //ALGORITHM_CONVERSION_H
