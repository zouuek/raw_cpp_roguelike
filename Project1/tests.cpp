#include "tests.h"

// miejsce na przerobienie tych d³ugich ifów w funkcje 




void test() {
	Map map;
	Entity player(Entity::player);
	Entity enemy(Entity::boar);
	Entity enemy2(Entity::rzezimierch);
	Entity enemy3(Entity::kotolak);
	Entity enemy4(Entity::leszy);
	Entity enemy5(Entity::wolf);
	string wait;
	map.generateCave(&player);
	//map.addEntity(2, 2, &player);
	/*map.addEntity(2, 3, &enemy);
	map.addEntity(1, 1, &enemy2);
	map.addEntity(0, 0, &enemy3);
	map.addEntity(0, 1, &enemy4);
	map.addEntity(1, 0, &enemy5);*/

	//map.addItem(1, 1, &zbroja);
	//map.addItem(1, 1, &he³m);
	//map.displayMap();
	//player.armor = new Armor(0.00);
	//enemy.weapon = new Weapon(50);
	//enemy.armor = new Armor(0.2428);
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
			map.addEntity(player.x, player.y-1, &enemy);
			for (int i = 0; i < n; i++) {
				w = map.Fight(&player, &enemy);
				if (w == &enemy) b++;
				else if (w == &player) a++;
				player.heal(player.maxHP);
				enemy.heal(enemy.maxHP);
			}
			cout << player.name << " won [" << a << "/" << n << "] fights with " << enemy.name << '\n';
			cout << enemy.name << " won [" << b << "/" << n << "] fights with " << player.name << '\n';
			a = 0, b = 0;

			map.removeEntity(&enemy);
			map.addEntity(2, 3, &enemy3);

			for (int i = 0; i < n; i++) {
				w = map.Fight(&player, &enemy3);
				if (w == &enemy3) b++;
				else if (w == &player) a++;
				player.heal(player.maxHP);
				enemy3.heal(enemy3.maxHP);
			}
			cout << player.name << " won [" << a << "/" << n << "] fights with " << enemy3.name << '\n';
			cout << enemy3.name << " won [" << b << "/" << n << "] fights with " << player.name << '\n';
			a = 0, b = 0;

			map.removeEntity(&enemy3);
			map.addEntity(2, 3, &enemy2);

			for (int i = 0; i < n; i++) {
				w = map.Fight(&player, &enemy2);
				if (w == &enemy2) b++;
				else if (w == &player) a++;
				player.heal(player.maxHP);
				enemy2.heal(enemy2.maxHP);
			}
			cout << player.name << " won [" << a << "/" << n << "] fights with " << enemy2.name << '\n';
			cout << enemy2.name << " won [" << b << "/" << n << "] fights with " << player.name << '\n';
			a = 0, b = 0;

			map.removeEntity(&enemy2);
			map.addEntity(2, 3, &enemy4);

			for (int i = 0; i < n; i++) {
				w = map.Fight(&player, &enemy4);
				if (w == &enemy4) b++;
				else if (w == &player) a++;
				player.heal(player.maxHP);
				enemy4.heal(enemy4.maxHP);
			}
			cout << player.name << " won [" << a << "/" << n << "] fights with " << enemy4.name << '\n';
			cout << enemy4.name << " won [" << b << "/" << n << "] fights with " << player.name << '\n';
			a = 0, b = 0;

			map.removeEntity(&enemy4);
			map.addEntity(2, 3, &enemy5);

			for (int i = 0; i < n; i++) {
				w = map.Fight(&player, &enemy5);
				if (w == &enemy5) b++;
				else if (w == &player) a++;
				player.heal(player.maxHP);
				enemy5.heal(enemy5.maxHP);
			}
			cout << player.name << " won [" << a << "/" << n << "] fights with " << enemy5.name << '\n';
			cout << enemy5.name << " won [" << b << "/" << n << "] fights with " << player.name << '\n';
			a = 0, b = 0;
		}
	}

		system("cls");
		map.listEntities();
		map.listItems();
		map.displayMap();
}

