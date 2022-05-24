#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <thread>

// global variables
const int WIDTH = 1920;
const int HEIGHT = 1800;
#define SQRT_MAGIC_F 0x5f3759df

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<int> dist(-2, 2);
std::uniform_real_distribution<float> mass(0.1f, 1.0f);

// utility functions

// calculates the square root of x using the Quake III method using bit shifting
float quake3sqrt(const float x) {
	const float xhalf = 0.5f * x;
	union {
		float x;
		int i;
	} u;
	u.x = x;
	u.i = SQRT_MAGIC_F - (u.i >> 1);
	return x * u.x * (1.5f - xhalf * u.x * u.x);
}
// calculates the distance between two vectors
float distance(sf::Vector2f a, sf::Vector2f b) {
	return quake3sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// calculates when a vector is divided by a scalar
sf::Vector2f divideVectorAndScalar(sf::Vector2f vector, float scalar) {
	return sf::Vector2f(vector.x / scalar, vector.y / scalar);
}

// clamps the magnitude of a vector to a maximum
sf::Vector2f clampVectormax(sf::Vector2f vector, float max) {
	float length = quake3sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	float f = std::min(length, max) / length;
	return sf::Vector2f(vector.x * f, vector.y * f);
}

// sets the magnitude of a vector to a maximum
sf::Vector2f setMagnitude(sf::Vector2f vector, float magnitude) {
	return divideVectorAndScalar(
	    vector, distance(vector, sf::Vector2f(0, 0)) / magnitude);
}

// multiplies a vector by a scalar
sf::Vector2f multiplyVectorAndScalar(sf::Vector2f vector, float scalar) {
	return sf::Vector2f(vector.x * scalar, vector.y * scalar);
}

// self-explanatory
void swap(sf::Vector2f& a, sf::Vector2f& b) {
	sf::Vector2f temp = a;
	a = b;
	b = temp;
}

// to do: write the boid class with maxturnrate

class Boid {
       public:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float maxSpeed;
	float maxForce;
	float perceptionRadius;
	Boid() {
		this->position =
		    sf::Vector2f(std::rand() % WIDTH, std::rand() % HEIGHT);
		this->velocity = sf::Vector2f(dist(rng), dist(rng));
		this->acceleration = sf::Vector2f(0, 0);
		this->perceptionRadius = 50;
		this->maxForce = 0.2;
		this->maxSpeed = 3;
	}

	// wraps the boid around the screen
	void checkEdges() {
		if (this->position.x > WIDTH) {
			this->position.x = 0;
		}
		if (this->position.x < 0) {
			this->position.x = WIDTH;
		}
		if (this->position.y > HEIGHT) {
			this->position.y = 0;
		}
		if (this->position.y < 0) {
			this->position.y = HEIGHT;
		}
	}
	// aligins boids to each other
	sf::Vector2f align(std::vector<Boid> boids) {
		sf::Vector2f avg_velocity(0, 0);
		int count = 0;
		for (int i = 0; i < boids.size(); i++) {
			if (distance(boids[i].position, this->position) <
				this->perceptionRadius &&
			    boids[i].position != this->position) {
				avg_velocity += boids[i].velocity;
				count++;
			}
		}
		if (count > 0) {
			avg_velocity =
			    divideVectorAndScalar(avg_velocity, count);
			avg_velocity =
			    setMagnitude(avg_velocity, this->maxSpeed);
			avg_velocity = avg_velocity - this->velocity;
			avg_velocity =
			    clampVectormax(avg_velocity, this->maxForce);
		}
		return avg_velocity;
	}

	// calculates the distance between the boid and the other boids and
	// moves the boid towards the other boids
	sf::Vector2f cohesion(std::vector<Boid> boids) {
		sf::Vector2f avg_position(0, 0);
		int count = 0;
		for (int i = 0; i < boids.size(); i++) {
			if (distance(boids[i].position, this->position) <
				this->perceptionRadius &&
			    boids[i].position != this->position) {
				avg_position += boids[i].position;
				count++;
			}
		}

		if (count > 0) {
			avg_position =
			    divideVectorAndScalar(avg_position, count);
			avg_position = avg_position - this->position;
			avg_position =
			    setMagnitude(avg_position, this->maxSpeed);
			avg_position = avg_position - this->velocity;
			avg_position =
			    clampVectormax(avg_position, this->maxForce);
		}

		return avg_position;
	}

	// calculates the distance between the boid and the other boids and
	// moves the boid away from the other boids
	sf::Vector2f seperation(std::vector<Boid> boids) {
		sf::Vector2f avg_position(0, 0);
		int count = 0;
		for (int i = 0; i < boids.size(); i++) {
			float dist =
			    distance(boids[i].position, this->position);
			if (dist < this->perceptionRadius &&
			    boids[i].position != this->position) {
				sf::Vector2f diff =
				    this->position - boids[i].position;
				diff =
				    divideVectorAndScalar(diff, pow(dist, 2));
				avg_position += diff;
				count++;
			}
		}
		if (count > 0) {
			avg_position =
			    divideVectorAndScalar(avg_position, count);
			avg_position =
			    setMagnitude(avg_position, this->maxSpeed);
			avg_position = avg_position - this->velocity;
			avg_position =
			    clampVectormax(avg_position, this->maxForce);
		}
		return avg_position;
	}

	// calculates the the boid movement for the next frame
	void checkFlock(std::vector<Boid> boids) {
		sf::Vector2f alignment = this->align(boids);
		sf::Vector2f cohesion = this->cohesion(boids);
		sf::Vector2f seperation = this->seperation(boids);
		this->acceleration += seperation;
		this->acceleration += alignment;
		this->acceleration += cohesion;
	}

	void update(std::vector<Boid> boids) {
		this->checkFlock(boids);
		this->velocity += this->acceleration;
		this->position += this->velocity;
		this->acceleration = sf::Vector2f(0, 0);
		
		this->checkEdges();
	}
	void show(sf::RenderWindow& window) {
		sf::CircleShape shape(10);
		shape.setPosition(this->position);
		shape.setFillColor(sf::Color::Red);
		window.draw(shape);
	}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Boids");
	window.setFramerateLimit(60);
	sf::Event event;
	std::vector<Boid> flock;
	std::vector<Boid> snapshot;
	for (int i = 0; i < 250; i++) {
		Boid boid;
		flock.push_back(boid);
		snapshot.push_back(boid);
	}
	

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		snapshot = flock;
		for (int i = 0; i < flock.size(); i++) {
			flock[i].update(snapshot);
			flock[i].show(window);
		}
		window.display();
	}
	return 0;
}

