#include <iostream>
#include <vector>
#include <map>
#include <conio.h>

class Entity {
public:
    Entity(const std::string& name, char symbol) : name(name), symbol(symbol) {}

    std::string getName() const { return name; }
    char getSymbol() const { return symbol; }

private:
    std::string name;
    char symbol;
};

class Map {
public:
    Map(int width, int height) : width(width), height(height), player(nullptr) {
        tiles.resize(width, std::vector<char>(height, '.'));
    }

    bool isWithinBounds(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    bool canPlaceEntity(int x, int y) const {
        return isWithinBounds(x, y) && tiles[x][y] == '.';
    }

    void placeEntity(Entity* entity, int x, int y) {
        if (canPlaceEntity(x, y)) {
            entities[entity] = std::make_pair(x, y);
            tiles[x][y] = entity->getSymbol();
        }
    }

    void removeEntity(Entity* entity) {
        if (entities.find(entity) != entities.end()) {
            const auto& pos = entities[entity];
            tiles[pos.first][pos.second] = '.';
            entities.erase(entity);
        }
    }

    void movePlayer(int dx, int dy) {
        if (player) {
            auto& playerPos = entities[player];
            int newPosX = playerPos.first + dx;
            int newPosY = playerPos.second + dy;
            if (canPlaceEntity(newPosX, newPosY)) {
                tiles[playerPos.first][playerPos.second] = '.';
                playerPos.first = newPosX;
                playerPos.second = newPosY;
                tiles[newPosX][newPosY] = player->getSymbol();
            }
        }
    }

    void displayMap() const {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::cout << tiles[x][y] << ' ';
            }
            std::cout << std::endl;
        }
    }

    void listEntities() const {
        std::cout << "Entities on the map:" << std::endl;
        for (const auto& entity : entities) {
            std::cout << entity.first->getName() << " at (" << entity.second.first << ", " << entity.second.second << ")" << std::endl;
        }
    }

    void changeTile(int x, int y, char newTile) {
        if (isWithinBounds(x, y) && canPlaceEntity(x,y)) {
            tiles[x][y] = newTile;
        }
    }

    void setPlayer(Entity* entity) {
        player = entity;
    }
    void buildWalls() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
            {
                if ((j == 0 || i == 0 || i==height -1 || j==width-1 )) changeTile(j, i, '#');
            }
        }
    }

private:
    int width;
    int height;
    std::vector<std::vector<char>> tiles;
    std::map<Entity*, std::pair<int, int>> entities;
    Entity* player;
};


int main() {
    Map gameMap(20, 20);

    Entity player("Player", '@');
    Entity monster("Monster", 'M');
    Entity treasure("Treasure", 'T');

    gameMap.setPlayer(&player);

    gameMap.placeEntity(&player, 5, 5);
    gameMap.placeEntity(&monster, 3, 4);
    gameMap.placeEntity(&treasure, 7, 8);

    std::cout << "Press (w/a/s/d) to start playing!" << std::endl;
    gameMap.buildWalls();

    // akcje
    while (true) {
        char input = _getch(); 
        if (input == 'w') {
            gameMap.movePlayer(0, -1); 
        }
        else if (input == 's') {
            gameMap.movePlayer(0, 1);  
        }
        else if (input == 'a') {
            gameMap.movePlayer(-1, 0); 
        }
        else if (input == 'd') {
            gameMap.movePlayer(1, 0);  
        }
        else if (input == 'q') {
            break;
        }
        else if (input == 'f') {
            gameMap.removeEntity(&monster);
        }

        system("cls");
        gameMap.listEntities();
        gameMap.displayMap();
    }

    gameMap.removeEntity(&player);
    gameMap.removeEntity(&monster);
    gameMap.removeEntity(&treasure);

    return 0;
}