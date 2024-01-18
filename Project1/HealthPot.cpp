#include "HealthPot.h"
//#include "Entity.h"

HealthPot::HealthPot(int heal): Item("Health Potion"), healing(heal) {
	isHealthPot = true;
};
//void HealthPot::consume(Entity* en) {
//	en->heal(this->healing);
//}
