#pragma once
//#include "Entity.h"
#include "Item.h"

class HealthPot :
   public Item
{
public: 
    int healing;
    HealthPot(int heal);
   // void consume(Entity* en);
};

