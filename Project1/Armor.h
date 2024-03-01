#pragma once
#include "Item.h"
class Armor :
    public Item
{
public:
    double reduction;
    int level;
    int armorPoints = 0;
    Armor(double reduction, string name);
    void use(Entity* wearer) override;
};
class Fur :
    public Armor {
public:
    Fur();
};
class BoarhideGuard : public Armor {
public:
    BoarhideGuard();
};

class ShadowCloak : public Armor {
public:
    ShadowCloak();
};

class WolfPelt : public Armor {
public:
    WolfPelt();
};
class EnchantedFur : public Armor {
public:
    EnchantedFur();
};

class EldritchBark : public Armor {
public:
    EldritchBark();
};

class BatWingCloak : public Armor {
public:
    BatWingCloak();
};
class SmallSizedLeatherArmor : public Armor {
public:
    SmallSizedLeatherArmor();
};
class RibCage : public Armor {
public:
    RibCage();
};
class ClothShirt : public Armor{
public:
    ClothShirt();
};