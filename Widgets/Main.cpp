#pragma warning( push )
#pragma warning( disable : 26454 )

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Panel.h"
#include "MousePositionTracker.h"

int main() {
	unsigned int width = 1200, height = 800;

	sf::RenderWindow window(sf::VideoMode(width, height), "Speed Test Window");
	window.setFramerateLimit(60);

	sf::Event event;
	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("./Staatliches-Regular.ttf");

	MousePositionTracker tracker;

	Panel panel(400, 400, 50, 50);
	panel.addButton(Button(100, 50, 50, 50, sf::Color::Green));
	panel.addButton(Button(100, 50, 50, 150, sf::Color::Red));

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (window.hasFocus()) {
			bool wasKeyPressed = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				wasKeyPressed = true;
			}

			if (wasKeyPressed) {
			}
		}

		if (panel.isDragged(window)) {
			std::cout << "panel is being dragged" << std::endl;
		}

		if (panel.isButtonPressed(1, window)) {
			std::cout << "Button 1 Pressed" << std::endl;
		}
		if (panel.isButtonPressed(2, window)) {
			std::cout << "Button 2 Pressed" << std::endl;
		}

		window.clear(sf::Color::Cyan);

		window.draw(panel);

		window.display();
	}

	return 1;
}