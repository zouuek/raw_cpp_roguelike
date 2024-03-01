#pragma once
#include "Weapon.h"

class MagicalWeapon :
    public Weapon {
public:
    int getAttack(Entity* wearer) override;
    MagicalWeapon(int min, int max, string name);
};

class LightningRod :
    public MagicalWeapon
{
public:
    LightningRod();
};
class FireWand :
    public MagicalWeapon
{
public:
    FireWand();
};
class WerecatsNightBow :
    public MagicalWeapon
{
public:
    WerecatsNightBow();
};
class MysticPaw : public MagicalWeapon {
public:
    MysticPaw();
};

class ForestWhisper : public MagicalWeapon {
public:
    ForestWhisper();
};
class AstralBatBat : public MagicalWeapon {
public:
    AstralBatBat();
};
class SmallSizedFireWand : public MagicalWeapon {
public:
    SmallSizedFireWand();
};
