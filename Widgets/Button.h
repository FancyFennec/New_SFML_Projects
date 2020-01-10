#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
private:
	static int counter;

	bool alreadyPressed = false;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	sf::RectangleShape rect;

public:
	int id;

	Button(int width, int height, int posX = 0, int posY = 0, sf::Color color = sf::Color::White) {
		counter ++; 
		id = counter;

		std::cout << "Button Constructor called" << std::endl;

		rect.setFillColor(color);
		rect.setPosition(sf::Vector2f(posX, posY));
		rect.setSize(sf::Vector2f(width, height));
	}

	sf::Vector2f getPos() {
		return rect.getPosition();
	}

	void setPos(sf::Vector2f newPos) {
		rect.setPosition(newPos);
	}

	void translate(sf::Vector2f vec) {
		rect.setPosition(rect.getPosition() + vec);
	}

	void move(sf::Vector2i& distance) {
		rect.setPosition(rect.getPosition() + sf::Vector2f(distance));
	}
	
	bool isPressed(sf::RenderWindow& window) {
		if (alreadyPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			alreadyPressed = !alreadyPressed;
		}
		if (!alreadyPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			alreadyPressed = !alreadyPressed;
			return isMouseHovering(sf::Mouse::getPosition(window));
		}
		else {
			return false;
		}
	}

	bool isMouseHovering(sf::Vector2i mousePos)
	{
		return mousePos.x >= rect.getPosition().x &&
			mousePos.y >= rect.getPosition().y &&
			mousePos.x <= rect.getPosition().x + rect.getSize().x &&
			mousePos.y <= rect.getPosition().y + rect.getSize().y;
	}
};

int Button::counter = 0;

void Button::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(rect, states);
}


