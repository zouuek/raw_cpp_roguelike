#pragma once
#include "Item.h"
class Armor :
    public Item
{
public:
    double reduction;
    Armor(double reduction);
};

