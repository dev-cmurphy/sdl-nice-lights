#pragma once
#include "Component.h"
#include "Grid.h"

class CollisionSystem
{
	friend class VisualSystem;
public:
	CollisionSystem(int w = 10, int h = 10, int cellSize = 64);
	~CollisionSystem();

	void update();
	void addStaticComponent(GameObject* h, Vector2 size);

protected:

	class CollisionComponent : public Component {
		friend class VisualSystem;
	public:
		CollisionComponent(GameObject* h = NULL, Vector2 size = Vector2());
		~CollisionComponent();

		Vector2 size;
	};

	int cellSize;
	Grid<CollisionComponent> staticComponents;
	Grid<CollisionComponent> activeComponents;
};

