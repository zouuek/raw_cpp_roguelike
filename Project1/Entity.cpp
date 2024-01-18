#include <iostream>
#include <string>
#include "Entity.h"
#include <random>
#include "Consumable.h"
using std::string;



Entity::Entity(char symb, string name, int x, int y) : symb(symb), name(name), x(x), y(y) {};
Entity::Entity(types type) {
	if (type == player) {
		symb = '@';
		name = "Chlystek";
		maxHP = 1000;
		currHP = maxHP;
		strenght = 10;
		agility = 5;
		intellect = 5;
		armor = new Armor(0.0);
		weapon = new LightningRod();
	}
	else if (type == boar) {
		symb = 'B';
		name = "Boar";
		maxHP = 100000;
		currHP = maxHP;
		strenght = 8;
		agility = 3;
		intellect = 1;
		weapon = new Weapon(30, 40, "def");
		weapon->isPhysical = true;
		armor = new Armor(0.0);
	}
	else if (type == rzezimierch) {
		symb = 'B';
		name = "Rzezimierch";
		maxHP = 1000;
		currHP = maxHP;
		strenght = 8;
		agility = 11;
		intellect = 4;
	}
	else if (type == wolf) {
		symb = 'W';
		name = "Wilczur";
		maxHP = 700;
		currHP = maxHP;
		strenght = 10;
		agility = 10;
		intellect = 2;
	}
	else if (type == kotolak) {
		symb = 'K';
		name = "Kotolak";
		maxHP = 600;
		currHP = maxHP;
		strenght = 10;
		agility = 20;
		intellect = 9;
	}
	else if (type == leszy) {
		symb = 'L';
		name = "Leszy";
		maxHP = 1300;
		currHP = maxHP;
		strenght = 12;
		agility = 10;
		intellect = 10;
		armor = new Armor(0.2);
		weapon = new FireWand();
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
	if (target->armor) {
		target->currHP -= dmg * (1-target->armor->reduction);
	}
	else {
		target->currHP -= dmg;
	}
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

int Entity::calcPhysicalDMG(){
	int critNum = rand() % 100 + 1;
	short diceRoll = rand() % 6 + 1;
	double diceMultiplier = ((diceRoll - 1) * 0.02) + 1;
	if (critNum < this->calcCritChance()) {
		//std::cout << "+CRITICAL HIT" << '\n';                                           // zakomentowane do testów
		if (this->weapon) {
			return (this->weapon->getAttack() + this->strenght * 1.05) * this->calcCritMultiplier() * diceMultiplier;
		}else return 1 + this->strenght * 1.05 * this->calcCritMultiplier() * diceMultiplier;
	}
	else {
		if (this->weapon) {
			
			return (this->weapon->getAttack() + this->strenght * 1.05) * diceMultiplier;
		}
		else return 1 + this->strenght * 1.05 * diceMultiplier;
	}
}

int Entity::calcMagicalDMG()
{
	int critNum = rand() % 100 + 1;
	short diceRoll = rand() % 6 + 1;
	double diceMultiplier = ((diceRoll - 1) * 0.02) + 1;
	if (critNum < this->calcCritChance()) {
		//std::cout << "+CRITICAL HIT" << '\n';                                           // zakomentowane do testów
		if (this->weapon) {
			return (this->weapon->getAttack() + this->intellect * 1.05) * this->calcCritMultiplier() * diceMultiplier;
		}
		else return 1 + this->intellect * 1.05 * this->calcCritMultiplier() * diceMultiplier;
	}
	else {
		if (this->weapon) {

			return (this->weapon->getAttack() + this->intellect * 1.05) * diceMultiplier;
		}
		else return 1 + this->intellect * 1.05 * diceMultiplier;
	}
}


void Entity::equipItem(int index) {
	if (this->eq[index]) {
		if (this->eq[index]->isWeapon) {
			if (!this->weapon) {
				this->weapon = (Weapon*)eq[index];
				this->eq.erase(eq.begin() + index);
			}
			else {
				this->eq.push_back(weapon);
				this->weapon = (Weapon*)eq[index];
				this->eq.erase(eq.begin() + index);
			}
		}
		else if (this->eq[index]->isArmor) {
			this->armor = (Armor*)eq[index];
			this->eq.erase(eq.begin() + index);
		}
		else if (this->eq[index]->isHealthPot) {
			this->consumeItem((HealthPot*)eq[index]);
		}
	}
	else return;
}

void Entity::examineSelf()
{
	std::cout << this->name << '\n';
	std::cout << "~~STATISTICS~~\n" <<
		"Health: (" << this->currHP << ") / (" << this->maxHP << ")\n" <<
		"Strenght: " << this->strenght << '\n' <<
		"Agility: " << this->agility << '\n' <<
		"~~EQUIPMENT~~\n" <<
		"Armor: " << this->armor->name << " - " << this->armor->reduction * 100 << "% damage reduction \n" <<
		"Weapon: " << this->weapon->name << " (" << this->weapon->min << " - " << this->weapon->max << ") attack\n";
	showInventory();
		
}

void Entity::consumeItem(HealthPot* consumable) {
	this->heal(consumable->healing);
	this->eq.erase(std::remove(eq.begin(), eq.end(), consumable), eq.end());
}

void Entity::showInventory() {
	"~~INVENTORY~~\n"
		;
	for (int i = 0; i < this->eq.size(); i++) {
		std::cout << i << "." << this->eq[i]->name << '\n';
	}
}




