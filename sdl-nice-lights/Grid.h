#pragma once
#include "GameObject.h"
#include <list>
#include <vector>

template <typename T>
class Grid {
	friend class GridIterator;
public:

	~Grid() {}

	Grid(int w = 10, int h = 10, int size = 128) : objects(), cellSize(size)
	{
		width = w;
		height = h;

		for (int i = 0; i < w; i++) {
			std::vector < std::list<T> > objs;
			for (int j = 0; j < h; j++) {
				objs.push_back(std::list<T>());
			}
			objects.push_back(objs);
		}
	}

	std::list<T>& getObjectsAt(size_t x, size_t y)
	{
		return objects[x][y];
	}

	/*T& addObjectAt(Vector2 pos) {
		Vector2 gridPos = pos;
		gridPos.x = (int)(pos.x + 0.5f);
		gridPos.y = (int)(pos.y + 0.5f);
		return objects[gridPos.x][gridPos.y].
	}*/

	void addObjectAt(Vector2 pos, T&& ref = T()) {
		pos = realToGrid(pos);
		objects[pos.x][pos.y].push_back(ref);
	}

	void addObjectAt(Vector2 pos, T& ref = T()) {
		pos = realToGrid(pos);
		objects[pos.x][pos.y].push_back(ref);
	}

	Vector2 realToGrid(Vector2 pos) {
		pos /= cellSize;
		pos.x = (int)(pos.x);
		pos.y = (int)(pos.y);
		return pos;
	}

	const int getWidth() const {
		return width;
	}

	const int getHeight() const {
		return height;
	}

	const int getCellSize() const{
		return cellSize;
	}

	// retourne les listes
	// pas besoin de faire 2 for loops nested

	/*class GridIterator {
	public:
		GridIterator(Grid* g) {
			grid = g;
		}
		~GridIterator() {}

		std::list<T>* operator++() {
			currentH++;
			if (currentH >= grid->height) {
				currentW++;
				currentH = 0;
			}

			if (currentW >= grid->width) {
				currentW = 0;
				currentH = 0;
			}

			return &grid->objects[currentW][currentH];
		}

	protected:
		Grid * grid;
		int currentW, currentH;
	};

	GridIterator&*/

protected:
	int width, height, cellSize;
	std::vector<std::vector<std::list<T>>> objects;
};