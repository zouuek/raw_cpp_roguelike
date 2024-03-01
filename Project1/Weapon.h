#pragma once
#include "Item.h"
class Weapon :
    public Item
{
public:
    int min;
    int max;
    int level;
    
    //string name;
    Weapon(int min, int max, string name);
    virtual int getAttack(Entity* wearer);
    void use(Entity* user) override;
};

