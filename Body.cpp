#include "Body.h"
#include "Math.h"
#include <cmath>
#include <iostream>


Body::Body(int id, sf::Vector2<double> position, sf::Vector2<double> velocity, double radius, double density, sf::Color color) {

	this->id = id;

	this->position = position;

	//radius = std::cbrt((3 * mass) / (4 * PI * density));
	this->radius = radius;

	this->density = density;

	//this->mass = mass;
	mass = (PI * Math::pow(this->radius, 3) * ((double)4/3) * this->density);

	shape = sf::CircleShape(radius / 500);

	shape.setOrigin(radius / 500, radius / 500);

	shape.setPosition(position.x, position.y);

	shape.setFillColor(color);

	this->velocity = velocity;
}

sf::Vector2<double> Body::getPosition() { return position; }

sf::Vector2<double> Body::getVelocity() { return velocity; }

int Body::getId() { return id; }

double Body::getMass() { return mass; }

double Body::getRadius() { return radius; }

void Body::absorb(Body* body) {

	mass += body->mass;

	radius = std::cbrt((mass * 3) / (4 * PI * density));

	shape.setRadius(radius / 500);
}

sf::CircleShape Body::getShape() { return shape; }

void Body::render(sf::RenderWindow* window) const{

	window->draw(shape); 
}

double Body::magnitude(sf::Vector2<double> lhs, sf::Vector2<double> rhs) { return sqrt((pow((rhs.x - lhs.x), 2) + pow((rhs.y - lhs.y), 2))); }

double Body::magnitude(sf::Vector2<float> lhs, sf::Vector2<float> rhs) { return sqrt((pow((rhs.x - lhs.x), 2) + pow((rhs.y - lhs.y), 2))); }

void Body::updatePosition() {

	position += velocity;

	shape.setPosition(position.x, position.y);

}

void Body::updateVelocity(std::vector<Body>* bodies) {

	for (int i = 0; i < bodies->size(); i++) {

		if (this->position != bodies->at(i).getPosition()) {

			double magn = magnitude(this->position, bodies->at(i).getPosition());

			sf::Vector2<double> unitV = (this->position - bodies->at(i).getPosition()) / magn;

			double F = -((G * mass * bodies->at(i).getMass()) / Math::pow(magn, 2));

			sf::Vector2<double> acceleration = (unitV * F) / mass;

			velocity += acceleration;
		}
	}
}
