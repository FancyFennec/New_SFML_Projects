#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MousePositionTracker.h"

class Panel : public sf::Drawable
{
private:
	std::vector<Button> buttons;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	sf::RectangleShape rect;
	MousePositionTracker tracker;
	bool alreadyPressed = false;
	bool isTracking = false;

public:
	Panel(int width, int height, int posX = 0, int posY = 0, sf::Color color = sf::Color::White) {
		buttons.reserve(20);

		rect.setFillColor(color);
		rect.setPosition(sf::Vector2f(posX, posY));
		rect.setSize(sf::Vector2f(width, height));
	}

	bool isDragged(sf::RenderWindow& window) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isMouseHovering(sf::Mouse::getPosition(window))) {
			if (!isTracking) isTracking = true;
			sf::Vector2f deltaPos = tracker.getTranslation();
			rect.setPosition(rect.getPosition() + deltaPos);
			for (Button& button : buttons) {
				button.setPos(button.getPos() + deltaPos);
			}
			return true;
		}
		else {
			{
				if (isTracking) isTracking = false;
				tracker.stopTracking();
			}
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

	bool isButtonPressed(int id, sf::RenderWindow& window) {
		bool isButtonPressed = false;
		for (Button& button : buttons) {
			if (button.id == id) isButtonPressed = button.isPressed(window);
		}
		return isButtonPressed;
	}

	void addButton(Button button) {
		button.translate(rect.getPosition());
		buttons.emplace_back(button);
	}
};

void Panel::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(rect, states);

	for (Button button : buttons) {
		target.draw(button, states);
	}
}