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
using std::cin;

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
	enum types
	{
		wall,
		floor
	};

	Pole(char symb, bool walkable, Istota* istota) : symb(symb), walkable(walkable), istota(istota){
	};
	Pole(char symb, bool walkable) : symb(symb), walkable(walkable) {};
	Pole(types type) {
		if (type == floor) {
			symb = '.';
			walkable = true;
		}
		if (type == wall) {
			symb = '#';
			walkable = false;
		}
	}
	
};


class Map {
public:
	int width=5, height=5;
	vector<vector<Pole>> pola = { {Pole('#',false),  Pole('#',false),  Pole('#',false),  Pole('#',false), Pole('#',false)},
								{Pole('#',false), Pole('.', true), Pole('.', true), Pole('.', true), Pole('#', false)},
								{Pole('#',false), Pole('.', true), Pole('.', true), Pole('.', true), Pole('#', false)},
								{Pole('#',false), Pole('.', true), Pole('.', true), Pole('.', true), Pole('#', false)},
								{Pole('#',false),  Pole('#',false),  Pole('#',false),  Pole('#',false), Pole('#',false)} };
	vector <Istota*> entities;
	vector <Przedmiot*> items;


	void initEntities() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (pola[i][j].istota) {
					entities.push_back(pola[i][j].istota);                       // do wyrzucenia
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
		return pola[x][y].istota == nullptr && pola[x][y].walkable && isWithinBounds(x,y);
	}
	bool canPlaceItem(int x, int y) const {
		return pola[x][y].walkable && isWithinBounds(x, y);
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
		cout << "Entities on the map:" << endl;
		for (const auto& entity : entities) {
			cout << entity->name << " at (" << entity->x << ", " << entity->y << ")" << endl;
		}
	}
	void listItems() const {
		cout << "Items on the map:" << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (!pola[i][j].przedmioty.empty()) {
					for (int k = 0; k < pola[i][j].przedmioty.size(); k++) {
						cout<<pola[i][j].przedmioty[k]->name<< " at (" << i << ", " << j << ")" << endl;
					}
				}
			}
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
	void removeItem(int x, int y, Przedmiot* item) {
		
		if (pola[x][y].przedmioty.empty()) {
			return;
		}
		else {
			vector<Przedmiot*>::iterator it;
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
	void delEntityByPlace(int x, int y) {
		if (!pola[x][y].istota) return;

		vector<Istota*>::iterator it;
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
	void delItemByPlace(int x, int y) {

		if (pola[x][y].przedmioty.empty()) {
			return;
		}
		else {
			pola[x][y].przedmioty.pop_back();
		}
	}


	void changeTile(int x, int y, Pole new_pole) {
		pola[x][y] = new_pole;
	}
	void addItem(int x, int y, Przedmiot* item) {
		if (canPlaceItem(x, y)) {
			pola[x][y].przedmioty.push_back(item);
		}
		else return;
	}
	void addEntity(int x, int y, Istota* ent) {
		if (canPlaceEntity(x, y)) {
			ent->x = x;
			ent->y = y;
			pola[x][y].istota = ent;
			
			entities.push_back(ent);
		}
		else return;
	}


	};





int main() {
	Map map;
	string name = "ziutek";
	Istota player ('@', name, 0, 0);
	Istota enemy('E', "oponent", 2, 3);
	Przedmiot zbroja("zbroja");
	Przedmiot hełm("hełm");
	Pole newfloor('.', true);
	map.addEntity(2, 2, &player);
	map.addEntity(2, 3, &enemy);
	map.addItem(1, 1, &zbroja);
	map.pola[1][1].przedmioty.push_back(&hełm);
	map.displayMap();
	//map.initEntities();
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
		else if (input == '`') {
			cout << "testing mode\n list of avaliable commands:\n changetile\n addentity\n additem\n delentity\n delitem\n";
			int tx, ty;
			string command;
			cin >> command;
			if (command == "changetile") {
				string type;
				cout << "type in coords\n";
				cin >> tx >> ty;
				cout << "new tile type? [wall/floor]\n";
				cin >> type;
				if (type == "wall") {
					map.changeTile(tx, ty, Pole(Pole::wall));
				}
				else if (type == "floor") {
					map.changeTile(tx, ty, Pole(Pole::floor));
				}
				else {
					cout << "wrong type of tile!\n";
				}

			}
			else if (command == "addentity") {
				string name;
				char symb;
				cout << "type in coords\n";
				cin >> tx >> ty;
				cout << "name?\n";
				cin >> name;
				cout << "looks? [one character]\n";
				cin >> symb;
				map.addEntity(tx, ty, new Istota(symb, name, tx, ty));	
			}
			else if (command == "additem") {
				string name;
				cout << "type in coords\n";
				cin >> tx >> ty;
				cout << "name?\n";
				cin >> name;
				map.addItem(tx, ty, new Przedmiot(name));
			}
			else if (command == "delentity") {
				cout << "type in coords\n";
				cin >> tx >> ty;
				map.delEntityByPlace(tx, ty);
			}
			else if (command == "delitem") {
				cout << "type in coords\n";
				cin >> tx >> ty;
				map.delItemByPlace(tx, ty);
			}
		}

		system("cls");
		map.listEntities();
		map.listItems();
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