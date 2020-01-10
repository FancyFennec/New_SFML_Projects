#pragma warning( push )
#pragma warning( disable : 26454 )

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Main.h"

int main() {
	unsigned int width = 1200, height = 800;
	float pi = 3.14159265359f;

	sf::RenderWindow window(sf::VideoMode(width, height), "Speed Test Window");
	window.setFramerateLimit(60);

	std::vector<sf::Uint8> pixels;

	for (int j = 0; j < 800; j++) {
		for (int i = 0; i < 800; i++) {
			float x = (i - 400) / 400.0f;
			float y = (j - 400) / 400.0f;
			if (x*x + y*y <= 1) {
				sf::Vector3f newNormal;

				newNormal.x = pi * x / sqrtf(x * x + y * y) * sin(sqrtf(x * x + y * y) * pi);
				newNormal.y = pi * y / sqrtf(x * x + y * y) * sin(sqrtf(x * x + y * y) * pi);
				newNormal.z = 1;

				float normalValue = sqrtf(newNormal.x * newNormal.x + newNormal.y * newNormal.y + newNormal.z * newNormal.z);
				newNormal /= normalValue;
				
				newNormal = (newNormal / 2.0f + sf::Vector3f(0.5f, 0.5f, 0.5f)) * 255.0f;

				pixels.push_back(sf::Uint8(newNormal.x));
				pixels.push_back(sf::Uint8(newNormal.y));
				pixels.push_back(sf::Uint8(newNormal.z));
				pixels.push_back(sf::Uint8(255));
			}
			else {
				pixels.push_back(sf::Uint8(127));
				pixels.push_back(sf::Uint8(127));
				pixels.push_back(sf::Uint8(255));
				pixels.push_back(sf::Uint8(255));
			}
		}
	}

	sf::Image testImg;
	testImg.create(800, 800, pixels.data());
	testImg.saveToFile("TestFile.png");

	sf::Event event;
	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("./Staatliches-Regular.ttf");

	sf::Text fpsCounter("0", font, 30);
	sf::Text startText("Testing Normal Blending", font, 30);

	bool hasAnyButonBeenPressed = false;

	fpsCounter.setPosition(sf::Vector2f(10.0f, 10.0f));
	startText.setPosition(sf::Vector2f(200.0f, 10));

	sf::Texture normalTex1;
	normalTex1.loadFromFile("test1.png");
	sf::Sprite normalSprite;
	normalSprite.setTexture(normalTex1);

	sf::Texture normalTex2;
	normalTex2.loadFromFile("test2.png");

	sf::Image colorImg;
	colorImg.create(width, height, sf::Color(255, 170, 170));
	sf::Texture colorTex;
	colorTex.loadFromImage(colorImg);

	sf::Shader normalBlendingShader;
	normalBlendingShader.loadFromFile("./NormalBlending.frag", sf::Shader::Fragment);
	normalBlendingShader.setUniform("normals1", normalTex1);
	normalBlendingShader.setUniform("normals2", normalTex2);

	sf::RenderTexture renderTex;
	renderTex.create(width, height);
	renderTex.draw(normalSprite, &normalBlendingShader);
	renderTex.display();

	normalTex1 = renderTex.getTexture();

	sf::Shader fragmentShader;
	fragmentShader.loadFromFile("./FragmentShader.frag", sf::Shader::Fragment);

	fragmentShader.setUniform("normalMap", normalTex1);
	fragmentShader.setUniform("layerTex", colorTex);

	sf::Vector3f lightpos(0, 0, 300);
	fragmentShader.setUniform("lightPos", lightpos);
	fragmentShader.setUniform("lightCol", sf::Vector3f(1, 1, 1));

	fragmentShader.setUniform("shininess", 64.f);

	fragmentShader.setUniform("specInt", 0.5f);
	fragmentShader.setUniform("ambInt", 0.1f);
	fragmentShader.setUniform("difInt", 1.0f);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				lightpos.y -= 10.0f;
				fragmentShader.setUniform("lightPos", lightpos);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				lightpos.y += 10.0f;
				fragmentShader.setUniform("lightPos", lightpos);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				lightpos.x += 10.0f;
				fragmentShader.setUniform("lightPos", lightpos);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				lightpos.x -= 10.0f;
				fragmentShader.setUniform("lightPos", lightpos);
			}
		}

		if (window.hasFocus()) {
			bool wasKeyPressed = false;
		}

		fpsCounter.setString(std::to_string(clock.getElapsedTime().asMilliseconds()));
		clock.restart();

		window.clear(sf::Color::Cyan);

		window.draw(normalSprite, &fragmentShader);
		window.draw(fpsCounter);

		if(!hasAnyButonBeenPressed) window.draw(startText);

		window.display();
	}

	return 1;
}