#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Body.h"

class Universe
{
private:
	std::vector<Body> bodies;

	std::vector<sf::VertexArray> trails;

	int findBody(Body*);

	sf::RenderWindow* window;

	bool paused;

	void addBody(Body);

	void removeBody(Body*);

	void resolveColision(int, int);

	void updateColisions();

	void checkEvent();

	void updateGravity();

	void updatePositions();

	void updateTrails();

	void update();

	void render();

public:

	Universe();

	Universe(std::vector<Body> bodies);

	void start();
};

