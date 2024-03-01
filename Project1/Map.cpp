#include "Map.h"
#include <string>
#include "EntityBase.h"

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
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
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
	if (newPosX < 0 || newPosY < 0) return;
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
	if (a->x != 0 && a->y != 0 && a->x != width - 1 && a->y != height - 1) {
		if (pola[a->x][a->y + 1].istota) return { a->x, a->y + 1 };
		else if (pola[a->x + 1][a->y].istota) return { a->x + 1, a->y };
		else if (pola[a->x - 1][a->y].istota) return { a->x - 1, a->y };
		else if (pola[a->x][a->y - 1].istota)	return { a->x, a->y - 1 };
		else return { -1, -1 };
	}
	else return { -1,-1 };
}

Entity* Map::Fight(Entity* a, Entity* b) {
	Entity* attckr;
	std::queue<Entity*> q;
	string action;
	int dmg;
	bool moved = false;
	int dealt = 0;
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
		moved = false;
		attckr = q.front();
		q.pop();
		q.push(attckr);
		dmg = attckr->calcDMG();
		if (attckr->isPlayer) {
			while (!moved) {
				//std::cin >> action;
				char in = _getch();
				if (in == '1') {
					if (!q.front()->dodge()) {
						attckr->dealDamage(q.front(), dmg);
						cout << attckr->name << attckr->displayHP() << " deals " << dmg * (1 - q.front()->armor->reduction) << " to " << q.front()->name << q.front()->displayHP() << "!\n";    // koment do testow
					}
					else cout << attckr->name << attckr->displayHP() << " deals " << 0 << " to " << q.front()->name << q.front()->displayHP() << "!\n" << "-DODGE\n";    // koment do testow
					moved = true;
				}
				else if (in == '2') {
					attckr->showInventory();
					if (!attckr->eq.empty()) {
						cin >> action;
						if (isdigit(action[0])) {
							attckr->equipItem(stoi(action));
							moved = true;
						}
					}
				}
			}
		}
		else attckr->manageFightAI(q.front());
	}
	if (a->isDead()) {
		            //zakomentowane do testów
		b->experience += a->calcExperience();
		b->levelUp();
		randomLoot(b, a);
		removeEntity(a);
		return b;
	}
	else {
		a->experience += b->calcExperience();
		a->levelUp();
		randomLoot(a, b);
		removeEntity(b);
		return a;
	}
}

void Map::entityPickUpItem(Entity* ent)
{
	if (!pola[ent->x][ent->y].przedmioty.empty()) {
		ent->eq.push_back(pola[ent->x][ent->y].przedmioty.front());
		pola[ent->x][ent->y].przedmioty.erase(pola[ent->x][ent->y].przedmioty.begin());

	}
}

void Map::generateForest(Entity* player)
{
	// randomowe wymiary mapy od 10 do 20
	int mapSize = std::rand() % 11 + 10;
	this->height = mapSize;
	this->width = mapSize;
	type = forest;

	pola.clear();
	pola.resize(height, vector<Field>(width, Field(Field::floor)));
	entities.clear();
	items.clear();




	int givenLevel;
	int entityCap = (int) (round((float)this->height/10) + 2);
	if (player->level > 10) { entityCap++; }

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == this->width / 2 && j == this->height - 2) pola[i][j] = Field(Field::floor);
			else {
				int distanceToBorder = this->distanceToBorder(i, j);
				if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
					if (i == width/3 -1 && j == 0 || i == width/3 * 2 && j == 0) {
						pola[i][j] = Field(Field::door);
					}
					else pola[i][j] = Field(Field::wall);
				}
				else if (distanceToBorder == 1) {
					if (rand() % 10 < 3 && i > 0 && j > 0) pola[i][j] = Field(Field::wall);
					else pola[i][j] = Field(Field::floor);
				}
				else if (distanceToBorder == 2) {
					if (rand() % 10 < 2) pola[i][j] = Field(Field::wall);
					else pola[i][j] = Field(Field::floor);
				}
				else if (rand() % 100 < 35 && noTreesInRange(i,j)) pola[i][j] = Field(Field::wall);
				else {
					pola[i][j] = Field(Field::floor);
					//if (i == player->x && j == player->y) pola[i][j].istota = player;

					 ///////////////////////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////// GENERACJA ENTITUW ////////////////////////////////////////////////
					std::random_device rd;
					std::mt19937 gen(rd());							//testuje nowoczesne generowanei lczb
					std::uniform_int_distribution<> range(0, 100);
					int givenNumber = range(gen);
					if (givenNumber <= 2) {
						givenLevel = std::max(player->level - 3, 1);
					}
					else if (givenNumber > 2 && givenNumber <= 16) {
						givenLevel = std::max(player->level - 2, 1); // ograniczenie, tak aby level by³ minimalnie pierwszy
					}
					else if (givenNumber > 16 && givenNumber <= 50) {
						givenLevel = std::max(player->level - 1, 1);
					}
					else if (givenNumber > 50 && givenNumber <= 84) {
						givenLevel = player->level;
					}
					else if (givenNumber > 84 && givenNumber <= 98) {
						givenLevel = std::min(player->level + 1, 12);  // ograniczenie górne
					}
					else if (givenNumber > 98 && givenNumber <= 100) {
						givenLevel = std::min(player->level + 2, 12);
					}
					givenLevel = znajdzNajblizszaLiczbe(givenLevel, player->listOfLvls);
					int modifier = 100;
					if (entityCap > 0) {

						if (rand() % 1000 < modifier && entityNotInRange(i,j)) {
							modifier = (modifier / 3) - (modifier / 5);
							this->addEntity(i, j, this->generateEntity(givenLevel, 0));
							entityCap--;
						}
					}
					/*	if (rand() % 1000 < 10) {
							int randomType = rand() % 10;                     // respienie itemuw na mapce
							if (randomType < 3) {
								this->addItem()
							}
						}*/
				}
			}
		}
	}
	this->addEntity(this->width / 2, height - 2, player);
	if (!dfs(player->x, player->y)) generateForest(player);
	else return;


}


bool Map::entityNotInRange(int x, int y) { // XD
	return !pola[x - (this->width/10 + 1)][y - (this->height / 10 + 1)].istota && !pola[x][y - (this->height / 10 + 1)].istota && !pola[x - (this->width / 10 + 1)][y].istota &&
		!pola[x + (this->width / 10 + 1)][y + (this->height / 10 + 1)].istota && !pola[x + (this->width / 10 + 1)][y].istota && !pola[x][y + (this->height / 10 + 1)].istota &&
		!pola[x + (this->width / 10 + 1)][y - (this->height / 10 + 1)].istota && !pola[x - (this->width / 10 + 1)][y + (this->height / 10 + 1)].istota
		&& !pola[x - (this->width / 10)][y - (this->height / 10)].istota && !pola[x][y - (this->height / 10)].istota && !pola[x - (this->width / 10)][y].istota &&
		!pola[x + (this->width / 10)][y + (this->height / 10)].istota && !pola[x + (this->width / 10)][y].istota && !pola[x][y + (this->height / 10)].istota &&
		!pola[x + (this->width / 10)][y - (this->height / 10)].istota && !pola[x - (this->width / 10)][y + (this->height / 10)].istota
		&& !pola[x - 1][y - 1].istota && !pola[x][y - 1].istota && !pola[x - 1][y].istota &&
		!pola[x + 1][y + 1].istota && !pola[x + 1][y].istota && !pola[x][y + 1].istota &&
		!pola[x - 1][y + 1].istota && !pola[x + 1][y - 1].istota;
}

bool Map::noTreesInRange(int x, int y) {
	return pola[x - 1][y - 1].walkable && pola[x][y - 1].walkable && pola[x - 1][y].walkable &&
		pola[x + 1][y + 1].walkable && pola[x + 1][y].walkable && pola[x][y + 1].walkable &&
		pola[x - 1][y + 1].walkable && pola[x + 1][y - 1].walkable;
}



void Map::generateBossRoomCave(Entity* player) {

	// randomowe wymiary mapy od 10 do 20
	int mapSize = std::rand() % 11 + 10;
	this->height = mapSize;
	this->width = mapSize;
	type = cave;

	pola.clear();
	pola.resize(height, vector<Field>(width, Field(Field::floor)));
	entities.clear();
	items.clear();




	int givenLevel;
	int entityCap = 1;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == this->width / 2 && j == this->height - 2) pola[i][j] = Field(Field::floor);
			else {
				int distanceToBorder = this->distanceToBorder(i, j);
				if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
					if (i == width / 3 - 1 && j == 0 || i == width / 3 * 2 && j == 0) {
						pola[i][j] = Field(Field::door);
					}
					else pola[i][j] = Field(Field::wall);
				}
				else if (distanceToBorder == 1) {
					if (rand() % 10 < 3 && i > 0 && j > 0) pola[i][j] = Field(Field::wall);
					else pola[i][j] = Field(Field::floor);
				}
				else if (distanceToBorder == 2) {
					if (rand() % 10 < 2) pola[i][j] = Field(Field::wall);
					else pola[i][j] = Field(Field::floor);
				}
				else if (rand() % 100 < 35 && noTreesInRange(i, j)) pola[i][j] = Field(Field::wall);
				else {
					pola[i][j] = Field(Field::floor);
					//if (i == player->x && j == player->y) pola[i][j].istota = player;

					 ///////////////////////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////// GENERACJA ENTITUW ////////////////////////////////////////////////

					if (entityCap > 0) {
						this->addEntity(i, j, new Entity(15, 2));
						entityCap--;
					}
					/*	if (rand() % 1000 < 10) {
							int randomType = rand() % 10;                     // respienie itemuw na mapce
							if (randomType < 3) {
								this->addItem()
							}
						}*/
				}
			}
		}
	}
	this->addEntity(this->width / 2, height - 2, player);
	if (!dfs(player->x, player->y)) generateBossRoomCave(player);
	else return;




}

void Map::generateBossRoomForest(Entity* player) {

	// randomowe wymiary mapy od 10 do 20
	int mapSize = std::rand() % 11 + 10;
	this->height = mapSize;
	this->width = mapSize;
	type = forest;

	pola.clear();
	pola.resize(height, vector<Field>(width, Field(Field::floor)));
	entities.clear();
	items.clear();




	int givenLevel;
	int entityCap = 1;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == this->width / 2 && j == this->height - 2) pola[i][j] = Field(Field::floor);
			else {
				int distanceToBorder = this->distanceToBorder(i, j);
				if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
					if (i == width / 3 - 1 && j == 0 || i == width / 3 * 2 && j == 0) {
						pola[i][j] = Field(Field::door);
					}
					else pola[i][j] = Field(Field::wall);
				}
				else if (distanceToBorder == 1) {
					if (rand() % 10 < 3 && i > 0 && j > 0) pola[i][j] = Field(Field::wall);
					else pola[i][j] = Field(Field::floor);
				}
				else if (distanceToBorder == 2) {
					if (rand() % 10 < 2) pola[i][j] = Field(Field::wall);
					else pola[i][j] = Field(Field::floor);
				}
				else if (rand() % 100 < 35 && noTreesInRange(i, j)) pola[i][j] = Field(Field::wall);
				else {
					pola[i][j] = Field(Field::floor);
					//if (i == player->x && j == player->y) pola[i][j].istota = player;

					 ///////////////////////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////// GENERACJA ENTITUW ////////////////////////////////////////////////
					
					if (entityCap > 0) {
						this->addEntity(i, j, new Entity(15, 1));
						entityCap--;
					}
					/*	if (rand() % 1000 < 10) {
							int randomType = rand() % 10;                     // respienie itemuw na mapce
							if (randomType < 3) {
								this->addItem()
							}
						}*/
				}
			}
		}
	}
	this->addEntity(this->width / 2, height - 2, player);
	if (!dfs(player->x, player->y)) generateBossRoomForest(player);
	else return;


}



void Map::searchForFights(){  //15.02 naprawiam tak zeby bylo wiadomo o co chodzi
	Entity *enem, *play;

	for (auto ent : this->entities) {
		std::pair<int, int> position = this->ableToStartFight(ent);

		if (position.first >= 0 && (ent->isPlayer || this->pola[position.first][position.second].istota->isPlayer)) {  //25.01.2024 nie wiem jak to dzia³a
			system("cls");
			if (ent->isPlayer) {
				enem = this->pola[position.first][position.second].istota;
				play = ent;
			}
			else {
				enem = ent;
				play = this->pola[position.first][position.second].istota;
			}
			std::cout << "A fight between " << play->name << " and " << enem->name << " emerges!\n";
			std::cout << "1. Attack\t\n";

			Entity* winner = this->Fight(play, enem);
			cout << winner->name << " " << winner->displayHP() << " wins!" << endl << "Press any key to continue..";
			while (1) {
				char in = _getch();
				if (in) break;
			}
			break;
		}
	}
}

void Map::manageEntityAI(){
	Entity* player = nullptr;
	for (auto ent : this->entities) {
		if (ent->isPlayer) player = ent;
	}
	if (!player) return;
	for (auto ent : this->entities) {
		if (ent->level >= player->level && ent->currHP > ent->maxHP / 2 && this->isPlayerInRange(ent, player, 3)) {
			this->chasePlayer(ent, player);
		}
		else if ((ent->level < player->level || ent->currHP < ent->maxHP / 2) && this->isPlayerInRange(ent, player, 3)) {
			this->fleePlayer(ent, player);
		}
		else if (rand() % 10 < 5) {
			int randomDirection = rand() % 4;
			if (randomDirection == 0) this->moveEntity(ent, 0, 1);
			else if (randomDirection == 1) this->moveEntity(ent, 1, 0);
			else if (randomDirection == 2) this->moveEntity(ent, -1, 0);
			else if (randomDirection == 3) this->moveEntity(ent, 0, -1);
		}
	}
}

void Map::checkDoors(Entity* player, int forestDepth, int cavesDepth, Entity* boss){
	string input;
	if (this->pola[this->width / 3 - 1][0].istota) {
		if (this->pola[this->width / 3 - 1][0].istota->isPlayer) {
			this->refresh();
			cout << "Do you wish to go to further into the woods? There is no way back..\n";
			cin >> input;
			if (input == "yes") {
				forestDepth++;
				this->generateForest(player);
				if (forestDepth == 8 || player->level == 14) {
					this->generateBossRoomForest(player);
					boss = this->entities[0];
				}

				if (rand() % 100 < 15) {
					player->event();
					cout << "Press any key to continue\n";
					while (1) {
						char in = _getch();
						if (in) break;
					}


				}
				if (forestDepth == 7) {
					cout << "You are being observed.\n";
					while (1) {
						char in = _getch();
						if (in) break;
					}
				}
			}
			else if (input == "no") {
				this->moveEntity(player, 0, 1);
			}
		}
	}
	else if (this->pola[this->width / 3 * 2][0].istota) {
		if (this->pola[this->width / 3 * 2][0].istota->isPlayer) {
			this->refresh();
			cout << "Do you wish to go deeper into the caves? There is no way back..\n";
			cin >> input;
			if (input == "yes") {
				if (cavesDepth == 8 || player->level == 14) {
					this->generateBossRoomCave(player);
					boss = this->entities[0];
				}
				else {
					this->generateCave(player);
					cavesDepth++;
					if (rand() % 100 < 15) {
						player->event();
						cout << "Press any key to continue\n";
						while (1) {
							char in = _getch();
							if (in) break;
						}

					}
					if (cavesDepth == 7) {
						cout << "You hear voices.\n";
						while (1) {
							char in = _getch();
							if (in) break;
						}
					}
				}
			}
			else if (input == "no") {
				this->moveEntity(player, 0, 1);
			}

		}
	}

}





void Map::generateCave(Entity* player)
{
	// randomowe wymiary mapy od 10 do 20
	int mapSize = std::rand() % 11 + 10;
	this->height = mapSize;
	this->width = mapSize;
	type = cave;

	pola.clear();
	pola.resize(height, vector<Field>(width, Field(Field::floor)));
	entities.clear();
	items.clear();
	 
	
	

	int givenLevel;
	int entityCap = (int)(round((float)this->height / 10) + 2);
	if (player->level > 10) { entityCap++; }
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (i == this->width / 2 && j == this->height - 2) pola[i][j] = Field(Field::floor);
			else {
				int distanceToBorder = this->distanceToBorder(i, j);
				if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
					if (i == width / 3 - 1 && j == 0 || i == width / 3 * 2 && j == 0) {
						pola[i][j] = Field(Field::door);
					}
					else pola[i][j] = Field(Field::wall);
				}
				else if (distanceToBorder == 1) {
					if (rand() % 10 < 8 && i > 0 && j > 0 && (pola[i][j - 1].symb == '#' || (pola[i - 1][j].symb == '#'))) pola[i][j] = Field(Field::wall);
					else pola[i][j] = Field(Field::floor);
				}
				else if (distanceToBorder == 2) {
					if (rand() % 10 < 6) pola[i][j] = Field(Field::wall);
					else pola[i][j] = Field(Field::floor);
				}
				else if (rand() % 10 < 4) pola[i][j] = Field(Field::wall);
				else {
					pola[i][j] = Field(Field::floor);
					//if (i == player->x && j == player->y) pola[i][j].istota = player;

					 ///////////////////////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////// GENERACJA ENTITUW ////////////////////////////////////////////////
					std::random_device rd;
					std::mt19937 gen(rd());							//testuje nowoczesne generowanei lczb
					std::uniform_int_distribution<> range(0, 100);
					int givenNumber = range(gen);
					if (givenNumber <= 2) {
						givenLevel = std::max(player->level - 3, 1);
					}
					else if (givenNumber > 2 && givenNumber <= 16) {
						givenLevel = std::max(player->level - 2, 1); // ograniczenie, tak aby level by³ minimalnie pierwszy
					}
					else if (givenNumber > 16 && givenNumber <= 50) {
						givenLevel = std::max(player->level - 1, 1);
					}
					else if (givenNumber > 50 && givenNumber <= 84) {
						givenLevel = player->level;
					}
					else if (givenNumber > 84 && givenNumber <= 98) {
						givenLevel = std::min(player->level + 1, 12);  // ograniczenie górne
					}
					else if (givenNumber > 98 && givenNumber <= 100) {
						givenLevel = std::min(player->level + 2, 12);
					}
					givenLevel = znajdzNajblizszaLiczbe(givenLevel, player->listOfLvls);
					int modifier = 100;
					if (entityCap > 0) {

						if (rand() % 1000 < modifier && entityNotInRange(i, j)) {
							modifier = (modifier / 3) - (modifier / 5);
							this->addEntity(i, j, this->generateEntity(givenLevel,1));
							entityCap--;
						}
					}
					/*	if (rand() % 1000 < 10) {
							int randomType = rand() % 10;                     // respienie itemuw na mapce
							if (randomType < 3) {
								this->addItem()
							}
						}*/
				}
			}
		}
	}
	this->addEntity(this->width / 2, height - 2, player);
	if (!dfs(player->x, player->y)) generateCave(player); 
	else return;
	
	
	
}
bool Map::dfs(int x, int y) {
	int rows = width;
	int cols = height;
	
	if (x < 0 || x >= rows || y < 0 || y >= cols || !pola[x][y].walkable || pola[x][y].visited) {
		return false;
	}

	if (pola[x][y].symb == '-') {
		return true;
	}

	pola[x][y].visited = true;

	
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (dfs(nx, ny)) {
			return true;
		}
	}

	return false;
}
int Map::znajdzNajblizszaLiczbe(int liczba, const std::vector<int>& lista) {
	int najblizsza = lista[0];
	int minimalnaRoznica = std::abs(liczba - najblizsza);

	for (int i = 1; i < lista.size(); ++i) {
		int roznica = std::abs(liczba - lista[i]);
		if (roznica < minimalnaRoznica) {
			najblizsza = lista[i];
			minimalnaRoznica = roznica;
		}
	}

	return najblizsza;
}
void Map::chasePlayer(Entity* chaser, Entity* player) {
	int dx = 0, dy = 0;

	if (chaser->x < player->x) {
		dx = 1;
	}
	else if (chaser->x > player->x) {
		dx = -1;
	}
	if (chaser->y < player->y) {
		dy = 1;
	}
	else if (chaser->y > player->y) {
		dy = -1;
	}
	//if(chaser->y > player->y && chaser->x > player->x){
	//	dy = 0, dx = 1;
	//}
	//if (chaser->y > player->y && chaser->x > player->x) {
	//	dy = -1, dx = 0;
	//}
	moveEntity(chaser, dx, dy);
}
void Map::fleePlayer(Entity* fleer, Entity* player) {
	int dx = 0, dy = 0;

	if (fleer->x < player->x) {
		dx = -1;
	}
	else if (fleer->x > player->x) {
		dx = 1;
	}
	if (fleer->y < player->y) {
		dy = -1;
	}
	else if (fleer->y > player->y) {
		dy = 1;
	}
	//if(chaser->y > player->y && chaser->x > player->x){
	//	dy = 0, dx = 1;
	//}
	//if (chaser->y > player->y && chaser->x > player->x) {
	//	dy = -1, dx = 0;
	//}
	moveEntity(fleer, dx, dy);
}

bool Map::isPlayerInRange(Entity * chaser, Entity * player, int range) const {
	int dx = std::abs(chaser->x - player->x);
	int dy = std::abs(chaser->y - player->y);

	return (dx <= range && dy <= range);
}
void Map::refresh() {
	system("cls");
	listEntities();
	listItems();
	displayMap();
}

void Map::randomLoot(Entity* looter, Entity* ofTheDead)
{
	if (looter->isPlayer) {
		int diceRoll = rand() % 6;
		int diceRolltwo = rand() % 100;
		if (diceRolltwo <35) {
			if (diceRoll < 1) {
				looter->eq.push_back(ofTheDead->weapon);
			}
			else if (diceRoll < 2) {
				looter->eq.push_back(ofTheDead->armor);
			}
			else if (diceRoll < 6) {
				looter->eq.push_back(new HealthPot(looter->maxHP / 3));
			}
			std::cout << "You've recived a new item\n";
		}
	}
}
int Map::distanceToBorder(int x, int y) {
	int distanceToBorder = std::min({ x, y, this->width - x - 1, this->height - y - 1 });
	return distanceToBorder;
}

Entity* Map::generateEntity(int level, int biom_id) {
	switch (biom_id)
	{
	case 0:
		switch (level)
		{
		case 1:
			return new Boar();
		case 3:
			return new Wolf();
		case 5:
			return new Rogue();
		case 9:
			return new Werecat();
		case 12:
			return new Sloth();
		}
	case 1:
		switch (level)
		{
		case 1:
			return new Spider();
		case 3:
			return new Bat();
		case 5:
			return new Cobolt();
		case 9:
			return new Demilich();
		case 12:
			return new Skeleton();
		}

	}
}



