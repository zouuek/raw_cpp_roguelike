#pragma once
#include "Weapon.h"
class PhysicalWeapon :
    public Weapon
{
public:
    int getAttack(Entity* wearer) override;
    PhysicalWeapon(int min, int max, string name);
};


class RustedDagger :
    public PhysicalWeapon
{
public:
    RustedDagger();
};
class BoarTusk :
    public PhysicalWeapon
{
public:
    BoarTusk();
};
class ClawedGloves :
    public PhysicalWeapon
{
public:
    ClawedGloves();
};
class TusksOfRampage : public PhysicalWeapon {
public:
    TusksOfRampage();
};

class Shadowblade : public PhysicalWeapon {
public:
    Shadowblade();
};

class MoonlitHowler : public PhysicalWeapon {
public:
    MoonlitHowler();
};
class SpiderClaw :
    public PhysicalWeapon
{
public:
    SpiderClaw();
};
class SpinalCord :
    public PhysicalWeapon {
public:
    SpinalCord();
};

