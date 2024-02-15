#include "Weapon.h"

Weapon::Weapon(int min, int max, string name) : Item(name), min(min), max(max) {
	this->isWeapon = true;
}
int Weapon::getAttack()
{
	return this->min + rand() % ((this->max + 1) - this->min);
}


;