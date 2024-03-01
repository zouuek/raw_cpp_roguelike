#pragma once
#include <string>
//#include "Entity.h"
class Entity;

using std::string;

class Item {
public:
	string name;
	Item(string name);
	virtual void use(Entity* wearer);
};