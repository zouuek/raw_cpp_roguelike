#include "LightningRod.h"

LightningRod::LightningRod() : Weapon(1, 500 ,"Rod of Lightning") {
	isMagical = true;
}
FireWand::FireWand() : Weapon(150, 240, "Wand of Fire"){
	isMagical = true;
}