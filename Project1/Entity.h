#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Armor.h"
#include "HealthPot.h"
#include "MagicalWeapons.h"
#include "PhysicalWeapons.h"
#include <random>




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
	int level;
	int experience;
	int armorPoints;
	std::vector<Item*> eq;
	std::vector<int> listOfLvls = { 1,3,5,9,15 };
	bool isPlayer = false;
	std::pair<string, int> environment;
	int gold = 0;

	Weapon* weapon = nullptr;
	Armor* armor = nullptr;
	
	int levelThresholds[16]{ 0 ,10, 30, 100, 120, 180, 200, 200, 200, 200, 200, 200, 200, 200, 200, 1000000 };
	

	enum types {
		// player
		player,
		// woods
		boar,			//wojow
		wolf,			//tanc		
		rzezimierch,	//³ow
		kotolak,		//trop
		leszy,			//pal
		// caves
		spider,
		bat,
		skeleton,
		troll,
		lich
	};
	

	Entity();
	Entity(char symb, string name, int x, int y);
	Entity(types type);
	Entity(int level, int e);

	string displayHP() const;
	bool isDead() const;
	int calcCritChance() const;
	void dealDamage(Entity* target, int dmg);
	int calcDMG();
	double calcCritMultiplier();
	void heal(int num);
	double calcDodgeChance();
	bool dodge();
	bool canAttack(Entity* oth);

	void equipItem(int index);
	void examineSelf();
	void consumeItem(HealthPot* consumable);
	
	void showInventory();

	int calcExperience();
	void levelUp();
	void event();
	virtual void manageFightAI(Entity* target);

	
	
};