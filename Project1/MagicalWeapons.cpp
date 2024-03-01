#include "MagicalWeapons.h"
#include "Entity.h"


LightningRod::LightningRod() : MagicalWeapon(1, 140 ,"Rod of Lightning") {
	level = 12;
}
FireWand::FireWand() : MagicalWeapon(100, 120, "Wand of Fire"){
	level = 15;
}

WerecatsNightBow::WerecatsNightBow() : MagicalWeapon(50,90,"Werecat's Night Bow")
{
	level = 9;
}
MysticPaw::MysticPaw() : MagicalWeapon(65, 85, "Mystic Paw") {
	level = 5;
}

ForestWhisper::ForestWhisper() : MagicalWeapon(80, 100, "Forest Whisper") {
}
AstralBatBat::AstralBatBat() : MagicalWeapon(20, 30, "Astral Bat Bat") {
}

SmallSizedFireWand::SmallSizedFireWand(): MagicalWeapon(30,80, "Small Sized Wand of Fire") {
}

int MagicalWeapon::getAttack(Entity* wearer){
	return this->min + rand() % ((this->max + 1) - this->min) + wearer->strenght * 1.05;
}
MagicalWeapon::MagicalWeapon(int min, int max, string name) : Weapon(min, max, name) {
}
