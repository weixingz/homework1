#include "enemy.h"
#include<math.h>
enemy::enemy()
{
}
void enemy::move(int nowx,int nowy,int rou){
    if(live==true){
        if(rou==1){
            if(nowy==600&&nowx!=270)enemyx++;
            else if(nowx==270&&nowy!=240)enemyy--;
            else if(nowy==240&&nowx!=100)enemyx--;
            else if(nowx==100&&nowy!=100)enemyy--;
            else {
                live=false;
                enter=true;}
        }
        else if(rou==2){
            if(enemyx==545&&enemyy!=470)enemyy--;
            else if(enemyy==470&&enemyx!=270)enemyx--;
            else if(enemyx==270&&enemyy!=240)enemyy--;
            else if(enemyy==240&&enemyx!=100)enemyx--;
            else if(enemyx==100&&enemyy!=100)enemyy--;
            else {
                live=false;
                enter=true;}
        }
        else if(rou==3){
            if(enemyx==545&&enemyy!=470&&enemyy!=220)enemyy--;
            else if(enemyy==470&&enemyx!=750)enemyx++;
            else if(enemyx==750&&enemyy!=220)enemyy--;
            else if(enemyy==220&&enemyx!=460)enemyx--;
            else if(enemyx==460&&enemyy!=70)enemyy--;
            else if(enemyy==70&&enemyx!=100)enemyx--;
            else {
                live=false;
                enter=true;}
        }
        else if(rou==4){
            if(enemyy==550&&enemyx!=750)enemyx--;
            else if(enemyx==750&&enemyy!=220)enemyy--;
            else if(enemyy==220&&enemyx!=460)enemyx--;
            else if(enemyx==460&&enemyy!=70)enemyy--;
            else if(enemyy==70&&enemyx!=100)enemyx--;
            else {
                live=false;
                enter=true;}
        }
        else if(rou==5){
            if(enemyy==550&&enemyx!=750)enemyx--;
            else if(enemyx==750&&enemyy!=470)enemyy--;
            else if(enemyy==470&&enemyx!=270)enemyx--;
            else if(enemyx==270&&enemyy!=240)enemyy--;
            else if(enemyy==240&&enemyx!=100)enemyx--;
            else if(enemyx==100&&enemyy!=100)enemyy--;
            else {
                live=false;
                enter=true;}
        }
    }
}
bool enemy::attack(double x,double y,double tarx,double tary){
    double spacex=tarx-x;
    double spacey=tary-y;
    double space=sqrt(spacex*spacex+spacey*spacey);
    double lenx=spacex/space;
    double leny=spacey/space;
    if(tarx>x)
        firex+=lenx;
    else if(tarx<x)
        firex+=lenx;
    if(tary>y)
        firey+=leny;
    else if(tary<y)
        firey+=leny;
    if(space<1){
        attacking=false;
        return true;}
    else return false;
}
void enemy::die(){
    link=":/wei/enemy2.png";
    live=false;
    body=true;
}
