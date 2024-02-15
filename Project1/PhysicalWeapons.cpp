#include "PhysicalWeapons.h"

RustedDagger::RustedDagger() :Weapon(5, 20, "Rusted Dagger"){
	isPhysical = true;
	level = 2;
}
BoarTusk::BoarTusk() :Weapon(10, 30, "Boar Tusk") {
	isPhysical = true;
	level = 1;
}
ClawedGloves::ClawedGloves() : Weapon(1, 120, "Clawed Gloves") {
	isPhysical = true;
	level = 4;
}
TusksOfRampage::TusksOfRampage() : Weapon(25, 40, "Tusks of Rampage") {
	isPhysical = true;
	level = 3;
}

Shadowblade::Shadowblade() : Weapon(45, 60, "Shadowblade") {
	isPhysical = true;
	level = 5;
}

MoonlitHowler::MoonlitHowler() : Weapon(50, 70, "Moonlit Howler") {
	isPhysical = true;
	level = 6;
}
SpiderClaw::SpiderClaw() : Weapon(5, 40, "Spider Claw") {
	isPhysical = true;
	level = 1;
}

SpinalCord::SpinalCord() : Weapon(30, 90, "Spinal Cord") {
	isPhysical = true;
}

