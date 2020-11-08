#include "Universe.h"
#include <iostream>

Universe::Universe() { paused = false; }

Universe::Universe(std::vector<Body> bodies) {

	this->bodies = bodies;
    paused = false;
}

void Universe::start(){

    window = new sf::RenderWindow(sf::VideoMode(1280, 768), "Gravity");

    bodies.push_back(Body(0, sf::Vector2<double>(window->getSize().x / 2, window->getSize().y / 2), sf::Vector2<double>(0, 0), 20000, 1.4, sf::Color::Yellow));
    bodies.push_back(Body(1, sf::Vector2<double>(370, 384), sf::Vector2<double>(0, -3.4), 3000, 5, sf::Color::Blue));
    bodies.push_back(Body(2, sf::Vector2<double>(350, 384), sf::Vector2<double>(0, -4.698), 500, 2, sf::Color::White));
    bodies.push_back(Body(3, sf::Vector2<double>(770, 384), sf::Vector2<double>(0, 4.748), 2000, 4, sf::Color::Green));

    trails.push_back(sf::VertexArray());
    trails.push_back(sf::VertexArray());
    trails.push_back(sf::VertexArray());
    trails.push_back(sf::VertexArray());

    int fps = 60;
    double timePerTick = 1000000000 / fps;
    double delta = 0;
    std::chrono::steady_clock::time_point now;
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (window->isOpen())
    {


        checkEvent();

        
        if (paused) {

            lastTime = std::chrono::high_resolution_clock::now();
        }

        if (!paused) {

            now = std::chrono::high_resolution_clock::now();

            delta += (std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastTime).count()) / timePerTick;

            lastTime = now;

            while (delta >= 1) {

                window->clear();

                render();

                window->display();

                update();

                delta--;
            }

        }
    }
}

void Universe::checkEvent() {

    sf::Event event;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window->close();

        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Space) {

                if (paused) {

                    paused = false;
                    return;
                }

                if (!paused) {

                    paused = true;
                    return;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {

            if (event.mouseButton.button == sf::Mouse::Button::Left) {

                bodies.push_back(Body(bodies.size(), sf::Vector2<double>(event.mouseButton.x, event.mouseButton.y), sf::Vector2<double>(5, -1), 2000, 0.1, sf::Color::Blue));
                trails.push_back(sf::VertexArray());
            }
        }
    }
}

int Universe::findBody(Body* body) {

	for (int i = 0; i < bodies.size(); i++) {

		if (bodies[i].getId() == body->getId()) return i;
	}

	return -1;
}

void Universe::addBody(Body body) {

	bodies.push_back(body);
}

void Universe::removeBody(Body* body) {

	int index = findBody(body);

	if (index >= 0) {

		bodies.erase(bodies.begin() + index);
	}
}

void Universe::resolveColision(int index1, int index2) {

    if (bodies[index1].getMass() > bodies[index2].getMass()) {

        bodies[index1].absorb(&bodies[index2]);
        removeBody(&bodies[index2]);
        trails.erase(trails.begin() + index2);
    }

    else {

        bodies[index2].absorb(&bodies[index1]);
        removeBody(&bodies[index1]);
        trails.erase(trails.begin() + index1);
    }
}

void Universe::updateColisions() {

    for (int i = 0; i < bodies.size(); i++) {

        for (int j = 0; j < bodies.size(); j++) {

            if ((i != j) && (bodies[i].getShape().getGlobalBounds().intersects(bodies[j].getShape().getGlobalBounds()))) {

               resolveColision(i, j);
            }
        }
    }
}

void Universe::updateGravity() {

    for (int i = 0; i < bodies.size(); i++) {

        bodies[i].updateVelocity(&bodies);
    }
}

void Universe::updatePositions() {

    for (int i = 0; i < bodies.size(); i++) {

        bodies[i].updatePosition();
    }
}

void Universe::updateTrails() {

    for (int i = 0; i < bodies.size(); i++) {

        trails[i].append(sf::Vertex(bodies[i].getShape().getPosition(), bodies[i].getShape().getFillColor()));
    }
}

void Universe::update() {

    updateGravity();

    updatePositions();

    updateColisions();

    updateTrails();
}

void Universe::render() {

    for (int i = 0; i < bodies.size(); i++) {

        bodies[i].render(window);
        if(trails.size()) window->draw(trails[i]);
    }
}