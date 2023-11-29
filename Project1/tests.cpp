#include "tests.h"

// miejsce na przerobienie tych d³ugich ifów w funkcje 




void test() {
	Map map;
	Entity player(Entity::player);
	Entity enemy(Entity::boar);
	Item zbroja("zbroja");
	Item he³m("he³m");
	string wait;
	map.addEntity(2, 2, &player);
	map.addEntity(2, 3, &enemy);
	map.addItem(1, 1, &zbroja);
	map.addItem(1, 1, &he³m);
	map.displayMap();
	//map.initEntities();
	while (true) {
		cout << "testing mode\n list of avaliable commands:\n changetile\n addentity\n additem\n delentity\n delitem\n testfights\n";
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
				map.changeTile(tx, ty, Field(Field::wall));
			}
			else if (type == "floor") {
				map.changeTile(tx, ty, Field(Field::floor));
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
			map.addEntity(tx, ty, new Entity(symb, name, tx, ty));
		}
		else if (command == "additem") {
			string name;
			cout << "type in coords\n";
			cin >> tx >> ty;
			cout << "name?\n";
			cin >> name;
			map.addItem(tx, ty, new Item(name));
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
		else if (command == "testfights") {
			int n;
			int a=0, b=0;
			Entity* w;
			cout << "count?\n";
			cin >> n;
			for (int i = 0; i < n; i++) {
				w = map.Fight(&player, &enemy);
				if (w == &enemy) b++;
				else if (w == &player) a++;
				player.heal(player.maxHP);
				enemy.heal(enemy.maxHP);
			}
			cout << player.name << " won [" << a << "/" << n << "] fights with " << enemy.name << '\n';
			cout << enemy.name << " won [" << b << "/" << n << "] fights with " << player.name << '\n';
		}
	}

		system("cls");
		map.listEntities();
		map.listItems();
		map.displayMap();
}

