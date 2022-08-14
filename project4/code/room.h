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
    Explorer * explorer; // ���� ̽����
    // ����
    int experience;
    room(int e):explorer(new Explorer()){
        experience = e;
    };

    virtual ~room(){};

    void setExplorer(Explorer * e){
        this->explorer = e;
    };
    // �����¼�
    virtual void entryEvent() = 0;

    // ս���¼�
    virtual void fightingEvent() = 0;

    // ����
    void settlement(){
        explorer->roleExperience += this->experience;
        if(explorer->roleExperience > explorer->roleExperienceLimit)
            explorer->roleExperience -= explorer->roleExperienceLimit;
        printf("���%d�㾭�飬��ǰ���飨%d/%d��\n",experience,explorer->roleExperience,explorer->roleExperienceLimit);
    };
};

// Ӫ��
class camp:public room{
public:
    camp():room(0){
        explorer->roomArray.at(0) += 1;
        printf("���� Ӫ��");
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~camp(){};
    // �����¼� -- �ָ�ȫ������
    void entryEvent() override {
        explorer->vitality = explorer->vitalityLimit;
    } ;

    // ս���¼�
    void fightingEvent() override {};

};


// ��ͨ����
class commonRoom:public room{
public:
    int generator; // �������1~3������
    commonRoom():room(0){
        explorer->roomArray.at(1) += 1;
        printf("���� ��ͨ����");
        std::srand(time(NULL));
        generator = rand() % 3 + 1;
        experience = generator;
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~commonRoom(){}
    // �����¼�
    void entryEvent() override {
        if(probability(10)){
            explorer->vitality += 10;
            printf("�����¼����ظ�10����������ó����ָ�Ч��,��ǰ����(%d / %d)",explorer->vitality,explorer->vitalityLimit);
            return;
        }
        // TODO ������������
    } ;

    void fightingEvent(){
        printf("���� ");
        std::vector<Monster *> *v = new std::vector<Monster *>;
        for (int i = 0; i < generator; ++i) {
            Monster *monster = new Monster();
            randomMonster(monster->vitality, monster->vitalityLimit, monster->roleAttack);
            v->emplace_back(monster);
            // ��������������Զ�ȹ�����������ߵ��Ǹ�
            if (v->size() > 1 && v->at(i)->roleAttack < v->at(i - 1)->roleAttack)
                std::swap(v->at(i), v->at(i - 1));
            printf(" ���� %d (%d / %d) ", i + 1, monster->vitality, monster->vitalityLimit);
        }

        printf("\n ս����ʼ \n");
        while (!v->empty()) {
            Monster *m = *v->end();
            if (m->vitality < 0) {
                printf("����%d����", v->size());
                delete m;
                v->pop_back();
                continue;
            }
            int n = v->size();
            printf("̽���߹�������%d,���%d���˺�,����%d (%d / %d)\n", n, explorer->roleAttack, n, m->vitality, m->vitalityLimit);
            for (int i = 1; i <= n; ++i) {
                explorer->vitality -= v->at(i - 1)->vitality;
                // ��̽��������
                if (explorer->vitality < 0) {
                    delete explorer;
                    return;
                }
                printf("����%d����̽���ߣ����%d���˺���̽���ߣ�%d/%d��\n", i, v->at(i - 1)->roleAttack, explorer->vitality,
                       explorer->vitalityLimit);
            }
        }
        return;
    };

};
// ���巿��
class trapRoom:public room{
public:
    trapRoom():room(1){
        explorer->roomArray.at(2) += 1;
//        experience = 1;
        printf("���� ���巿��");
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~trapRoom(){}
    // �����¼�
    void entryEvent() override{
        int loss = explorer->vitality * 0.1;
        explorer -= loss;
        // TODO ����
        //ÿ�ν��뷿����ʧ
        //2������������5��
        //����
        printf("�����¼�����ʧ%d����������ɳ������ˣ���ǰ������%d / %d��",loss,explorer->vitality,explorer->vitalityLimit);
    } ;


    void fightingEvent(){
        // ����1������ֵΪ�����������ֵ�������Ĺ���
        Monster *m = new Monster();
        m->vitality *= 2;
        m->vitalityLimit *= 2;
        m->roleAttack *= 2;

        printf("���� ����1��%d/%d��",m->vitality,m->vitalityLimit);
        printf("\n ս����ʼ \n ");

        while(m->vitality < 0){
            m->vitality -= explorer->roleAttack;
            printf("̽���߹�������1,���%d���˺�,����1 (%d / %d)\n",explorer->roleAttack ,m->vitality,m->vitalityLimit);
            if(m->vitality < 0){
                printf("����1����\n");
                break;
            }
            explorer->vitality -= m->roleAttack;
            printf("����1����̽���ߣ����%d���˺���̽���ߣ�%d / %d��\n",m->roleAttack,explorer->vitality,explorer->vitalityLimit);
            if(explorer->vitality < 0){
                delete explorer;
                return;
            }
        }
        return;
    };



};
// ���췿��
class bossRoom:public room{
public:
    bossRoom():room(5){
        explorer->roomArray.at(3) += 1;
//        experience = 5;
        printf("���� ���췿��");
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~bossRoom(){}
    // �����¼�
    void entryEvent() override{
        explorer->vitality += 20;
        if(explorer->vitality > explorer->vitalityLimit)
            explorer->vitality = explorer->vitalityLimit;
        // TODO ������и���Ч��
    } ;


    void fightingEvent(){
        // ����1������ֵΪ�����������ֵ�������Ĺ���
        Monsterboss *m = new Monsterboss();

        printf("���� �������죨%d / %d��",m->vitality,m->vitalityLimit);
        printf("\n ս����ʼ \n ");

        while(m->vitality < 0){
            m->vitality -= explorer->roleAttack;
            printf("̽���߹�����������,���%d���˺�,����1 (%d / %d)\n",explorer->roleAttack ,m->vitality,m->vitalityLimit);
            if(m->vitality < 0){
                printf("����1����\n");
                break;
            }
            explorer->vitality -= m->roleAttack;
            printf("�������칥��̽���ߣ����%d���˺���̽���ߣ�%d / %d��\n",m->roleAttack,explorer->vitality,explorer->vitalityLimit);
            if(explorer->vitality < 0){
                delete explorer;
                return;
            }
        }
        return;
    };

};
// ��������
class weaponRoom:public room{
public:
    // ԭʼ����ֵ
    int rawVitality;
    weaponFactor * wf;
    // �������һ������
    weapon * weap;
    weaponRoom():room(2){
        explorer->roomArray.at(4) += 1;
//        this->experience = 2;
        this->wf = new weaponFactor();
        this->weap = this->wf->weap;
        printf("���� ��������");
        this->entryEvent();
        this->fightingEvent();
        this->settlement();
    }
    ~weaponRoom(){}
    // �����¼�
    void entryEvent() override{
        rawVitality = explorer->vitality;
    };

    void fightingEvent() {
        // ����1������ֵΪ�����������ֵ�������Ĺ���
        Explorer *m = new Explorer();
        m->vitality *= 0.4;
        m->vitalityLimit *= 0.4;
        m->roleAttack *= 0.4;
        m->weap = weap;
        m->weap->setRole(m);


        printf("���� ����1��%d/%d��", m->vitality, m->vitalityLimit);
        printf("\n ս����ʼ \n ");

        while (m->vitality < 0) {
            m->vitality -= explorer->roleAttack;
            printf("̽���߹�������1,���%d���˺�,����1 (%d / %d)\n", explorer->roleAttack, m->vitality, m->vitalityLimit);
            if (m->vitality < 0) {
                printf("����1����\n");
                explorer->weap = wf->createNewWeap(wf->r);
                printf("̽���߻������%d\n", wf->r);
                delete m;
                delete wf;
                break;
            }
            // �����������
            if (!m->weap->effect()) {
                printf("����%d���\n", wf->r);
                delete wf;
            };
            explorer->vitality -= m->roleAttack;
            printf("����1����̽���ߣ����%d���˺���̽���ߣ�%d / %d��\n", m->roleAttack, explorer->vitality, explorer->vitalityLimit);
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
    // ���ɷ���
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
                    printf("��������ɴ���\n");
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
