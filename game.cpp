#include"game.h"
#include"ui_game.h"
#include<QPixmap>
#include<QMediaPlayer>
#include<QPainter>
#include<iostream>
#include<QTimer>
#include<stdlib.h>
#include<math.h>
game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    timer->start(0);
    timer->setInterval(1);
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/wei/bgm.mp3"));
    player->setVolume(30);
    player->play();
    ui->setupUi(this);
}

game::~game()
{
    delete ui;
}

void game::paintEvent(QPaintEvent *e){
    setFixedSize(1000,800);
    QPainter painter(this);
    //读入背景
    painter.drawPixmap(0,0,1000,800,QPixmap(":/wei/back.png"));
    if(life>0&&time<=4800){
        if(modulecontrol==0){
            painter.drawText(400,20,200,200,Qt::AlignTop|Qt::AlignLeft,"建造防御塔模式");
        }
        else if(modulecontrol==1){
            painter.drawText(400,20,200,200,Qt::AlignTop|Qt::AlignLeft,"升级防御塔模式");
        }
        else if(modulecontrol==2){
            painter.drawText(400,20,200,200,Qt::AlignTop|Qt::AlignLeft,"出售防御塔模式");
        }
        else if(modulecontrol==3){
            painter.drawText(400,20,200,200,Qt::AlignTop|Qt::AlignLeft,"收集战利品模式");
        }
        const QString resourceshow="资源:"+QString::number(resource);
        painter.drawText(0,20,200,200,Qt::AlignTop|Qt::AlignLeft,resourceshow);
        const QString liveshow="剩余血量:"+QString::number(life);
        painter.drawText(800,20,200,200,Qt::AlignTop|Qt::AlignLeft,liveshow);
        //逐个扫描敌人对象
        for(int i=0;i<100;i++){
            if(en[i].live==true){
                const QString hitpointshow="剩余血量:"+QString::number(en[i].hitpoint);
                painter.drawText(en[i].enemyx+10,en[i].enemyy+100,200,200,Qt::AlignTop|Qt::AlignLeft,hitpointshow);
                painter.drawPixmap(en[i].enemyx,en[i].enemyy,100,100,en[i].link);
                double space[100],conspace[100];
                for(int j=0;j<100;j++)
                    if(to[j].live==true)towersum++;
                if(en[i].attacking==false&&towersum!=0){
                    for(int j=0;j<100;j++)
                        if(en[i].live==true&&to[j].live==true){
                            space[j]=(to[j].towerx+40-en[i].enemyx)*(to[j].towerx+40-en[i].enemyx)+(to[j].towery+50-en[i].enemyy)*(to[j].towery+50-en[i].enemyy);
                            conspace[j]=space[j];
                        }
                        else space[j]=10000000;

                    for(int j=0;j<99;j++){
                        if(space[j]<space[j+1]){
                            double mid=space[j];
                            space[j]=space[j+1];
                            space[j+1]=mid;
                        }
                    }
                    for(int j=0;j<100;j++){
                        if(conspace[j]==space[99]){
                            en[i].minto=j;break;
                        }
                    }
                    en[i].attacking=true;
                    en[i].firex=en[i].enemyx;
                    en[i].firey=en[i].enemyy;
                    en[i].tarx=to[en[i].minto].towerx;
                    en[i].tary=to[en[i].minto].towery;
                }
                else if(en[i].attacking==true&&to[en[i].minto].live==true)
                    painter.drawPixmap(en[i].firex,en[i].firey,30,30,en[i].link2);
                towersum=0;
            }
            else if(en[i].body==true)painter.drawPixmap(en[i].enemyx,en[i].enemyy,100,100,en[i].link);
        }
        //逐个扫描塔对象
        for(int i=0;i<100;i++){
            if(to[i].live==true){
                const QString hitpointshow="剩余血量:"+QString::number(to[i].hitpoint);
                painter.drawText(to[i].towerx-30,to[i].towery+80,200,200,Qt::AlignTop|Qt::AlignLeft,hitpointshow);
                painter.drawPixmap(to[i].towerx-35,to[i].towery-42,80,100,to[i].link);
                if(to[i].level==0)
                    painter.drawEllipse(to[i].towerx-to[i].area/2,to[i].towery-to[i].area/2,to[i].area,to[i].area);
                if(to[i].level==1){
                    bool enemyexist=false;
                    int tarenemy=0;
                    for(int j=0;j<100;j++){
                        if(en[j].live==true){
                            enemyexist=true;
                            tarenemy=j;
                            break;
                        }
                    }
                    if(enemyexist==true){
                        painter.setPen(QPen(Qt::red, 5));
                        painter.drawLine(to[i].towerx+3,to[i].towery-35,en[tarenemy].enemyx+30,en[tarenemy].enemyy+40);
                        painter.setPen(Qt::black);
                        en[tarenemy].hitpoint-=1;
                        if(en[tarenemy].hitpoint<=0){
                            tarenemy++;
                            en[tarenemy].die();
                        }
                    }
                }
                double space[100];
                for(int j=0;j<100;j++)
                    if(to[i].live==true&&en[j].live==true){
                        space[j]=sqrt((to[i].towerx+40-en[j].enemyx)*(to[i].towerx+40-en[j].enemyx)+(to[i].towery+50-en[j].enemyy)*(to[i].towery+50-en[j].enemyy));
                        if(space[j]<to[i].area)en[j].hitpoint--;
                        if(en[j].hitpoint<=0){
                            en[j].die();
                        }
                    }
            }
        }
    }
    else if(life<=0)
        painter.drawText(400,400,200,200,Qt::AlignTop|Qt::AlignLeft,"游戏失败");
    else
        painter.drawText(400,400,200,200,Qt::AlignTop|Qt::AlignLeft,"胜利");
}

void game::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Q)
        modulecontrol=0;
    else if(e->key() == Qt::Key_W)
        modulecontrol=1;
    else if(e->key() == Qt::Key_E)
        modulecontrol=2;
    else if(e->key() == Qt::Key_R)
        modulecontrol=3;
    this->repaint();
}
void game::mousePressEvent(QMouseEvent *e){
    if(modulecontrol==0){
        if(e->button()==Qt::LeftButton){
            if(resource>=200){
                to[towercount].settower(e->x(),e->y());
                resource-=200;
                towercount++;}
        }
    }
    else if(modulecontrol==1){if(e->button()==Qt::LeftButton){
            if(resource>=400){
                for(int i=0;i<100;i++)
                    if(to[i].live==true)towersum++;
                if(towersum>0){
                    double space[100],conspace[100];
                    int minto=0;
                    for(int i=0;i<100;i++){
                        if(to[i].live==true)
                            space[i]=(to[i].towerx-e->x())*(to[i].towerx-e->x())+(to[i].towery-e->y())*(to[i].towery-e->y());
                        else space[i]=100000000;
                        conspace[i]=space[i];
                    }
                    for(int i=0;i<99;i++){
                        if(space[i]<space[i+1]){
                            double mid=space[i];
                            space[i]=space[i+1];
                            space[i+1]=mid;
                        }
                    }
                    for(int i=0;i<100;i++)
                        if(conspace[i]==space[99]){
                            minto=i;
                            break;
                        }
                    to[minto].upgrade();
                    resource-=400;
                }
                towersum=0;
            }
        }
    }
    else if(modulecontrol==2){
        if(e->button()==Qt::LeftButton){
            for(int i=0;i<100;i++)
                if(to[i].live==true)towersum++;
            if(towersum>0){
                double space[100],conspace[100];
                int minto=0;
                for(int i=0;i<100;i++){
                    if(to[i].live==true)
                        space[i]=(to[i].towerx-e->x())*(to[i].towerx-e->x())+(to[i].towery-e->y())*(to[i].towery-e->y());
                    else space[i]=100000000;
                    conspace[i]=space[i];
                }
                for(int i=0;i<99;i++){
                    if(space[i]<space[i+1]){
                        double mid=space[i];
                        space[i]=space[i+1];
                        space[i+1]=mid;
                    }
                }
                for(int i=0;i<100;i++)
                    if(conspace[i]==space[99]){
                        minto=i;
                        break;
                    }
                to[minto].sell();
                resource+=150;
            }
            towersum=0;

        }
    }
    else if(modulecontrol==3){
        if(e->button()==Qt::LeftButton){
            int bodysum=0;
            for(int i=0;i<100;i++)
                if(en[i].body==true)bodysum++;
            if(bodysum>0){
                int minbo=0;
                double space[100],conspace[100];
                for(int i=0;i<100;i++){
                    if(en[i].body==true)
                        space[i]=(en[i].enemyx-e->x())*(en[i].enemyx-e->x())+(en[i].enemyy-e->y())*(en[i].enemyy-e->y());
                    else space[i]=100000000;
                    conspace[i]=space[i];
                }
                for(int i=0;i<99;i++){
                    if(space[i]<space[i+1]){
                        double mid=space[i];
                        space[i]=space[i+1];
                        space[i+1]=mid;
                    }
                }
                for(int i=0;i<100;i++)
                    if(conspace[i]==space[99]){
                        minbo=i;
                        break;
                    }
                en[minbo].body=false;
                resource+=100;
            }
            bodysum=0;

        }
    }
    this->repaint();
}
void game::run(){
    //游戏运行
    if(time<4800&&time%50==0)enemygenerate(time/50);
    for(int i=0;i<100;i++){
        if(en[i].live==true){
            en[i].move(en[i].enemyx,en[i].enemyy,en[i].routine);
            if(en[i].attacking==true)
                if(en[i].attack(en[i].firex,en[i].firey,en[i].tarx,en[i].tary)==true){
                    to[en[i].minto].hitpoint-=2;
                    if(to[en[i].minto].hitpoint<=0){
                        to[en[i].minto].live=false;
                        towersum--;
                    }
                }
        }
        if(to[i].live==true){
            to[i].attack(to[i].area);
        }
    }
    time+=1;
    int allenter=0;
    for(int i=0;i<100;i++){
        if(en[i].enter==true)allenter++;
    }
    life=10-allenter;
    this->repaint();
}

void game::enemygenerate(int x){
    en[x].live=true;
    en[x].hitpoint=300+time/2;
    int sort=rand()%5+1;
    int inix[6]={0,0,545,545,900,900},iniy[6]={0,600,680,680,550,550};
    en[x].routine=sort;
    en[x].enemyx=inix[sort];
    en[x].enemyy=iniy[sort];
}
