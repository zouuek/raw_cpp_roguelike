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
		strenght = 5;
		agility = 5;
		intellect = 5;
		armor = new ClothShirt();
		weapon = new RustedDagger();
		level = 1;
		experience = 0;
		isPlayer = true;
	}
	else if (type == boar) {
		symb = 'B';
		name = "Boar";
		maxHP = 100;
		currHP = maxHP;
		strenght = 8;
		agility = 3;
		intellect = 1;
		weapon = new Weapon(30, 40, "def");
		weapon->isPhysical = true;
		armor = new Fur();
		level = 6;
		environment = { "Forest", 1 };
	}
	else if (type == rzezimierch) {
		symb = 'R';
		name = "Rzezimierch";
		maxHP = 1000;
		currHP = maxHP;
		strenght = 8;
		agility = 11;
		intellect = 4;
		level = 5;
		environment = { "Forest", 1 };
	}
	else if (type == wolf) {
		symb = 'W';
		name = "Wilczur";
		maxHP = 700;
		currHP = maxHP;
		strenght = 10;
		agility = 8;
		intellect = 2;
		level = 3;
		environment = { "Forest", 1 };
	}
	else if (type == kotolak) {
		symb = 'K';
		name = "Kotolak";
		maxHP = 600;
		currHP = maxHP;
		strenght = 10;
		agility = 20;
		intellect = 13;
		level = 9;
		environment = { "Forest", 1 };
	}
	else if (type == leszy) {
		symb = 'L';
		name = "Leszy";
		maxHP = 1300;
		currHP = maxHP;
		strenght = 9;
		agility = 10;
		intellect = 15;
		//armor = new Armor(0.2);
		weapon = new FireWand();
		level = 15;
		environment = { "Forest", 1 };
	}
	else if (type == spider) {
		symb = 'S';
		name = "Spider";
		maxHP = 100;
		currHP = maxHP;
		strenght = 8;
		agility = 3;
		intellect = 1;
		weapon = new Weapon(30, 40, "def");
		weapon->isPhysical = true;
		armor = new Fur();
		level = 6;
		environment = { "Forest", 1 };
	}
	else if (type == bat) {
		symb = 'b';
		name = "Bat";
		maxHP = 100;
		currHP = maxHP;
		strenght = 8;
		agility = 3;
		intellect = 1;
		weapon = new Weapon(30, 40, "def");
		weapon->isPhysical = true;
		armor = new Fur();
		level = 6;
		environment = { "Forest", 1 };
	}
	//else if (type == )
	
}
Entity::Entity() {};
Entity::Entity(int lvl, int e)
{

	if (e == 1) {
		if (lvl == 1) {
			symb = 'B';
			name = "Boar";
			maxHP = 100;
			currHP = maxHP;
			strenght = 8;
			agility = 3;
			intellect = 1;
			weapon = new BoarTusk();
			armor = new Fur();
			level = 1;
			//isPlayer = true;
		}
		else if (lvl == 5) {
			symb = 'R';
			name = "Rogue";
			maxHP = 150;
			currHP = maxHP;
			strenght = 8;
			agility = 11;
			intellect = 4;
			level = 5;
			weapon = new Shadowblade();
			armor = new ShadowCloak();
			environment = { "Forest", 1 };
		}
		else if (lvl == 3) {
			symb = 'W';
			name = "Wolf";
			maxHP = 120;
			currHP = maxHP;
			strenght = 8;
			agility = 8;
			intellect = 2;
			level = 3;
			weapon = new TusksOfRampage();
			armor = new WolfPelt();
			environment = { "Forest", 1 };
		}
		else if (lvl == 9) {
			symb = 'w';
			name = "Werecat";
			maxHP = 90;
			currHP = maxHP;
			strenght = 2;
			agility = 15;
			intellect = 6;
			level = 9;
			weapon = new WerecatsNightBow();
			armor = new EnchantedFur();
			environment = { "Forest", 1 };
		}
		else if (lvl == 15) {
			symb = 'L';
			name = "Leshy";
			maxHP = 1000;
			currHP = maxHP;
			strenght = 9;
			agility = 10;
			intellect = 15;
			//armor = new Armor(0.2);
			weapon = new FireWand();
			armor = new EldritchBark();
			level = 15;
			environment = { "Forest", 1 };
		}
		else if (lvl == 12) {
			symb = '$';
			name = "Sloth";
			maxHP = 230;
			currHP = maxHP;
			strenght = 7;
			agility = 13;
			intellect = 3;
			level = 12;
			weapon = new ClawedGloves();
			armor = new EnchantedFur();
			environment = { "Forest", 1 };
		}
	}
	else if (e == 2) {
		if (lvl == 1) {
			symb = 's';
			name = "Spider";
			maxHP = 100;
			currHP = maxHP;
			strenght = 6;
			agility = 5;
			intellect = 3;
			level = 1;
			weapon = new SpiderClaw();
			armor = new Fur();
			environment = { "Caves", 2 };
		}
		else if (lvl == 3) {
			symb = 'b';
			name = "Bat";
			maxHP = 100;
			currHP = maxHP;
			strenght = 2;
			agility = 6;
			intellect = 5;
			level = 3;
			weapon = new AstralBatBat();
			armor = new BatWingCloak();
			environment = { "Caves", 2 };
		}
		else if (lvl == 5) {
			symb = 'C';
			name = "Cobold";
			maxHP = 150;
			currHP = maxHP;
			strenght = 1;
			agility = 9;
			intellect = 7;
			level = 5;
			weapon = new SmallSizedFireWand();
			armor = new SmallSizedLeatherArmor();
			environment = { "Caves", 2 };
		}
		else if (lvl == 12) {
			symb = 'S';
			name = "Skeleton";
			maxHP = 200;
			currHP = maxHP;
			strenght = 12;
			agility = 6;
			intellect = 3;
			level = 12;
			weapon = new SpinalCord();
			armor = new RibCage();
			environment = { "Caves", 2 };
		}
		else if (lvl == 9) {
			symb = 'D';
			name = "Demilich";
			maxHP = 170;
			currHP = maxHP;
			strenght = 2;
			agility = 1;
			intellect = 10;
			level = 12;
			weapon = new LightningRod();
			armor = new RibCage();
			environment = { "Caves", 2 };
		}
		else if (lvl == 15) {
			symb = 'L';
			name = "Lich";
			maxHP = 1000;
			currHP = maxHP;
			strenght = 8;
			agility = 8;
			intellect = 10;
			level = 15;
			weapon = new FireWand();
			armor = new EldritchBark();
			environment = { "Caves", 2 };
		}
	}
}
;
string Entity::displayHP() const
{
	return "(" + std::to_string(this->currHP) + "/" + std::to_string(this->maxHP) + ")";
}

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
			if (!this->armor) {
				this->armor = (Armor*)eq[index];
				this->eq.erase(eq.begin() + index);
			}
			else
			{
				this->eq.push_back(armor);
				this->armor = (Armor*)eq[index];
				this->eq.erase(eq.begin() + index);
			}
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
	std::cout <<"Level " << this->level << " (" << this->experience << "/" << levelThresholds[this->level] << ") exp\n";
	std::cout << "~~STATISTICS~~\n" <<
		"Health: (" << this->currHP << ") / (" << this->maxHP << ")\n" <<
		"Strenght: " << this->strenght << '\n' <<
		"Agility: " << this->agility << '\n' <<
		"Intellect: " << this->intellect << '\n' <<
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
	std::cout << "~~INVENTORY~~\n";
	if (this->eq.empty()) {
		std::cout << "Empty\n";
	}
	else {
		for (int i = 0; i < this->eq.size(); i++) {
			std::cout << i << "." << this->eq[i]->name << '\n';
		}
	}
}

int Entity::calcExperience()
{
	return this->level * 10;
}

void Entity::levelUp()
{
	if (this->experience >= levelThresholds[this->level]) {
		this->experience -= levelThresholds[this->level];
		level++;
	}
	else return;
	std::cout << "LEVEL UP!\n" << "U have 2 stat point to spend\n" << "1. Strenght\n2. Agility\n3. Intellect";
	string input;
	int pts = 2;
	while (pts) {
		std::cin >> input;
		if (input == "1") {
			this->strenght++;
			pts--;
		}
		else if (input == "3") {
			this->intellect++;
			pts--;
		}
		else if (input == "2") {
			this->agility++;
			pts--;
		}
		else std::cout << "Type in a valid statistic\n";
	}
	this->heal(this->maxHP);
	
}

void Entity::event(){
	int randomEvent = rand() % 3;
	switch (randomEvent)
	{
	case 0:
		std::cout << "You suddenly feel tired. You decide to set up a camp and take a nap.\nWhile napping, you hear something weird lurking around you. ";
		if (this->intellect >= 8) {
			std::cout << "You decide to make a really scary noise. The lurker runs away in fear!\n+33% HP gained from the rest\n";
			this->heal(this->maxHP / 3);
		}
		else {
			std::cout << "You decide to investigate. While approaching the lurker, you suddenly get hit in the head. All you can recognize is a feather falling to the ground\n" <<
				"You wake up. Your head hurts";
			this->heal((-1) * currHP / 5);
			if (!this->eq.empty()) {
				std::cout << ", and your pockets feel lighter\n";
				int dice = rand() % this->eq.size();
				this->eq.erase(eq.begin() + dice);
			}
			else std::cout << "\n";
		}
		break;
	case 1:
		std::cout << "While traveling, you notice a weird looking, top hat shaped backpack lying on bare ground.\nYou decide to examine it. On its back theres a note \"If you manage to grab something from me without touching me, you may keep it\"\n" <<
			"You wonder if theres a catch but your greed takes over. You stick out your hand and try to reach for an item.\n";
		if (this->agility >= 8) {
			std::cout << "You managed to grab something and pull it without touching the backpack. Its a health potion!\nWhile looking at your prize, the backpack magically disappears\n";
			this->eq.push_back(new HealthPot(100));
		}
		else {
			std::cout << "You try to grab something, but you accidentally touch one of the backpack inner walls. Nothing happens. You just take out the item and store it in your pocket. It was a healthpot.\n" <<
				"While contemplaining if you should keep it, the backpack disappears. You move on, feeling dumb for not taking everything.\n";
			this->experience = 0;
			this->eq.push_back(new HealthPot(100));
		}
		break;
	case 2:
		std::cout << "Admiring the landscapes, afar off you hear an old lady screaming\n" <<
			"- HELP, HELP SOMEBODY HELP ME!\n" << "You dont hesitate for a moment. Rushing to get there as soon as possible, you hear the scream turning into laughter\n" <<
			"You know that you've been fooled. It's a trap! You are getting jumped! There is no time to do anything different than fight with your bare fists.\n";
		if (this->strenght >= 8) {
			std::cout << "You've managed to stop the attack. The masked ambusher runs off in fear seeing your strenght. On his run he drops a money purse with some gold in it\n";
			this->gold += 100;
		}
		else {
			std::cout << "You are not strong enough to block upcoming attack from the aggresor. After the first hit you blackout. You dream of a chicken looking through your belongings\n" <<
				"You wake up hurt and robbed\n";
			this->currHP /= 5;
			this->gold = 0;
		}
		break;

	default:
		break;
	}
}

