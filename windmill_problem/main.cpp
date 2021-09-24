#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <random>
#include <time.h>
#include <math.h>
#include <iostream>

#define white sf::Color::White

int windowHeight = 1000;
int windowWidth = 1000;
float currentAngleP = 0.f;
float currentAngleN = 180.f;
sf::CircleShape createCircle();
sf::Vertex createLineStart(float xCircle, float yCircle, float currentAngle);
sf::Vertex createLineEnd(float xCircle, float yCircle, float currentAngle);
bool checkCollision(float xCircle, float yCircle, sf::Vertex lineStart, sf::Vertex lineEnd);

int main() 
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Windmill Problem");

	std::vector<sf::CircleShape> v;

	sf::Event event;

	srand(time(0));

	for (int i = 0; i < 20; i++) {
		v.push_back(createCircle());
	}

	int vIndex = rand() % v.size();

	sf::CircleShape currentRotationCenter = v[vIndex];
	v[vIndex].setFillColor(sf::Color::Red);

	window.setFramerateLimit(100);

	while (window.isOpen())
	{
		while (window.pollEvent(event)) 
		{		
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (currentAngleP == 360) currentAngleP = 0;
		if (currentAngleN == 360) currentAngleN = 0;

		window.clear();
		sf::Vertex line[] =
		{
			createLineStart(currentRotationCenter.getPosition().x, currentRotationCenter.getPosition().y, currentAngleP),
			createLineEnd(currentRotationCenter.getPosition().x, currentRotationCenter.getPosition().y, currentAngleP)
		};
		for (auto circle : v) {
			window.draw(circle);
			if (checkCollision(circle.getPosition().x, circle.getPosition().y, line[0], line[1]) == true)
			std::cout << "True\n";
		}		
		window.draw(line, 2, sf::Lines);
		window.display();
		currentAngleP += 0.001;
		currentAngleN += 0.001;
		
	}
	return 0;
}

sf::CircleShape createCircle()
{
	sf::CircleShape circle(4.f);
	circle.setFillColor(white);
	float x = windowWidth / 20 + rand() % (windowWidth - windowWidth/10);
	float y = windowHeight / 20 + rand() % (windowHeight - windowHeight / 10);
	circle.move(x, y);
	return circle;
}

sf::Vertex createLineStart(float xCircle, float yCircle, float currentAngle) 
{
	float x = xCircle;
	float y = yCircle;
	return sf::Vertex(sf::Vector2f((x + windowWidth * 1.41 * cos(currentAngle)) + 4.f, (y + windowWidth * 1.41 * sin(currentAngle)) + 4.f));
}

sf::Vertex createLineEnd(float xCircle, float yCircle, float currentAngle)
{	
	float x = xCircle;
	float y = yCircle;
	return sf::Vertex(sf::Vector2f((x + (-1.f) * (windowWidth * 1.41 * cos(currentAngle))) + 4.f, (y + (-1.f) * (windowWidth * 1.41 * sin(currentAngle))) + 4.f));
}

bool checkCollision(float xCircle, float yCircle, sf::Vertex lineStart, sf::Vertex lineEnd)
{
	float checkA = round(((xCircle + 4.f) / lineEnd.position.x) - lineStart.position.x);
	float checkB = round(((yCircle + 4.f) / lineEnd.position.y) - lineStart.position.y);
	std::cout << checkA << " == ";
	std::cout << checkB << std::endl;
	if (checkA != checkB) return false;
	return true;
}




