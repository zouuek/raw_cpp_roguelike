#include "PhysicalWeapons.h"
#include "Entity.h"

int PhysicalWeapon::getAttack(Entity* wearer) {
	return this->min + rand() % ((this->max + 1) - this->min) + wearer->strenght * 1.05;
}
PhysicalWeapon::PhysicalWeapon(int min, int max, string name) : Weapon(min, max, name) {
}

RustedDagger::RustedDagger() :PhysicalWeapon(5, 20, "Rusted Dagger"){
	level = 2;
}
BoarTusk::BoarTusk() :PhysicalWeapon(10, 30, "Boar Tusk") {
	level = 1;
}
ClawedGloves::ClawedGloves() : PhysicalWeapon(1, 120, "Clawed Gloves") {
	level = 4;
}
TusksOfRampage::TusksOfRampage() : PhysicalWeapon(25, 40, "Tusks of Rampage") {
	level = 3;
}

Shadowblade::Shadowblade() : PhysicalWeapon(45, 60, "Shadowblade") {
	level = 5;
}

MoonlitHowler::MoonlitHowler() : PhysicalWeapon(50, 70, "Moonlit Howler") {
	level = 6;
}
SpiderClaw::SpiderClaw() : PhysicalWeapon(5, 40, "Spider Claw") {
	level = 1;
}

SpinalCord::SpinalCord() : PhysicalWeapon(30, 90, "Spinal Cord") {
}

