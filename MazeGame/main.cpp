#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace sf;

enum Direct { None, Up, Down, Left, Right };
enum Screen { Menu, Select, Main };

int SPLIT_X = 32;
int SPLIT_Y = 18;
int SCREEN_X = 800;
int SCREEN_Y = 450;
int initPosX;
int initPosY;
int goalPosX;
int goalPosY;
int levelN = 0;
bool autoSearch;
bool completed;
Screen currentScreen;
int count;
int autoArrI;
float timer = 0, delay = 0.3;

std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
std::vector <Direct> autoArr;

int levelpos[3][4] = {
	{1, 16, 30, 4},
	{4, 1, 26, 16},
	{1, 2, 27, 15}
};

int levelmap[3][18][32] = {
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 1, 0, 0, 0, 0, 2, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0,
		0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 1, 0, 0, 2, 2, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	},
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 2, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0,
		0, 1, 1, 2, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

	},
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 4, 0, 0, 2, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	}
};

int map[18][32] = { 0, };

void init(int n) {
	levelN = n;
	autoSearch = false;
	completed = false;
	count = 0;
	initPosX = levelpos[levelN][0];
	initPosY = levelpos[levelN][1];
	goalPosX = levelpos[levelN][2];
	goalPosY = levelpos[levelN][3];
	for (int i = 0; i < SPLIT_X; i++) {
		for (int j = 0; j < SPLIT_Y; j++) {
			map[j][i] = levelmap[levelN][j][i];
		}
	}
}

class Item {
private:
	Sprite sprite;
	Texture texture;

public:
	Item(String path = "", int leftX = 0, int leftY = 0, int rightX = 0, int rightY = 0, int sizeX = 0, int sizeY = 0) {
		if (path == "") return;
		setItem(path);
		if (rightX != 0 && rightY != 0) {
			sprite.setTextureRect(IntRect(leftX, leftY, rightX, rightY));
		}
		if (sizeX != 0 && sizeY != 0) setSize(sizeX, sizeY);
	}

	virtual void setItem(String path) {
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}

	virtual void setSize(int x, int y) {
		sprite.setScale((float)x / sprite.getTextureRect().width, (float)y / sprite.getTextureRect().height);
	}

	virtual void setReallyPos(int x, int y) {
		sprite.setPosition(x, y);
	}

	virtual void setPos(int x, int y) {
		float halfSizeX = sprite.getScale().x * sprite.getTextureRect().width / 2;
		float halfSizeY = sprite.getScale().y * sprite.getTextureRect().height / 2;
		setReallyPos((x * 2 + 1) * SCREEN_X / 2 / SPLIT_X - halfSizeX, (y * 2 + 1) * SCREEN_Y / 2 / SPLIT_Y - halfSizeY);
	}

	virtual void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	virtual FloatRect getBounds() {
		return sprite.getGlobalBounds();
	}

	virtual Sprite getSprite() {
		return sprite;
	}
};

class Character : public Item {
private:
	int posX;
	int posY;

public:
	Character(String path, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0) : Item(path, 0, 0, 0, 0, sizeX, sizeY) {
		posX = x;
		posY = y;
		setPos(x, y);
	}

	void moveCharacter(Direct dir) {
		if (!dir) return;
		if (completed) return;
		int x = posX, y = posY;
		if (dir == Up && posY > 0) y--;
		else if (dir == Down && posY < SPLIT_Y - 1) y++;
		else if (dir == Left && posX > 0) x--;
		else if (dir == Right && posX < SPLIT_X - 1) x++;
		if (map[y][x] != 0) {
			posX = x;
			posY = y;
			setPos(posX, posY);
		}
		if (map[y][x] == 2) {
			map[y][x] = 1;
			count++;
		}
		else if (map[y][x] == 4) {
			map[goalPosY][goalPosX] = 5;
			map[y][x] = 1;
		}
		else if (map[y][x] == 5) {
			completed = true;
		}
	}

	void setPos(int x, int y) {
		float halfSizeX = getSprite().getScale().x * getSprite().getTextureRect().width / 2;
		float halfSizeY = getSprite().getScale().y * getSprite().getTextureRect().height / 2;
		setReallyPos((x * 2 + 1) * SCREEN_X / 2 / SPLIT_X - halfSizeX, (y * 2 + 1) * SCREEN_Y / 2 / SPLIT_Y - halfSizeY);
		posX = x;
		posY = y;
	}

	Vector2i getPos() {
		return Vector2i(posX, posY);
	}
};

struct State {
	int x, y;
	std::set<std::pair<int, int>> collected;
	std::vector<std::pair<int, int>> path;

	State(int x, int y, std::set<std::pair<int, int>> collected, std::vector<std::pair<int, int>> path)
		: x(x), y(y), collected(collected), path(path) {}
};

bool isValidMove(int x, int y, const std::vector<std::vector<int>>& grid, const std::set<std::pair<int, int>>& collected, std::unordered_map<int, std::unordered_map<int, std::set<std::set<std::pair<int, int>>>>>& visited) {
	int rows = grid.size();
	int cols = grid[0].size();
	return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] != 0 && visited[x][y].find(collected) == visited[x][y].end();
}

std::vector<std::pair<int, int>> bfsCollectAllCoins(std::pair<int, int> start, std::pair<int, int> end) {
	std::vector<std::vector<int>> grid;

	int rows = SPLIT_Y;
	int cols = SPLIT_X;

	for (int i = 0; i < rows; i++) {
		std::vector <int> v;
		for (int j = 0; j < cols; j++) {
			v.push_back(map[i][j]);
		}
		grid.push_back(v);
	}

	std::set<std::pair<int, int>> coins;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (grid[i][j] == 2 || grid[i][j] == 4) {
				coins.insert({ i, j });
			}
		}
	}

	std::queue<State> q;
	std::unordered_map<int, std::unordered_map<int, std::set<std::set<std::pair<int, int>>>>> visited; // visited[x][y] -> collected coins at this cell

	std::set<std::pair<int, int>> initialCollected;
	std::vector<std::pair<int, int>> initialPath = { start };

	q.push(State(start.first, start.second, initialCollected, initialPath));
	visited[start.first][start.second].insert(initialCollected);

	while (!q.empty()) {
		State current = q.front();
		q.pop();

		int x = current.x;
		int y = current.y;

		if (std::make_pair(x, y) == end && current.collected == coins) {
			return current.path;
		}

		for (const auto& dir : directions) {
			int nx = x + dir.first;
			int ny = y + dir.second;

			if (isValidMove(nx, ny, grid, current.collected, visited)) {
				std::set<std::pair<int, int>> newCollected = current.collected;
				if (grid[nx][ny] == 2 || grid[nx][ny] == 4) {
					newCollected.insert({ nx, ny });
				}
				std::vector<std::pair<int, int>> newPath = current.path;
				newPath.push_back({ nx, ny });

				q.push(State(nx, ny, newCollected, newPath));
				visited[nx][ny].insert(newCollected);
			}
		}
	}

	return {}; // return an empty path if no solution is found
}

int main() {

	RenderWindow window(sf::VideoMode(SCREEN_X - 1, SCREEN_Y - 1), "Maze Game");
	Item background("GameData/MainWind-background.png", 0, 0, 0, 0, SCREEN_X, SCREEN_Y);
	int width = SCREEN_X / SPLIT_X;
	int height = SCREEN_Y / SPLIT_Y;
	Item block("GameData/map(80x80).jpg", 0, 0, 80, 80, 25, 25);
	Item glass("GameData/map(80x80).jpg", 81, 0, 80, 80, 25, 25);
	Item coin("GameData/map(80x80).jpg", 161, 0, 80, 80, 25, 25);
	Item box("GameData/map(80x80).jpg", 241, 0, 80, 80, 25, 25);
	Item key("GameData/map(80x80).jpg", 321, 0, 80, 80, 25, 25);
	Item door("GameData/map(80x80).jpg", 401, 0, 80, 80, 25, 25);
	Character character("GameData/character.png", 0, 0, 25, 25);
	Item playBtn("GameData/play.png", 0, 0, 0, 0, 100, 30);
	Item quitBtn("GameData/quit.png", 0, 0, 0, 0, 100, 30);
	Item autoBtn("GameData/auto.png", 0, 0, 0, 0, 100, 30);
	Item backBtn("GameData/back.png", 0, 0, 0, 0, 100, 30);
	Item backBtn1("GameData/back.png", 0, 0, 0, 0, 100, 30);
	Item c("GameData/c.png", 0, 0, 0, 0, 30, 30);
	Item end("GameData/end.png", 0, 0, 0, 0, 500, 300);
	playBtn.setReallyPos(SCREEN_X - 205, 1);
	quitBtn.setReallyPos(SCREEN_X - 105, 1);
	autoBtn.setReallyPos(SCREEN_X - 205, 1);
	backBtn.setReallyPos(SCREEN_X - 105, 1);
	backBtn1.setReallyPos(SCREEN_X / 2 - 50, SCREEN_Y / 2 + 50);
	end.setReallyPos(SCREEN_X / 2 - 250, SCREEN_Y / 2 - 150);
	Item num("GameData/0.png", 0, 0, 0, 0, 30, 30);
	Item num1("GameData/0.png", 0, 0, 0, 0, 50, 50);
	c.setReallyPos(10, 1);
	num.setReallyPos(40, 1);
	num1.setReallyPos(SCREEN_X / 2 - 25, SCREEN_Y / 2 - 5);
	Item level1("GameData/level1.png", 0, 0, 0, 0, 150, 80);
	Item level2("GameData/level2.png", 0, 0, 0, 0, 150, 80);
	Item level3("GameData/level3.png", 0, 0, 0, 0, 150, 80);
	level1.setReallyPos(10, 10);
	level2.setReallyPos(10, 100);
	level3.setReallyPos(10, 190);

	Direct dir;
	currentScreen = Menu;

	Clock clock;
	int step = 0;

	while (window.isOpen()) {

		dir = None;

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Up || e.key.code == Keyboard::W) dir = Up;
				else if (e.key.code == Keyboard::Down || e.key.code == Keyboard::S) dir = Down;
				else if (e.key.code == Keyboard::Left || e.key.code == Keyboard::A) dir = Left;
				else if (e.key.code == Keyboard::Right || e.key.code == Keyboard::D) dir = Right;
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {
					Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

					if (currentScreen == Menu) {
						if (playBtn.getBounds().contains(mouse)) {
							currentScreen = Select;
						}
						if (quitBtn.getBounds().contains(mouse)) {
							window.close();
						}
					}
					else if (currentScreen == Select) {
						if (playBtn.getBounds().contains(mouse)) {
							currentScreen = Menu;
						}
						if (quitBtn.getBounds().contains(mouse)) {
							window.close();
						}
						if (level1.getBounds().contains(mouse)) {
							init(0);
							character.setPos(initPosX, initPosY);
							currentScreen = Main;
						}
						if (level2.getBounds().contains(mouse)) {
							init(1);
							character.setPos(initPosX, initPosY);
							currentScreen = Main;
						}
						if (level3.getBounds().contains(mouse)) {
							init(2);
							character.setPos(initPosX, initPosY);
							currentScreen = Main;
						}
					}
					else if (currentScreen == Main) {
						if (backBtn.getBounds().contains(mouse)) {
							currentScreen = Menu;
							character.setPos(initPosX, initPosY);
						}
						if (backBtn1.getBounds().contains(mouse) && completed) {
							currentScreen = Select;
							character.setPos(initPosX, initPosY);
						}
						if (autoBtn.getBounds().contains(mouse)) {
							autoSearch ^= true;
							if (autoSearch) {
								autoArr.clear();
								autoArrI = 0;

								std::pair<int, int> start = { character.getPos().y, character.getPos().x };
								std::pair<int, int> end = { goalPosY, goalPosX };
								std::vector<std::pair<int, int>> path = bfsCollectAllCoins(start, end);

								if (!path.empty()) {
									bool flg = 0;
									int prex = 0, prey = 0;
									for (const auto& pos : path) {
										if (flg)
										{
											for (int i = 0; i < 4; i++) {
												int nx = prex + directions[i].first;
												int ny = prey + directions[i].second;
												if (nx == pos.first && ny == pos.second) {
													if (i == 0) autoArr.push_back(Up);
													if (i == 1) autoArr.push_back(Down);
													if (i == 2) autoArr.push_back(Left);
													if (i == 3) autoArr.push_back(Right);
												}
											}
										}
										prex = pos.first, prey = pos.second;
										flg = true;
									}
								}
							}
						}
					}
				}
			}
		}

		if (autoSearch && !completed) {

			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			if (timer > delay) {
				if (autoArrI == autoArr.size()) autoSearch = false;
				else {
					character.moveCharacter(autoArr[autoArrI++]);
					timer = 0;
				}
			}
		}

		window.clear(Color::White);

		if (currentScreen == Main) {
			if (!autoSearch && !completed) character.moveCharacter(dir);
			for (int i = 0; i < SPLIT_X; i++) {
				for (int j = 0; j < SPLIT_Y; j++) {
					switch (map[j][i]) {
					case 0: {
						glass.setPos(i, j);
						glass.draw(window);
						break;
					}
					case 1: {
						block.setPos(i, j);
						block.draw(window);
						break;
					}
					case 2: {
						coin.setPos(i, j);
						coin.draw(window);
						break;
					}
					case 3: {
						box.setPos(i, j);
						box.draw(window);
						break;
					}
					case 4: {
						key.setPos(i, j);
						key.draw(window);
						break;
					}
					case 5: {
						door.setPos(i, j);
						door.draw(window);
						break;
					}
					}
				}
			}
			character.draw(window);
			String countStr = "GameData/";
			countStr += (char)(count + '0');
			countStr += ".png";
			if (completed) {
				end.draw(window);
				backBtn1.draw(window);
				num1.setItem(countStr);
				num1.draw(window);
			}
			else {
				backBtn.draw(window);
				autoBtn.draw(window);
				c.draw(window);
				num.setItem(countStr);
				num.draw(window);
			}
		}
		else {
			background.draw(window);
			playBtn.draw(window);
			quitBtn.draw(window);
			if (currentScreen == Select) {
				level1.draw(window);
				level2.draw(window);
				level3.draw(window);
			}
		}

		window.display();
	}

	return 0;
}