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
		maxHP = 1000;
		currHP = maxHP;
		strenght = 23;
		agility = 5;
		intellect = 5;
	}
	else if (type == boar) {
		symb = 'B';
		name = "Boar";
		maxHP = 1000;
		currHP = maxHP;
		strenght = 20;
		agility = 8;
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

double Entity::calcDodgeChance(){
	double max = 50;
	if (this->agility * 2.5 > max) return max;
	return this->agility * 2.5;
}

bool Entity::dodge(){
	int ran = rand() % 100 + 1;
	return this->calcDodgeChance() > ran;
}

int Entity::calcDMG(){
	int critNum = rand() % 100 + 1;
	short diceRoll = rand() % 6 + 1;
	double diceMultiplier = ((diceRoll - 1) * 0.02) + 1;
	if (critNum < this->calcCritChance()) {
		//std::cout << "\n" << "CRITICAL HIT!" << '\n';                                           // zakomentowane do test�w
		return 1 + this->strenght * 1.05 * this->calcCritMultiplier() * diceMultiplier;
	}
	else return 1 + this->strenght * 1.05 * diceMultiplier;
}
