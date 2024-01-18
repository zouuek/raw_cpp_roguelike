#pragma once
#include "Entity.h";
#include "Item.h";
#include "Field.h";

using std::cout;
using std::endl;
using std::cin;

class Map {
public:
	int width=5, height=5;
	vector<vector<Field>> pola = { {Field(Field::wall),  Field(Field::wall),  Field(Field::wall),  Field(Field::wall), Field(Field::wall)},
								{Field(Field::wall), Field(Field::floor), Field(Field::floor), Field(Field::floor), Field(Field::wall)},
								{Field(Field::wall), Field(Field::floor), Field(Field::floor), Field(Field::floor), Field(Field::wall)},
								{Field(Field::wall), Field(Field::floor), Field(Field::floor), Field(Field::floor), Field(Field::wall)},
								{Field(Field::wall),  Field(Field::wall),  Field(Field::wall),  Field(Field::wall), Field(Field::wall)} };
	vector <Entity*> entities;
	vector <Item*> items;


	void initEntities();

	void displayMap() const;

	bool isWithinBounds(int x, int y) const;

	bool canPlaceEntity(int x, int y) const;
	bool canPlaceItem(int x, int y) const;

	void moveEntity(Entity* ist, int dx, int dy);

	void listEntities() const;
	void listItems() const;

	void removeEntity(Entity* istota);
	void removeItem(int x, int y, Item* item);
	void delEntityByPlace(int x, int y);
	void delItemByPlace(int x, int y);
	void changeTile(int x, int y, Field new_pole);
	void addItem(int x, int y, Item* item);
	void addEntity(int x, int y, Entity* ent);

	std::pair<int, int> ableToStartFight(Entity* a);
	Entity* Fight(Entity* a, Entity* b);

	void entityPickUpItem(Entity* ent);

};
