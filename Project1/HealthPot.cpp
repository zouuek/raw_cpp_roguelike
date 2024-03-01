#include "HealthPot.h"
#include "Entity.h"


HealthPot::HealthPot(int heal): Item("Health Potion"), healing(heal) {
}
void HealthPot::use(Entity* user){
	user->heal(this->healing);

}
;

