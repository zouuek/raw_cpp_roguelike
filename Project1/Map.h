#pragma once
#include "Field.h";
#include <queue>
#include <random>
#include <algorithm>
#include <utility>
#include <map>
#include <iostream>
#include <conio.h>

using std::cout;
using std::endl;
using std::cin;

class Map {
public:
	int width, height;
	vector<vector<Field>> pola;
	vector <Entity*> entities;
	vector <Item*> items;
	string type;

	enum type
	{
		cave,
		forest,
		merchant,
		boss_cave,
		boss_forest

	};

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
	void generateCave(Entity* player);
	void generateForest(Entity* player);
	bool dfs(int x, int y);
	void chasePlayer(Entity* chaser, Entity* player);
	bool isPlayerInRange(Entity* chaser, Entity* player, int range) const;
	bool entityNotInRange(int x, int y);
	bool noTreesInRange(int x, int y);
	int znajdzNajblizszaLiczbe(int liczba, const std::vector<int>& lista);
	void fleePlayer(Entity* fleer, Entity* player);
	void refresh();

	void randomLoot(Entity* looter, Entity* ofTheDead);

	int distanceToBorder(int x, int y);

	void generateBossRoomCave(Entity* player);
	void generateBossRoomForest(Entity* player);
	void searchForFights();
	void manageEntityAI();
	void checkDoors(Entity* player, int forestDepth, int cavesDepth, Entity* boss);

	Entity* generateEntity(int level, int biom_id);

};
