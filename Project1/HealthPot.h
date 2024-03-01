#pragma once

#include "Item.h"

class HealthPot :
   public Item
{
public: 
    int healing;
    HealthPot(int heal);
    void use(Entity* user) override;
};

