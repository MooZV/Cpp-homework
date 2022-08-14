//
// Created by MooZV on 2021/7/13.
//

#ifndef ALGORITHM_ROLE_H
#define ALGORITHM_ROLE_H
#include <iostream>
#include <vector>
#include "numeric"
#include <ctime>

bool probability(int percentage){
    // �������һ��1~100����
    std::srand(time(NULL));
    int r = rand() % 100 + 1;
    return r < percentage;
};

void randomMonster(int &i, int &j, int &k){
    std::srand(time(NULL));
    int r = rand() % 8 - 4;
    i *= r;
    j *= r;
    k *= r;
};


class role{
public:
    // ������
    int vitality;
    // ������ ����
    int vitalityLimit;
    // ������
    int roleAttack;

    role() = default;
    role(int vitality,int vitalityLimit,int roleAttack){};
    virtual ~role(){};
};

// ̽����
class Explorer :public role{
public:
    // ����ֵ
    int roleExperience;
    // ����ֵ
    int roleExperienceLimit;
    // ����
    class weapon * weap;
    // ��¼����ķ�������
    std::vector<int> roomArray;

    Explorer() : role(100, 100, 10) {
        this->roleExperience = 0;
        this->roleExperienceLimit = 10;
        this->roomArray = {0, 0, 0, 0, 0}; // 5������
    };

    void setWeapon(weapon * w){
        this->weap = w;
    };

    ~Explorer() {
        printf("̽�������������߹�%d�����䣺\n ", std::accumulate(this->roomArray.begin(), this->roomArray.end(), 0),
               "Ӫ��:%d \n ", this->roomArray.at(0),
               "��ͨ����:%d \n", this->roomArray.at(1),
               "���巿��:%d \n", this->roomArray.at(2),
               "���췿��:%d \n", this->roomArray.at(3),
               "��������:%d \n", this->roomArray.at(4)
        );
    }
};



// ����
class Monster :public role{
public:
    Monster():role(10,10,5){}
    ~Monster(){};
};
// ��������
class Monsterboss :public role{
public:
    Monsterboss():role(40,40,15){};
    ~Monsterboss(){};
};

#endif //ALGORITHM_ROLE_H
