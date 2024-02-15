#pragma once
#include <string>



using std::string;

class Item {
public:
	string name;
	bool isWeapon = false;
	bool isArmor = false;
	bool isHealthPot = false;
	Item(string name);
};