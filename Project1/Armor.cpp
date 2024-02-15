#include "Armor.h"

Armor::Armor(double reduction,string name) : Item(name), reduction(reduction) {
	this->isArmor = true;
};
Fur::Fur() : Armor(0.15, "Animal Fur") {
	level = 2;
};
BoarhideGuard::BoarhideGuard() : Armor(0.15, "Boarhide Guard") {
    level = 5;
}

ShadowCloak::ShadowCloak() : Armor(0.25, "Shadow Cloak") {
    level = 8;
}

WolfPelt::WolfPelt() : Armor(0.2, "Wolf Pelt") {
    level = 7;
}
EnchantedFur::EnchantedFur() : Armor(0.3, "Enchanted Fur") {
    level = 9;
}

EldritchBark::EldritchBark() : Armor(0.35, "Eldritch Bark") {
    level = 15;
}
BatWingCloak::BatWingCloak() : Armor(0.15, "Bat Wing Cloak") {
    level = 7;
}

SmallSizedLeatherArmor::SmallSizedLeatherArmor() : Armor(0.2, "Small Sized Leather Armor") {
    level = 8;
}

RibCage::RibCage(): Armor(0.30, "RibCage"){
    level = 10;
}
ClothShirt::ClothShirt() : Armor(0.1, "Linen Cloth Shirt") {
    level = 0;
}