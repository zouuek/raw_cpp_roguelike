#pragma once
#include <vector>
#include "Entity.h"
using std::vector;
class Field {
public:
	char symb;
	bool walkable;
	Entity* istota = nullptr;
	vector<Item*> przedmioty;
	enum types
	{
		wall,
		floor
	};
	Field(char symb, bool walkable, Entity* istota);
	Field(char symb, bool walkable);
	Field(types type);
	

};