#ifndef GAME_H
#define GAME_H
#include<QMediaPlayer>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include<iostream>
#include<QKeyEvent>
#include"enemy.h"
#include"tower.h"
namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void enemygenerate(int x);
protected slots:
    void run();
private:
    QTimer *timer;
    Ui::game *ui;
    int resource=1000;
    int life=10;
    int time=0;
    int towercount=0;
    int towersum=0;
    int towerpointer=0;
    int modulecontrol=0;
    enemy en[100];
    tower to[100];
};

#endif // GAME_H
