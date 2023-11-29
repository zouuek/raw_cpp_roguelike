#pragma once
#include <iostream>
#include <string>
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

	enum types {
		player,
		boar
	};

	Entity(char symb, string name, int x, int y);
	Entity(types type);

	string displayHP() const;
	bool isDead() const;
	int calcCritChance() const;
	void dealDamage(Entity* target, int dmg);
	int calcDMG();
	double calcCritMultiplier();
	void heal(int num);
};