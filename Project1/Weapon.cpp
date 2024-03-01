#include "Weapon.h"
#include "Entity.h"
Weapon::Weapon(int min, int max, string name) : Item(name), min(min), max(max) {
}
int Weapon::getAttack(Entity* wearer)
{
	return this->min + rand() % ((this->max + 1) - this->min);
}

void Weapon::use(Entity* user){
	user->eq.push_back(user->weapon);
	user->weapon = this;
}


