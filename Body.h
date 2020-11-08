#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
const double PI = 3.14159;
const double G = 0.00000000006673;

class Body
{
private:
	int id;
	double density;
	double radius;
	double mass;

	sf::Vector2<double> velocity;

	sf::Vector2<double> position;

	sf::CircleShape shape;

public:
	Body(int, sf::Vector2<double>, sf::Vector2<double>, double, double, sf::Color);

	sf::Vector2<double> getPosition();

	sf::Vector2<double> getVelocity();

	int getId();

	double getMass();

	double getRadius();

	sf::CircleShape getShape();

	void absorb(Body* body);

	void render(sf::RenderWindow*) const;

	void updatePosition();

	void updateVelocity(std::vector<Body>* bodies);

	static double magnitude(sf::Vector2<double>, sf::Vector2<double>);

	static double magnitude(sf::Vector2<float> lhs, sf::Vector2<float> rhs);
};

