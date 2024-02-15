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
    bool isRanged = false;
    int level;
    
    //string name;
    Weapon(int min, int max, string name);
    int getAttack();
    
};

