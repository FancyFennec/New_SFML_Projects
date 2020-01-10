#pragma once

#include <SFML/Graphics.hpp>

class Boid : public sf::Drawable
{

public:

	int index;
	sf::Vector2f direction;

	Boid() {
		counter++;
		index = counter;

		bounds = sf::Vector2u(1200, 800);

		convex.setPointCount(3);
		convex.setPoint(0, sf::Vector2f(-5, -7));
		convex.setPoint(1, sf::Vector2f(5, -7));
		convex.setPoint(2, sf::Vector2f(0, 7));

		convex.setFillColor(sf::Color::White);

		convex.setPosition(sf::Vector2f((rand() % 100) / 100.0f * bounds.x, (rand() % 100) / 100.0f * bounds.y));

		direction = sf::Vector2f((rand() % 100 - 50) / 100.0f, (rand() % 100 - 50) / 100.0f);
		direction /= norm(direction);
		setRotation();
	};

	float getSquaredDistance(Boid boid) {
		float dx = getPosition().x - boid.getPosition().x;
		float dy = getPosition().y - boid.getPosition().y;
		return dx * dx + dy * dy;
	}

	sf::Vector2f getPosition() {
		return convex.getPosition();
	}

	void setPosition(sf::Vector2f pos) {
		convex.setPosition(sf::Vector2f(
			pos.x < 0.0f ? pos.x + float(bounds.x) : fmodf(pos.x, bounds.x),
			pos.y < 0.0f ? pos.y + float(bounds.y) : fmodf(pos.y, bounds.y)
		));
	}

	float getRotation() {
		return convex.getRotation();
	}

	void setRotation() {
		float angle = direction.y >= 0 ? acosf(direction.x) / pi * 180.0f : 360.0f - acosf(direction.x) / pi * 180.0f;
		convex.setRotation(angle - 90);
	}

	void movePosition(sf::Vector2f delta) {
		setPosition(getPosition() + delta);
	}

	void setBounds(int x, int y) {
		bounds = sf::Vector2u(x, y);
	}

	sf::Vector2u getBounds() {
		return bounds;
	}

	void moveForward(float stepSize) {
		setRotation();
		movePosition(stepSize * direction);
	}

	void setColor(sf::Color col) {
		convex.setFillColor(col);
	}

private:
	const float pi = 3.14159265359f;
	sf::ConvexShape convex;
	sf::Vector2u bounds;

	static int counter;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	float norm(sf::Vector2f vec) {
		return sqrtf(vec.x * vec.x + vec.y * vec.y);
	}
};

int Boid::counter = 0;

void Boid::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(convex, states);
}
