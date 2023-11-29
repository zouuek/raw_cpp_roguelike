#include <vector>
#include "Entity.h";
#include "Item.h";
#include "Field.h"
using std::vector;


Field::Field(char symb, bool walkable, Entity* istota) : symb(symb), walkable(walkable), istota(istota) {
};
Field::Field(char symb, bool walkable) : symb(symb), walkable(walkable) {};
Field::Field(types type) {
	if (type == floor) {
		symb = '.';
		walkable = true;
	}
	if (type == wall) {
		symb = '#';
		walkable = false;
	}
}