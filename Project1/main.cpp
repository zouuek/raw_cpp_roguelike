#include "Map.h";
#include <conio.h>;
#include "tests.h"
#include "EntityBase.h"
// out of range przy wyborze itemu w walce


int main() {
	srand(time(0));
	Map map;
	Entity player(Entity::player);
	map.generateForest(&player);
	string wait;
	int index;
	int cavesDepth = 0, forestDepth = 1;
	Entity boss(15,2);
	//Entity xd = xd.generateEntity();
	//map.addEntity(5,5,&xd);
	cout << "\t~~RZEZIMIESZKI~~" << "\n\n press f to continue..\n";
	while (1) {
		char in = _getch();
		if (in == 'f') break;
		else if (in == '`') test();
	}
	map.refresh();
	while (true) {
		if (boss.isDead()) break;
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
			if (wait == "e") {
				cin >> index;
				player.equipItem(index);
			}
		}
		map.searchForFights();
		map.manageEntityAI();
		map.checkDoors(&player, forestDepth, cavesDepth, &boss);
		if (player.isDead()) {
			break;
		}

		map.refresh();
	}
}
