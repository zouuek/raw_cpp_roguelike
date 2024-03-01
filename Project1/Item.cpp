#include <string>
#include "Item.h"
#include "Entity.h"
using std::string;

Item::Item(string name) : name(name) {}
void Item::use(Entity* wearer){}
;
