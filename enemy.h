#ifndef ENEMY_H
#define ENEMY_H
#include<QString>
class enemy
{
public:
    enemy();
    void move(int nowx,int nowy,int rou);
    bool attack(double x,double y,double tarx,double tary);
    void die();
    bool live=false;
    bool body=false;
    int hitpoint=300;
    int enemyx;
    int enemyy;
    double firex;
    double firey;
    double tarx;
    double tary;
    int minto;
    int routine;
    bool enter=false;
    bool attacking=false;
    QString link=":/wei/enemy1.png";
    QString link2=":/wei/fire.png";

};

#endif // ENEMY_H
