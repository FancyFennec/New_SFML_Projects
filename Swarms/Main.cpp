#pragma warning( push )
#pragma warning( disable : 26454 )

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Main.h"
#include "Swarm.h"

int main() {
	unsigned int width = 1200, height = 800;
	float pi = 3.14159265359f;

	sf::RenderWindow window(sf::VideoMode(width, height), "Speed Test Window");
	window.setFramerateLimit(60);

	sf::Event event;
	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("./Staatliches-Regular.ttf");

	sf::Text fpsCounter("0", font, 50);
	sf::Text startText("Testing Swarms", font, 30);

	bool hasAnyButonBeenPressed = false;

	fpsCounter.setPosition(sf::Vector2f(10.0f, 10.0f));
	startText.setPosition(sf::Vector2f(200.0f, 10));

	Swarm swarm;
	swarm.addBoids(200);
	
	bool isPaused = false;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			if (sf::Event::KeyReleased == event.type && event.key.code == sf::Keyboard::Space) {
				isPaused = !isPaused;
			}
		}

		fpsCounter.setString(std::to_string(clock.getElapsedTime().asMilliseconds()));
		clock.restart();

		window.clear(sf::Color::Blue);

		if (!isPaused) {
			swarm.alignBoids();
			swarm.moveBoidsForward(3.0f);
			//swarm.logFirstBoidRotation();
		}

		window.draw(fpsCounter);
		window.draw(swarm);

		if(!hasAnyButonBeenPressed) window.draw(startText);

		window.display();
	}

	return 1;
}