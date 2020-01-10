#pragma warning( push )
#pragma warning( disable : 26454 )

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Main.h"

int main() {
	unsigned int width = 1200, height = 800;

	sf::RenderWindow window(sf::VideoMode(width, height), "Speed Test Window");
	window.setFramerateLimit(60);

	sf::Event event;
	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("./Staatliches-Regular.ttf");

	sf::Text fpsCounter("Press E or Q to start", font, 30);
	sf::Text startText("Press W, A, S, D to move around and Arrow-Up/Down to zoom In/Out", font, 30);
	sf::Text xCoord("x", font, 30);
	sf::Text yCoord("y", font, 30);

	bool hasAnyButotnBeenPressed = false;

	fpsCounter.setPosition(sf::Vector2f(10.0f, 10.0f));
	startText.setPosition(sf::Vector2f(200.0f, height / 2));
	xCoord.setPosition(sf::Vector2f(width - 100.0f, 10.0f));
	yCoord.setPosition(sf::Vector2f(width - 100.0f, 40.0f));
	
	sf::Texture tex;
	tex.create(width, height);
	sf::Sprite sprite;
	sprite.setTexture(tex);

	sf::Shader fragmentShader;
	fragmentShader.loadFromFile("./FragmentShader.frag", sf::Shader::Fragment);

	float x = 1.0f, y = 0.5f, s = 2.0f;
	fragmentShader.setUniform("x", x);
	fragmentShader.setUniform("y", y);
	fragmentShader.setUniform("s", s);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (window.hasFocus()) {
			bool wasKeyPressed = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				y += 0.005f * s;
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				y -= 0.005f * s;
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				x -= 0.005f * s;
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				x += 0.005f * s;
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				s += 0.01f * s;
				wasKeyPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				s -= 0.01f * s;
				wasKeyPressed = true;
			}

			if (!hasAnyButotnBeenPressed) {
				hasAnyButotnBeenPressed = wasKeyPressed;
			}

			if (wasKeyPressed) {
				fragmentShader.setUniform("x", x);
				fragmentShader.setUniform("y", y);
				fragmentShader.setUniform("s", s);
			}
		}

		fpsCounter.setString(std::to_string(clock.getElapsedTime().asMilliseconds()));
		clock.restart();
		xCoord.setString("X: " + std::to_string(x).substr(0, 5));
		yCoord.setString("Y: " + std::to_string(y).substr(0, 5));

		window.clear(sf::Color::Cyan);

		window.draw(sprite, &fragmentShader);
		window.draw(fpsCounter);
		window.draw(xCoord);
		window.draw(yCoord);

		if(!hasAnyButotnBeenPressed) window.draw(startText);

		window.display();
	}

	return 1;
}