#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <random>
#include <time.h>
#include <math.h>
#include <iostream>

#define STEP 0.0001
#define TOLERANCE 10000
#define RADIUS 4.f
#define white sf::Color::White

short windowHeight = 1000;
short windowWidth = 1000;
double currentAngleP = 0.f;
sf::CircleShape createCircle();
sf::Vertex createLineStart(double xCircle, double yCircle, double currentAngle);
sf::Vertex createLineEnd(double xCircle, double yCircle, double currentAngle);
bool checkCollision(double xCircle, double yCircle, sf::CircleShape currentCircle, sf::Vertex lineEnd, double currentAngle, sf::CircleShape previousCircle);

int main() 
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Windmill Problem");

	std::vector<sf::CircleShape> v;

	sf::Event event;

	srand(time(0));

	for (int i = 0; i < 10; i++) {
		v.push_back(createCircle());
	}

	int vIndex = rand() % v.size();

	sf::CircleShape currentRotationCenter = v[vIndex];
	sf::CircleShape previousCircle;

	while (window.isOpen())
	{
		window.clear();
		while (window.pollEvent(event)) 
		{		
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (currentAngleP == 360) currentAngleP = 0;

		sf::Vertex line[] =
		{
			createLineStart(currentRotationCenter.getPosition().x, currentRotationCenter.getPosition().y, currentAngleP),
			createLineEnd(currentRotationCenter.getPosition().x, currentRotationCenter.getPosition().y, currentAngleP)
		};
		int index = 0;
		for (auto circle : v) 
		{
			if(vIndex != index)
			v[index].setFillColor(white);
			if (checkCollision(circle.getPosition().x, circle.getPosition().y, circle, line[1], currentAngleP, previousCircle) == true)
			{
				previousCircle = currentRotationCenter;
				currentRotationCenter = circle;
				v[vIndex].setFillColor(sf::Color::Red);	
			}
			window.draw(circle);
			index++;
		}
		window.draw(line, 2, sf::Lines);
		window.display();
		currentAngleP += STEP;	
	}
	return 0;
}

sf::CircleShape createCircle()
{
	sf::CircleShape circle(RADIUS);
	circle.setFillColor(white);
	double x = round(windowWidth / 10 + rand() % (windowWidth - windowWidth / 5));
	double y = round(windowHeight / 10 + rand() % (windowHeight - windowHeight / 5));
	circle.move(x, y);
	return circle;
}

sf::Vertex createLineStart(double xCircle, double yCircle, double currentAngle) 
{
	double x = xCircle;
	double y = yCircle;
	return sf::Vertex(sf::Vector2f((x + windowWidth * 1.41 * cos(currentAngle)) + RADIUS, (y + windowWidth * 1.41 * sin(currentAngle)) + RADIUS));
}

sf::Vertex createLineEnd(double xCircle, double yCircle, double currentAngle)
{	
	double x = xCircle;
	double y = yCircle;
	return sf::Vertex(sf::Vector2f((x + (-1.f) * (windowWidth * 1.41 * cos(currentAngle))) + RADIUS, (y + (-1.f) * (windowWidth * 1.41 * sin(currentAngle))) + RADIUS));
}

bool checkCollision(double xCircle, double yCircle, sf::CircleShape currentCircle, sf::Vertex lineEnd, double currentAngle, sf::CircleShape previousCircle)
{
	if (currentCircle.getPosition().x != previousCircle.getPosition().x && currentCircle.getPosition().y != previousCircle.getPosition().y) {
		double k = tan(currentAngle);
		double d = lineEnd.position.y - k * lineEnd.position.x;
		double y = round(k * (xCircle + RADIUS) + d);
		return (y >= yCircle - (STEP * TOLERANCE) && y <= yCircle + (STEP * TOLERANCE)) ? true : false;
	}
	return false;
}




