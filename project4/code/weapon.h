//
// Created by MooZV on 2021/7/13.
//

#ifndef ALGORITHM_WEAPEN_H
#define ALGORITHM_WEAPEN_H
#include <iostream>
#include "role.h"

class weapon{
public:
    class Explorer * r;
    void setRole(Explorer * R){
        this->r = R;

    }
    // 攻击力
    int weaponAttck;

    // 耐久
    int Durable;
    weapon() = default;
    weapon(int w,int d):weaponAttck(w),Durable(d){

    };

    virtual ~weapon(){
        std::cout << "weapon 析构" << std::endl;
    };
    virtual bool effect() = 0;
};

// 武器一
class weapon1:public weapon{
public:
    weapon1(): weapon(4,6){
        printf("weapon1 generator");
    }
    ~weapon1(){
        std::cout << "weapon1 析构" << std::endl;
    }
    bool effect() {
        this->r->roleAttack += this->weaponAttck;
        Durable -= 1;
        return this->Durable;
    }
};

// 武器2
class weapon2:public weapon{
public:
    weapon2(): weapon(6,6){
        printf("weapon2 generator");
    }
    ~weapon2(){
        std::cout << "weapon2 析构" << std::endl;
    }
    bool effect() {
        this->r->roleAttack += this->weaponAttck;
        Durable -= 1;
        weaponAttck = Durable;
        return this->Durable;
    }
};

// 武器3
class weapon3:public weapon{
public:

    weapon3(): weapon(0,6){
        printf("weapon3 generator");
    }
    ~weapon3(){
        std::cout << "weapon3 析构" << std::endl;
    }
    bool effect() {
        this->r->roleAttack += this->weaponAttck;
        if(probability(50)){
            printf("获得永久攻击力*2");
            this->r->roleAttack *= 2;
        }
        Durable -= 1;
        return this->Durable;
    }
};

class weaponFactor{
public:
    weapon *weap;
    int r; // 记录生成的哪个武器

    weaponFactor(){
        std::srand(time(NULL));
        r = rand() % 3 + 1;
        switch (r) {
            case 1: weap = new weapon1();break;
            case 2: weap = new weapon2();break;
            case 3: weap = new weapon3();break;
            default:
                printf("随机数生成错误");
        }
    }

    weapon* createNewWeap(int r){
        switch (r) {
            case 1: weap = new weapon1();break;
            case 2: weap = new weapon2();break;
            case 3: weap = new weapon3();break;
            default:
                printf("生成错误");
        }
        return weap;
    }
    ~weaponFactor(){
        delete weap;
    }

};


#endif //ALGORITHM_WEAPEN_H
