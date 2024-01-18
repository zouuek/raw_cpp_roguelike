#include "Map.h";
#include <conio.h>;
#include "tests.h"


int main() {
	srand(time(0));
	Map map;
	Entity player(Entity::player);
	Entity enemy(Entity::leszy);
	Armor zbroja = Armor(0.9);
	LightningRod bronka = LightningRod();
	HealthPot potka = HealthPot(100);
	string wait;
	int index;
	map.addEntity(2, 2, &player);
	map.addEntity(2, 3, &enemy);
	//map.addItem(1, 1, &zbroja);
	map.addItem(1, 1, &potka);
	map.addItem(1, 1, &bronka);

	//map.displayMap();
	//map.initEntities();
	cout << "\t~~RZEZIMIESZKI~~" << "\n\n press f to continue..\n";
	while (1) {
		char in = _getch();
		if (in == 'f') break;
		else if (in == '`') test();
	}
	system("cls");
	map.listEntities();
	map.listItems();
	map.displayMap();
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
			map.entityPickUpItem(&player);
		}
		else if (input == 'i') {
			player.examineSelf();
			cin >> wait;
			if (wait == "equip") {
				cin >> index;
				player.equipItem(index);
			}
			
			
		}
		for (auto ent : map.entities) {
			if (map.ableToStartFight(ent).first >= 0) {
				system("cls");
				map.displayMap();
				Entity* winner = map.Fight(ent, map.pola[map.ableToStartFight(ent).first][map.ableToStartFight(ent).second].istota);
				cout << winner->name << " " << winner->displayHP() << " wins!" << endl << "press any key to continue";
				while (1) {
					char in = _getch();
					if (in) break;
				}
				break;
			}
		}
		if (player.isDead()) {
			break;
		}

		system("cls");
		map.listEntities();
		map.listItems();
		map.displayMap();
	}
}
