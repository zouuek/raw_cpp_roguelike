#include "Armor.h"

Armor::Armor(double reduction) : Item("armor"), reduction(reduction) {
	this->isArmor = true;
};