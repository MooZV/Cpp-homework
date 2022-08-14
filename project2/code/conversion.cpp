//
// Created by MooZV on 2021/4/19.
//
#include "conversion.h"
using namespace std;

bool convertion::same(string &s1, string &s2) {
    // 读取第一个字符（运算符）
    char c1 = s1[0];
    char c2 = s2[0];
    s1.erase(0, 1);
    s2.erase(0, 1);
    // 判断符号
    if (c1 == c2) {
        flag = c1;
        return true;
    } else { // 若相减，则判断是否改变符号
        if (s1.size() > s2.size()) {
            flag = c1;
            return false;
        } else if (s1.size() < s2.size()) {
            flag = c2;
            swap(s1, s2);
            return false;
        } else {
            for (int i = 0; i < s2.size(); ++i) {
                if (s1[i] != s2[i]) {
                    if (s1[i] < s2[i]) {
                        // 永远把 s1 当成那个大的
                        swap(s1, s2);
                        flag = c2;
                        break;
                    }
                    break;
                }
            }
        }
        return false;
    }
    return true;
}

// 去头部的0
void convertion::headZero(string &s) {
    int pos = 0;
    while (s[pos] == '0') pos++;
    s.erase(0, pos);
    if (s.empty())
        s = "0";
}

char convertion::getChar(int n) {
    if (n <= 9)
        return n + '0';
    else
        return n - 10 + 'a';
}

int convertion::getInt(char ch) {
    int a = 0;
    if ('0' <= ch && ch <= '9')
        a = ch - '0';
    else
        a = ch - 'a' + 10;
    if (a >= in)
        throw out_of_range(" character out of base ");
    return a;
}

// 任意进制输入（in）加法计算
string convertion::addXStrings(string &num1, string &num2) {
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;
    int x, y;
    string res;
    while (i >= 0 || j >= 0 || carry) {
        x = i >= 0 ? getInt(num1[i]) : 0;
        y = j >= 0 ? getInt(num2[j]) : 0;
        int temp = x + y + carry;
        res += getChar(temp % in);
        carry = temp / in;
        i--, j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

// 输入任意进制（in）减法
string convertion::minusXStrings(string &num1, string &num2) {
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;
    int x, y;
    string res;
    while (i >= 0 || j >= 0 || carry) {
        x = i >= 0 ? getInt(num1[i]) : 0;
        y = j >= 0 ? getInt(num2[j]) : 0;
        int temp = x - y - carry;

        if (temp < 0) {
            x += in;
            temp = x - y - carry;
            carry = 1;
        } else
            carry = 0;
        res += getChar(temp % in);
        carry += temp / in;
        i--, j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

string convertion::inToOut(string &num) {
    // 使用递归调用
    if (num == "0") {
        reverse(res.begin(), res.end());
        headZero(res);
        return res;
    }
    int x, y, carry(0);
    string temp;
    for (int i = 0; i < num.size(); ++i) {
        x = carry * in + getInt(num[i]);
        y = x / out;
        temp.push_back(getChar(y));
        carry = x - y * out;
    }
    res.push_back(getChar(carry));
    headZero(temp);
    return inToOut(temp);
}



// 判断加减 -- 求和
void convertion::compute(string &s1, string &s2) {

    if (same(s1, s2)) {
        ans = addXStrings(s1, s2);
    } else
        ans = minusXStrings(s1, s2);
    headZero(ans);
}


int main(int argc, char *argv[]) {
    // myparm data.txt
    // myparm data.txt baseIn
    // myparm data.txt baseIn baseOut

    // 默认十进制输入，十进制输出
    int baseIn = 10;
    int baseOut = 10;

    switch (argc) {
        case 2:
            break;
        case 3:
            baseIn = atoi(argv[2]);
            break;
        case 4:
            baseIn = atoi(argv[2]);
            baseOut = atoi(argv[3]);
            break;
        default:
            throw out_of_range(" Invalid number of input parameters ");
            break;
    }
    // lamda函数
    auto f = [](uint8_t a) -> bool { return a > 1 && a <= 36; };

    bool result = f(baseIn) && f(baseOut);

    if (!result)
        throw out_of_range(" Input base is invalid ");

    convertion base(baseIn, baseOut);

    fstream data{argv[1], ios_base::in};
    if (data.is_open()) {
        string line1, line2;
        getline(data, line1);
        getline(data, line2);
        base.compute(line1, line2);
        data.close();
    } else
        cout << "文件无法打开" << endl;


    return 0;
}