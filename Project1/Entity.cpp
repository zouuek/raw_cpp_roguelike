#include <iostream>
#include <string>
#include "Entity.h"
#include <random>
using std::string;



Entity::Entity(char symb, string name, int x, int y) : symb(symb), name(name), x(x), y(y) {};
Entity::Entity(types type) {
	if (type == player) {
		symb = '@';
		name = "Chlystek";
		maxHP = 10000;
		currHP = maxHP;
		strenght = 20;
		agility = 5;
		intellect = 5;
	}
	else if (type == boar) {
		symb = 'B';
		name = "Boar";
		maxHP = 10000;
		currHP = maxHP;
		strenght = 20;
		agility = 5;
		intellect = 1;
	}
};
string Entity::displayHP() const
{
	return "(" + std::to_string(this->currHP) + "/" + std::to_string(this->maxHP) + ")";
}
//double Entity::calcCritChance() {
//	return agility * 0, 01;
//}
bool Entity::isDead() const {
	return this->currHP <= 0;
}

int Entity::calcCritChance() const{
	if (this->agility * 100 * 0.05 > 100) {
		return 100;
	}
	return this->agility * 0.05 * 100;
}


void Entity::dealDamage(Entity* target, int dmg) {
	target->currHP -= dmg;
}
double Entity::calcCritMultiplier() {
	return (this->strenght * 0.015) + 1;
}

void Entity::heal(int num){
	this->currHP += num;
	if (this->currHP > this->maxHP) {
		this->currHP = this->maxHP;
	}
}

int Entity::calcDMG(){
	int critNum = rand() % 100 + 1;
	short diceRoll = rand() % 6 + 1;
	double diceMultiplier = ((diceRoll - 1) * 0.02) + 1;
	if (critNum < this->calcCritChance()) {
		//std::cout << "\n" << "CRITICAL HIT!" << '\n';                                           // zakomentowane do testów
		return 1 + this->strenght * 1.05 * this->calcCritMultiplier() * diceMultiplier;
	}
	else return 1 + this->strenght * 1.05 * diceMultiplier;
}
