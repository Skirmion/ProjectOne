#include <math.h>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "windows.h"
using namespace std;


struct Vector2i
{
	float x;
	float y;
};

struct Sphere
{
	Vector2i position;
	Vector2i velocity;
	int radius;
	int red;
	int green;
	int blue;
};

void drawSphere(Sphere sphere, sf::RenderWindow* window)
{
	sf::CircleShape circle(sphere.radius, 30);
	circle.setFillColor(sf::Color(sphere.red, sphere.green, sphere.blue));
	circle.setPosition(sphere.position.x, sphere.position.y);
	window->draw(circle);
};

void moveSphere(Sphere* sphere, float t)
{
	(*sphere).position.x += (*sphere).velocity.x * t;
	(*sphere).position.y += (*sphere).velocity.y * t;
};

void checkCollision(Sphere* sphere, int t, int X, int Y)
{
	if (((*sphere).position.x + (*sphere).velocity.x * t) > (X - (*sphere).radius) and (*sphere).velocity.x > 0)
	{
		(*sphere).position.x += (*sphere).velocity.x;
		(*sphere).velocity.x = -(*sphere).velocity.x;
	};

	if (((*sphere).position.x + (*sphere).velocity.x * t) < ((*sphere).radius) and (*sphere).velocity.x < 0)
	{
		(*sphere).position.x += (*sphere).velocity.x;
		(*sphere).velocity.x = -(*sphere).velocity.x;
	};
	if (((*sphere).position.y + (*sphere).velocity.y * t) > (Y - (*sphere).radius) and (*sphere).velocity.y > 0)
	{
		(*sphere).position.y += (*sphere).velocity.y;
		(*sphere).velocity.y = -(*sphere).velocity.y;
	};

	if (((*sphere).position.y + (*sphere).velocity.y * t) < (*sphere).radius and (*sphere).velocity.y < 0)
	{
		(*sphere).position.y += (*sphere).velocity.y;
		(*sphere).velocity.y = -(*sphere).velocity.y;
	};
};

bool ballsDangerouslyClose(Sphere one, Sphere two)
{
	if (pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2) < ((one.radius + 2) * (two.radius + 2)))
	{
		return true;
	};
	return false;
};

bool ballDangerouslyCloseVector(Sphere one, Sphere two)
{
	if (pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2) >= pow((one.position.x + one.velocity.x - two.position.x - two.velocity.x), 2) + pow((one.position.y + one.velocity.y - two.position.y - +two.velocity.y), 2))
	{
		return true;
	};
	return false;
};

void checkCollisionTwoSpheres(Sphere* one, Sphere* two)
{
	if (ballsDangerouslyClose(*one, *two) and ballDangerouslyCloseVector(*one, *two))
	{
		int buffer1 = (*one).velocity.x;
		int buffer2 = (*one).velocity.y;
		(*one).velocity.x = (*two).velocity.x;
		(*one).velocity.y = (*two).velocity.y;
		(*two).velocity.x = buffer1;
		(*two).velocity.y = buffer2;
	};
};

void lawgHookeCheck(Sphere one, Sphere two, float *k_x, float *k_y)
{
	if (pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5) < 120)
	{
		*k_x = pow(pow((one.position.x - two.position.x), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);
		*k_y = pow(pow((one.position.y - two.position.y), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);
	};
	if (pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5) > 120)
	{
		*k_x = - pow(pow((one.position.x - two.position.x), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);  
		*k_y = - pow(pow((one.position.y - two.position.y), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);
	};
	if (pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5) == 120)
	{
		*k_x = 0;
		*k_y = 0;
	};
};

void accelerationSpring(Sphere* one, Sphere two, float k_x, float k_y, float kk)
{
	(*one).velocity.x += kk * k_x * ((*one).position.x - two.position.x);
	(*one).velocity.y += kk * k_y * ((*one).position.y - two.position.y);
};


int main()
{
	int X = 1920;
	int Y = 1080;
	sf::RenderWindow window(sf::VideoMode(X, Y), "Window");

	float t = 1;
	const int n = 50;
	float kk = 0.000008;

	int spconnection[n][n - 1];

		for (int k = 0; k < n; k++)
		{
			for (int s = 0; s < n; s++)
			{   
				if (k != s)
				{
					if (s < k)
					{
						spconnection[k][s] = s;
					}
					if (s > k)
					{
						spconnection[k][s - 1] = s;
					}
				};  

			};

		};

	Sphere particles[n];
	for (int i = 0; i < n; i++)
	{
		particles[i] = { {float(i*5), float(i*2)}, {((-1) ^ (rand() % 2))*(float((rand() % 100)) / 100), ((-1) ^ (rand() % 2))*(float(rand() % 100) / 100)}, 5, rand()*100 % 255, rand()*100 % 255, rand()*100 % 255 };
	};

    float k_x = 0; 
	float k_y = 0;

	while (true)
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		};

        for (int u = 0; u < n; u++)
		{
			for (int j = 0; j < n - 1; j++)
			{
				lawgHookeCheck(particles[u], particles[spconnection[u][j]], &k_x, &k_y);
				accelerationSpring(&particles[u], particles[spconnection[u][j]], k_x, k_y, kk);
			};
		};

		for (int i = 0; i < n; i++)
		{
			drawSphere(particles[i], &window);
			moveSphere(&particles[i], t);
			checkCollision(&particles[i], t, X, Y);
			for (int j = i + 1; j < n; j++)
			{
				//checkCollisionTwoSpheres(&particles[i], &particles[j]);
			};
		};

		window.display();
	};

	return 0;
}
