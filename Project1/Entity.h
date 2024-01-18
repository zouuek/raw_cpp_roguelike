#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Armor.h"
#include "Weapon.h"
#include "HealthPot.h"
#include "LightningRod.h"

using std::string;


class Entity {
public:
	int x, y;
	int last_x, last_y;
	char symb;
	string name;
	int maxHP;
	int currHP;
	int strenght;
	int agility;
	int intellect;
	int distance;
	std::vector<Item*> eq;

	Weapon* weapon = nullptr;
	Armor* armor = nullptr;
	

	enum types {
		// player
		player,
		// woods
		boar,			//wojow
		wolf,			//tanc		
		rzezimierch,	//³ow
		kotolak,		//trop
		leszy			//pal
		// caves

	};


	Entity(char symb, string name, int x, int y);
	Entity(types type);

	string displayHP() const;
	bool isDead() const;
	int calcCritChance() const;
	void dealDamage(Entity* target, int dmg);
	int calcPhysicalDMG();
	int calcMagicalDMG();
	double calcCritMultiplier();
	void heal(int num);
	double calcDodgeChance();
	bool dodge();
	bool canAttack(Entity* oth);

	void equipItem(int index);
	void examineSelf();
	void consumeItem(HealthPot* consumable);
	
	void showInventory();
};