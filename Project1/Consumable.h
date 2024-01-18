#pragma once
#include "Item.h"
#include "Entity.h"

class Consumable :
    public Item
{
public:
    Consumable();
    Consumable(string name);
    void consume(Entity* en);
};

/// ROZDZIELK TO NA DWA PLIKI I TO PIERDOL ZA DUZO ZABAWY
// w usuwaniu potiona popatrz na tego stacka

