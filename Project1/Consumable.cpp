#include "Consumable.h"


Consumable::Consumable() : Item("null") {}
Consumable::Consumable(string name) : Item(name){};
void Consumable::consume(Entity* en)
{
}

