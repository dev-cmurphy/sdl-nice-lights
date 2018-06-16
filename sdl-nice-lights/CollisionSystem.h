#pragma once
#include "Component.h"
#include "Grid.h"

class CollisionSystem
{
	friend class VisualSystem;
public:
	CollisionSystem(int w = 10, int h = 10, int cellSize = 64);
	~CollisionSystem();

	void update(std::vector<GameObject>& objects);
	void addStaticComponent(int h, Vector2 pos, Vector2 size);

protected:

	class CollisionComponent : public Component {
		friend class CollisionSystem;
	public:
		CollisionComponent(int holder = -1, Vector2 size = Vector2());
		~CollisionComponent();

		Vector2 size;
	};

	int cellSize;
	Grid<CollisionComponent> staticComponents;
	Grid<CollisionComponent> activeComponents;
};

