#include "EntityBase.h"

enum biom {
	forest,
	cave
};



Player::Player(){
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

Spider::Spider(){
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

Bat::Bat(){
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

Cobolt::Cobolt(){
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
Demilich::Demilich() {
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

Skeleton::Skeleton(){
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

Boar::Boar(){
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
}

Wolf::Wolf(){
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

Rogue::Rogue(){
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

Werecat::Werecat(){
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

Sloth::Sloth(){
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

Leshy::Leshy(){
	symb = 'L';
	name = "Leshy";
	maxHP = 1000;
	currHP = maxHP;
	strenght = 9;
	agility = 10;
	intellect = 15;
	weapon = new FireWand();
	armor = new EldritchBark();
	level = 15;
	environment = { "Forest", 1 };
}

Lich::Lich(){
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
