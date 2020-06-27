#ifndef TOWER_H
#define TOWER_H
#include<QString>

class tower
{
public:
    tower();
    void die();
    void attack(int a);
    void attack2(int x,int y,int tarx,int tary);
    void settower(int x,int y);
    void upgrade();
    void sell();
    bool live=false;
    int hitpoint=100;
    int towerx;
    int towery;
    int level=0;
    int area=0;
    QString link=":/wei/tower1.png";
};

#endif // TOWER_H
