#include "tower.h"

tower::tower()
{

}
void tower::attack(int a){
    if(a<=200)area+=2;
    else area=0;
}
void tower::settower(int x,int y){
    live=true;
    towerx=x;
    towery=y;
}
void tower::upgrade(){
    level++;
    link=":/wei/tower2.png";
}
void tower::sell(){
    live=false;
}
