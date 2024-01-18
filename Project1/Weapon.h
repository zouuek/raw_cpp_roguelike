#pragma once
#include "Item.h"
class Weapon :
    public Item
{
public:
    int min;
    int max;
    bool isMagical = false;
    bool isPhysical = false;
    
    //string name;
    Weapon(int min, int max, string name);
    int getAttack();
    
};

