//
// Created by MooZV on 2021/7/13.
//

#ifndef ALGORITHM_ROOM_H
#define ALGORITHM_ROOM_H

#include "role.h"
#include <vector>

#include "string"
#include "weapon.h"



class room{
public:
    Explorer * explorer; // 接收 探险者
    // 经验
    int experience;
    room(int e):explorer(new Explorer()){
        experience = e;
    };

    virtual ~room(){};

    void setExplorer(Explorer * e){
        this->explorer = e;
    };
    // 进入事件
    virtual void entryEvent() = 0;

    // 战斗事件
    virtual void fightingEvent() = 0;

    // 结算
    void settlement(){
        explorer->roleExperience += this->experience;
        if(explorer->roleExperience > explorer->roleExperienceLimit)
            explorer->roleExperience -= explorer->roleExperienceLimit;
        printf("获得%d点经验，当前经验（%d/%d）\n",experience,explorer->roleExperience,explorer->roleExperienceLimit);
    };
};

// 营地
class camp:public room{
public:
    camp():room(0){
        explorer->roomArray.at(0) += 1;
        printf("进入 营地");
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~camp(){};
    // 进入事件 -- 恢复全部生命
    void entryEvent() override {
        explorer->vitality = explorer->vitalityLimit;
    } ;

    // 战斗事件
    void fightingEvent() override {};

};


// 普通房间
class commonRoom:public room{
public:
    int generator; // 随机生成1~3个怪物
    commonRoom():room(0){
        explorer->roomArray.at(1) += 1;
        printf("进入 普通房间");
        std::srand(time(NULL));
        generator = rand() % 3 + 1;
        experience = generator;
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~commonRoom(){}
    // 进入事件
    void entryEvent() override {
        if(probability(10)){
            explorer->vitality += 10;
            printf("触发事件，回复10点生命，获得持续恢复效果,当前生命(%d / %d)",explorer->vitality,explorer->vitalityLimit);
            return;
        }
        // TODO 持续两个房间
    } ;

    void fightingEvent(){
        printf("遇到 ");
        std::vector<Monster *> *v = new std::vector<Monster *>;
        for (int i = 0; i < generator; ++i) {
            Monster *monster = new Monster();
            randomMonster(monster->vitality, monster->vitalityLimit, monster->roleAttack);
            v->emplace_back(monster);
            // 按攻击力排序，永远先攻击攻击力最高的那个
            if (v->size() > 1 && v->at(i)->roleAttack < v->at(i - 1)->roleAttack)
                std::swap(v->at(i), v->at(i - 1));
            printf(" 怪物 %d (%d / %d) ", i + 1, monster->vitality, monster->vitalityLimit);
        }

        printf("\n 战斗开始 \n");
        while (!v->empty()) {
            Monster *m = *v->end();
            if (m->vitality < 0) {
                printf("怪物%d死亡", v->size());
                delete m;
                v->pop_back();
                continue;
            }
            int n = v->size();
            printf("探险者攻击怪物%d,造成%d点伤害,怪物%d (%d / %d)\n", n, explorer->roleAttack, n, m->vitality, m->vitalityLimit);
            for (int i = 1; i <= n; ++i) {
                explorer->vitality -= v->at(i - 1)->vitality;
                // 若探险者死亡
                if (explorer->vitality < 0) {
                    delete explorer;
                    return;
                }
                printf("怪物%d攻击探险者，造成%d点伤害，探险者（%d/%d）\n", i, v->at(i - 1)->roleAttack, explorer->vitality,
                       explorer->vitalityLimit);
            }
        }
        return;
    };

};
// 陷阱房间
class trapRoom:public room{
public:
    trapRoom():room(1){
        explorer->roomArray.at(2) += 1;
//        experience = 1;
        printf("进入 陷阱房间");
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~trapRoom(){}
    // 进入事件
    void entryEvent() override{
        int loss = explorer->vitality * 0.1;
        explorer -= loss;
        // TODO 并且
        //每次进入房间损失
        //2点生命，持续5个
        //房间
        printf("触发事件，损失%d点生命，造成持续损伤，当前生命（%d / %d）",loss,explorer->vitality,explorer->vitalityLimit);
    } ;


    void fightingEvent(){
        // 生成1个属性值为怪物基本属性值的两倍的怪物
        Monster *m = new Monster();
        m->vitality *= 2;
        m->vitalityLimit *= 2;
        m->roleAttack *= 2;

        printf("遇到 怪物1（%d/%d）",m->vitality,m->vitalityLimit);
        printf("\n 战斗开始 \n ");

        while(m->vitality < 0){
            m->vitality -= explorer->roleAttack;
            printf("探险者攻击怪物1,造成%d点伤害,怪物1 (%d / %d)\n",explorer->roleAttack ,m->vitality,m->vitalityLimit);
            if(m->vitality < 0){
                printf("怪物1死亡\n");
                break;
            }
            explorer->vitality -= m->roleAttack;
            printf("怪物1攻击探险者，造成%d点伤害，探险者（%d / %d）\n",m->roleAttack,explorer->vitality,explorer->vitalityLimit);
            if(explorer->vitality < 0){
                delete explorer;
                return;
            }
        }
        return;
    };



};
// 首领房间
class bossRoom:public room{
public:
    bossRoom():room(5){
        explorer->roomArray.at(3) += 1;
//        experience = 5;
        printf("进入 首领房间");
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~bossRoom(){}
    // 进入事件
    void entryEvent() override{
        explorer->vitality += 20;
        if(explorer->vitality > explorer->vitalityLimit)
            explorer->vitality = explorer->vitalityLimit;
        // TODO 清除所有负面效果
    } ;


    void fightingEvent(){
        // 生成1个属性值为怪物基本属性值的两倍的怪物
        Monsterboss *m = new Monsterboss();

        printf("遇到 怪物首领（%d / %d）",m->vitality,m->vitalityLimit);
        printf("\n 战斗开始 \n ");

        while(m->vitality < 0){
            m->vitality -= explorer->roleAttack;
            printf("探险者攻击怪物首领,造成%d点伤害,怪物1 (%d / %d)\n",explorer->roleAttack ,m->vitality,m->vitalityLimit);
            if(m->vitality < 0){
                printf("怪物1死亡\n");
                break;
            }
            explorer->vitality -= m->roleAttack;
            printf("怪物首领攻击探险者，造成%d点伤害，探险者（%d / %d）\n",m->roleAttack,explorer->vitality,explorer->vitalityLimit);
            if(explorer->vitality < 0){
                delete explorer;
                return;
            }
        }
        return;
    };

};
// 武器房间
class weaponRoom:public room{
public:
    // 原始生命值
    int rawVitality;
    weaponFactor * wf;
    // 随机生成一个武器
    weapon * weap;
    weaponRoom():room(2){
        explorer->roomArray.at(4) += 1;
//        this->experience = 2;
        this->wf = new weaponFactor();
        this->weap = this->wf->weap;
        printf("进入 武器房间");
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~weaponRoom(){}
    // 进入事件
    void entryEvent() override{
        rawVitality = explorer->vitality;
    };

    void fightingEvent() {
        // 生成1个属性值为怪物基本属性值的两倍的怪物
        Explorer *m = new Explorer();
        m->vitality *= 0.4;
        m->vitalityLimit *= 0.4;
        m->roleAttack *= 0.4;
        m->weap = weap;
        m->weap->setRole(m);


        printf("遇到 怪物1（%d/%d）", m->vitality, m->vitalityLimit);
        printf("\n 战斗开始 \n ");

        while (m->vitality < 0) {
            m->vitality -= explorer->roleAttack;
            printf("探险者攻击怪物1,造成%d点伤害,怪物1 (%d / %d)\n", explorer->roleAttack, m->vitality, m->vitalityLimit);
            if (m->vitality < 0) {
                printf("怪物1死亡\n");
                explorer->weap = wf->createNewWeap(wf->r);
                printf("探险者获得武器%d\n", wf->r);
                delete m;
                delete wf;
                break;
            }
            // 添加武器属性
            if (!m->weap->effect()) {
                printf("武器%d损毁\n", wf->r);
                delete wf;
            };
            explorer->vitality -= m->roleAttack;
            printf("怪物1攻击探险者，造成%d点伤害，探险者（%d / %d）\n", m->roleAttack, explorer->vitality, explorer->vitalityLimit);
            if (explorer->vitality < 0) {
                delete explorer;
                return;
            }
        }
        return;
    };
};

class roomFactor{
public:

    room * Room;
    roomFactor(){
        this->Generate();
    }
    // 生成房间
    void Generate(){
        while(true){
            std::srand(time(NULL));
            int i = rand() % 5 + 1;
            switch (i) {
                case 1: Room = new camp();break;
                case 2: Room = new commonRoom();break;
                case 3: Room = new trapRoom();break;
                case 4: Room = new bossRoom();break;
                case 5: Room = new weaponRoom();break;
                default:
                    printf("随机数生成错误\n");
            }
            if(Room->explorer->vitality < 0)
                break;
        }

    }
    ~roomFactor(){
        delete Room;
    }
};

#endif //ALGORITHM_ROOM_H
