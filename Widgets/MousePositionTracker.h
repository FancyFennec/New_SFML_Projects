#pragma once

#include <SFML/Graphics.hpp>

class MousePositionTracker
{
public:

	bool isTracking = false;

	MousePositionTracker() {}

	sf::Vector2f getTranslation() {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (!isTracking) {
				return startTracking();
			}
			else {
				return getDeltaPos();
			}
		}
		else {
			return stopTracking();
		}
	}


	sf::Vector2f startTracking() {
		isTracking = true;
		pos = sf::Vector2f(sf::Mouse::getPosition());
		lastPos = pos;
		return sf::Vector2f(0, 0);
	}


	sf::Vector2f stopTracking() {
		isTracking = false;
		return sf::Vector2f(0, 0);
	}

	sf::Vector2f getDeltaPos() {
		lastPos = pos;
		pos = sf::Vector2f(sf::Mouse::getPosition());

		return pos - lastPos;
	}

private:
	sf::Vector2f pos;
	sf::Vector2f lastPos;
};

