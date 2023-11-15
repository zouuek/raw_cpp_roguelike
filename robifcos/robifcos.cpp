#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <utility>
#include <map>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::endl;

class Istota {
public:
	int x, y;
	char symb;
	string name;
	//int hp, attack;
	Istota(char symb, string name, int x, int y): symb(symb), name(name), x(x), y(y){};
};

class Przedmiot {
public:
	string name;
	Przedmiot(string name) : name(name) {};
};

class Pole {
public:
	char symb;
	bool walkable;
	Istota* istota = nullptr;
	vector<Przedmiot*> przedmioty;
	Pole(char symb, bool walkable, Istota* istota) : symb(symb), walkable(walkable), istota(istota){
	};
	Pole(char symb, bool walkable) : symb(symb), walkable(walkable) {};
	
};

//class Gracz
//	:Istota {
//public:
//	Gracz() {
//		symb = '@';
//		name = "Bohater";
//	}
//};

class Map {
public:
	int width=5, height=5;
	vector<vector<Pole>> pola = { {Pole('#',false),  Pole('#',false),  Pole('#',false),  Pole('#',false), Pole('#',false)},
								{Pole('#',false), Pole('.', true), Pole('.', true), Pole('.', true), Pole('#', false)},
								{Pole('#',false), Pole('.', true), Pole('.', true), Pole('.', true), Pole('#', false)},
								{Pole('#',false), Pole('.', true), Pole('.', true), Pole('.', true), Pole('#', false)},
								{Pole('#',false),  Pole('#',false),  Pole('#',false),  Pole('#',false), Pole('#',false)} };
	vector <Istota*> entities;


	void initEntities() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (pola[i][j].istota) {
					entities.push_back(pola[i][j].istota);
				}
			}
		}
	}

	void displayMap() const {
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

	bool isWithinBounds(int x, int y) const {
		return x >= 0 && x < width && y >= 0 && y < height;      //nie dzial
	}

	bool canPlaceEntity(int x, int y) const {
		return pola[x][y].istota == nullptr && pola[x][y].walkable;
	}
	bool canPlaceItem(int x, int y) const {
		return pola[x][y].walkable;
	}

	void moveEntity(Istota* ist, int dx, int dy) {
		std::pair<int, int> currPos = {ist->x, ist->y};
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

	void listEntities() const {
		std::cout << "Entities on the map:" << std::endl;
		for (const auto& entity : entities) {
			std::cout << entity->name << " at (" << entity->x << ", " << entity->y << ")" << std::endl;
		}
	}

	void removeEntity(Istota* istota) {
		vector<Istota*>::iterator it;
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
	void changeTile(int x, int y, Pole pole) {
		pola[x][y] = pole;
	}
	

	};





int main() {
	Map map;
	string name = "ziutek";
	Istota player ('@', name, 2, 2);
	Istota enemy('E', "oponent", 2, 3);
	Przedmiot zbroja("zbroja");
	Pole newfloor('.', true);
	map.pola[2][2].istota = &player;
	map.pola[2][3].istota = &enemy;
	map.pola[1][1].przedmioty.push_back(&zbroja);
	map.displayMap();
	map.initEntities();
	while (true) {
		char input = _getch();
		if (input == 'w') {
			map.moveEntity(&player, 0, -1);
		}
		else if (input == 's') {
			map.moveEntity(&player, 0, 1);
		}
		else if (input == 'a') {
			map.moveEntity(&player, -1, 0);
		}
		else if (input == 'd') {
			map.moveEntity(&player, 1, 0);
		}
		else if (input == 'q') {
			break;
		}
		else if (input == 'f') {
			map.removeEntity(&enemy);
		}
		else if (input == 'r'){
			map.changeTile(0, 0, newfloor);
		}

		system("cls");
		map.listEntities();
		map.displayMap();
	}
}




//Map(int width, int height) : width(width), height(height) {
	//pola.resize(height, vector<Pole>(width));

	/*for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if((j == 0 || i == 0 || i == height - 1 || j == width - 1)) {
				pola.push_back() Pole(j,i,'#',false);
			}
			else {
				pola[i][j] = Pole(j, i, '.', true);
			}
		}*/
		//}
	//}