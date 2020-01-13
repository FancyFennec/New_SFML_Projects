#pragma once

#include "Boid.h"
#include <vector>
class Swarm : public sf::Drawable
{
public:
	Swarm() {};

	float radius = 5000.0f;

	float separation = 8.0f;
	float alignment = 0.04f;
	float cohesion = 0.1f;

	void addBoid(Boid boid) {
		boids.push_back(boid);
		newDirections.push_back(boid.direction);
	}

	void addBoids(unsigned int n) {
		for (int i = 0; i < n; i++) {
			boids.push_back(Boid());
			newDirections.push_back(boids[i].direction);
		}
	}

	void logFirstBoidRotation() {
		std::cout << "Rot: " << boids[0].getRotation() << "X: " << boids[0].direction.x << "Y: " << boids[0].direction.y << std::endl;
	}

	void alignBoids() {
		if (boids.size() <= 1) return;

#pragma omp parallel for
		for (int i = 0; i < boids.size(); i++) {
			int counter = 0;

			sf::Vector2f averagePos;
			sf::Vector2f directionOfOthers;
			sf::Vector2f averageDirection;

			for (Boid& otherBoid : boids) {
				float dist = boids[i].getSquaredDistance(otherBoid);

				if (dist  > 0 && dist < radius) {
					counter++;

					averagePos += otherBoid.getPosition();
					sf::Vector2f directionOfOther = boids[i].getPosition() - otherBoid.getPosition();
					directionOfOther /= boids[i].getSquaredDistance(otherBoid);

					directionOfOthers += directionOfOther;
					averageDirection += otherBoid.direction;
				}
			}

			if (counter > 0) {
				averagePos /= float(counter);
				directionOfOthers /= float(counter);
				averageDirection /= float(counter);

				sf::Vector2f directionToAveragePos = averagePos - boids[i].getPosition();
				directionToAveragePos /= norm(directionToAveragePos);

				sf::Vector2f newDirection = boids[i].direction + directionToAveragePos * cohesion + directionOfOthers * separation + averageDirection * alignment;
				newDirection /= norm(newDirection);

				newDirections[i] = newDirection;
			}
			else {
				newDirections[i] = boids[i].direction;
			}
		}

		for (auto boid = boids.begin(); boid < boids.end(); boid++) {
			boid->direction = newDirections[boid - boids.begin()];
		}
	}

	void moveBoidsForward(float speed) {
		for (auto boid = boids.begin(); boid < boids.end(); boid++) {
			boid->moveForward(speed);
		}
	}

private:
	const float pi = 3.14159265359f;
	std::vector<Boid> boids;
	std::vector<sf::Vector2f> newDirections;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	float norm(sf::Vector2f vec) {
		return sqrtf(vec.x * vec.x + vec.y * vec.y);
	}
};

void Swarm::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	for (auto boid = boids.begin(); boid < boids.end(); boid++) {
		target.draw(*boid, states);
	}
}

