#include <utility>
#include <map>
#include <iostream>
#include <conio.h>
#include "Map.h"
#include <queue>

using std::cout;
using std::endl;
using std::cin;



void Map::initEntities() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (pola[i][j].istota) {
				entities.push_back(pola[i][j].istota);                       // do wyrzucenia
			}
		}
	}
}
void Map::displayMap() const {
	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 5; ++x) {
			if (pola[x][y].istota != nullptr) {
				cout << pola[x][y].istota->symb << ' ';
			}
			else if (!pola[x][y].przedmioty.empty()) {
				cout << 'P' << ' ';
			}
			else cout << pola[x][y].symb << ' ';
		}
		cout << endl;
	}
}
bool Map::isWithinBounds(int x, int y) const {
	return x >= 0 && x < width && y >= 0 && y < height;      //nie dzial
}
bool Map::canPlaceEntity(int x, int y) const {
	return pola[x][y].istota == nullptr && pola[x][y].walkable && isWithinBounds(x, y);
}
bool Map::canPlaceItem(int x, int y) const {
	return pola[x][y].walkable && isWithinBounds(x, y);
}
void Map::moveEntity(Entity* ist, int dx, int dy) {
	ist->last_x = ist->x;
	ist->last_y = ist->y;
	std::pair<int, int> currPos = { ist->x, ist->y };
	int newPosX = currPos.first + dx;
	int newPosY = currPos.second + dy;
	if (canPlaceEntity(newPosX, newPosY)) {
		pola[currPos.first][currPos.second].istota = nullptr;
		currPos.first = newPosX;
		currPos.second = newPosY;
		ist->x = newPosX;
		ist->y = newPosY;
		pola[newPosX][newPosY].istota = ist;
	}
}
void Map::listEntities() const {
	cout << "Entities on the map:" << endl;
	for (const auto& entity : entities) {
		cout << entity->name << " at (" << entity->x << ", " << entity->y << ")" << endl;
	}
}
void Map::listItems() const {
	cout << "Items on the map:" << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (!pola[i][j].przedmioty.empty()) {
				for (int k = 0; k < pola[i][j].przedmioty.size(); k++) {
					cout << pola[i][j].przedmioty[k]->name << " at (" << i << ", " << j << ")" << endl;
				}
			}
		}
	}
}

void Map::removeEntity(Entity* istota) {
	vector<Entity*>::iterator it;
	it = entities.begin();
	for (const auto& ents : entities) {
		if (*it == istota) {
			entities.erase(it);
			break;
		}
		it++;
	}
	pola[istota->x][istota->y].istota = nullptr;
}
void Map::removeItem(int x, int y, Item* item) {
	if (pola[x][y].przedmioty.empty()) {
		return;
	}
	else {
		vector<Item*>::iterator it;
		it = pola[x][y].przedmioty.begin();
		for (const auto& its : pola[x][y].przedmioty) {
			if (*it == item) {
				pola[x][y].przedmioty.erase(it);
				break;
			}
			it++;
		}
	}
}
void Map::delEntityByPlace(int x, int y) {
	if (!pola[x][y].istota) return;
	vector<Entity*>::iterator it;
	it = entities.begin();
	for (const auto& ents : entities) {
		if (*it == pola[x][y].istota) {
		entities.erase(it);
		break;
		}
		it++;
	}
	pola[x][y].istota = nullptr;
}
void Map::delItemByPlace(int x, int y) {
	if (pola[x][y].przedmioty.empty()) {
		return;
	}
	else {
		pola[x][y].przedmioty.pop_back();
	}
}

void Map::changeTile(int x, int y, Field new_pole) {
	pola[x][y] = new_pole;
}
void Map::addItem(int x, int y, Item* item) {
	if (canPlaceItem(x, y)) {
		pola[x][y].przedmioty.push_back(item);
	}
	else return;
}
void Map::addEntity(int x, int y, Entity* ent) {
	if (canPlaceEntity(x, y)) {
		ent->x = x;
		ent->y = y;
		pola[x][y].istota = ent;
		entities.push_back(ent);
	}
	else return;
}

std::pair<int, int> Map::ableToStartFight(Entity* a)
{	
	if (pola[a->x][a->y + 1].istota) return { a->x, a->y + 1 };
	else if (pola[a->x + 1][a->y].istota) return { a->x + 1, a->y };
	else if (pola[a->x - 1][a->y].istota) return { a->x - 1, a->y };
	else if (pola[a->x][a->y - 1].istota)	return { a->x, a->y - 1 };
	else return { -1, -1 };
}
//void clearDeadEnties() {
	
//}
Entity* Map::Fight(Entity* a, Entity* b) {
	Entity* attckr;
	std::queue<Entity*> q;
	int dmg;
	if (a->agility > b->agility){
		q.push(a); 
		q.push(b);
	}
	else if (a->agility < b->agility) {
		q.push(b);
		q.push(a);
	}
	else {
		if (rand() % 2) q.push(a), q.push(b);
		else q.push(b), q.push(a);
	}
	
	while (!a->isDead() && !b->isDead()) {
		attckr = q.front();
		q.pop();
		q.push(attckr);
		dmg = attckr->calcDMG();
		//cout << endl << attckr->name << " deals " << dmg << " to " << q.front()->name << "!\n";    // koment do testow
		attckr->dealDamage(q.front(), dmg);
	}
	if (a->isDead()) {
		//removeEntity(a);            //zakomentowane do testów
		return b;
	}
	else {
		//removeEntity(b);
		return a;
	}
}