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
    // ������
    int weaponAttck;

    // �;�
    int Durable;
    weapon() = default;
    weapon(int w,int d):weaponAttck(w),Durable(d){

    };

    virtual ~weapon(){
        std::cout << "weapon ����" << std::endl;
    };
    virtual bool effect() = 0;
};

// ����һ
class weapon1:public weapon{
public:
    weapon1(): weapon(4,6){
        printf("weapon1 generator");
    }
    ~weapon1(){
        std::cout << "weapon1 ����" << std::endl;
    }
    bool effect() {
        this->r->roleAttack += this->weaponAttck;
        Durable -= 1;
        return this->Durable;
    }
};

// ����2
class weapon2:public weapon{
public:
    weapon2(): weapon(6,6){
        printf("weapon2 generator");
    }
    ~weapon2(){
        std::cout << "weapon2 ����" << std::endl;
    }
    bool effect() {
        this->r->roleAttack += this->weaponAttck;
        Durable -= 1;
        weaponAttck = Durable;
        return this->Durable;
    }
};

// ����3
class weapon3:public weapon{
public:

    weapon3(): weapon(0,6){
        printf("weapon3 generator");
    }
    ~weapon3(){
        std::cout << "weapon3 ����" << std::endl;
    }
    bool effect() {
        this->r->roleAttack += this->weaponAttck;
        if(probability(50)){
            printf("������ù�����*2");
            this->r->roleAttack *= 2;
        }
        Durable -= 1;
        return this->Durable;
    }
};

class weaponFactor{
public:
    weapon *weap;
    int r; // ��¼���ɵ��ĸ�����

    weaponFactor(){
        std::srand(time(NULL));
        r = rand() % 3 + 1;
        switch (r) {
            case 1: weap = new weapon1();break;
            case 2: weap = new weapon2();break;
            case 3: weap = new weapon3();break;
            default:
                printf("��������ɴ���");
        }
    }

    weapon* createNewWeap(int r){
        switch (r) {
            case 1: weap = new weapon1();break;
            case 2: weap = new weapon2();break;
            case 3: weap = new weapon3();break;
            default:
                printf("���ɴ���");
        }
        return weap;
    }
    ~weaponFactor(){
        delete weap;
    }

};


#endif //ALGORITHM_WEAPEN_H
