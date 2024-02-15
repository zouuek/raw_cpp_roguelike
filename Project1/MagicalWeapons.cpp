#include "MagicalWeapons.h"

LightningRod::LightningRod() : Weapon(1, 140 ,"Rod of Lightning") {
	isMagical = true;
	level = 12;
}
FireWand::FireWand() : Weapon(100, 120, "Wand of Fire"){
	isMagical = true;
	level = 15;
}

WerecatsNightBow::WerecatsNightBow() : Weapon(50,90,"Werecat's Night Bow")
{
	isMagical = true;
	level = 9;
}
MysticPaw::MysticPaw() : Weapon(65, 85, "Mystic Paw") {
	isMagical = true;
	level = 5;
}

ForestWhisper::ForestWhisper() : Weapon(80, 100, "Forest Whisper") {
	isMagical = true;
}
AstralBatBat::AstralBatBat() : Weapon(20, 30, "Astral Bat Bat") {
	isMagical = true;
}

SmallSizedFireWand::SmallSizedFireWand(): Weapon(30,80, "Small Sized Wand of Fire") {
	isMagical = true;
}
