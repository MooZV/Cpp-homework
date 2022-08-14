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
    // 随机生成一个1~100的数
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
    // 生命力
    int vitality;
    // 生命力 上限
    int vitalityLimit;
    // 攻击力
    int roleAttack;

    role() = default;
    role(int vitality,int vitalityLimit,int roleAttack){};
    virtual ~role(){};
};

// 探险者
class Explorer :public role{
public:
    // 经验值
    int roleExperience;
    // 经验值
    int roleExperienceLimit;
    // 武器
    class weapon * weap;
    // 记录进入的房间容器
    std::vector<int> roomArray;

    Explorer() : role(100, 100, 10) {
        this->roleExperience = 0;
        this->roleExperienceLimit = 10;
        this->roomArray = {0, 0, 0, 0, 0}; // 5个房间
    };

    void setWeapon(weapon * w){
        this->weap = w;
    };

    ~Explorer() {
        printf("探险者死亡，共走过%d个房间：\n ", std::accumulate(this->roomArray.begin(), this->roomArray.end(), 0),
               "营地:%d \n ", this->roomArray.at(0),
               "普通房间:%d \n", this->roomArray.at(1),
               "陷阱房间:%d \n", this->roomArray.at(2),
               "首领房间:%d \n", this->roomArray.at(3),
               "武器房间:%d \n", this->roomArray.at(4)
        );
    }
};



// 怪物
class Monster :public role{
public:
    Monster():role(10,10,5){}
    ~Monster(){};
};
// 怪物首领
class Monsterboss :public role{
public:
    Monsterboss():role(40,40,15){};
    ~Monsterboss(){};
};

#endif //ALGORITHM_ROLE_H
