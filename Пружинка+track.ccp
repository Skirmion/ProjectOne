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

struct Spring
{
	Vector2i vec;
	float k;
	float l;
};

struct Sphere
{
	Vector2i position;
	Vector2i velocity;
	int radius;
	float red;
	float green;
	float blue;
	float cr;
	float cg;
	float cb;
};

void moveSphere(Sphere* sphere, float t)
{
	(*sphere).position.x += (*sphere).velocity.x * t;
	(*sphere).position.y += (*sphere).velocity.y * t;
};

void checkCollisionX(Sphere sphere, int t, int X, string* changecollision)
{
	if ((sphere.position.x + sphere.velocity.x * t) > (X - sphere.radius) and sphere.velocity.x > 0)
	{
		(*changecollision)[0] = 1;
	};

	if ((sphere.position.x + sphere.velocity.x * t) < (sphere.radius) and sphere.velocity.x < 0)
	{
		(*changecollision)[0] = -1;
	};
};

void checkCollisionY(Sphere sphere, int t, int Y, string* changecollision)
{
	if ((sphere.position.y + sphere.velocity.y * t) > (Y - sphere.radius) and sphere.velocity.y > 0)
	{
		(*changecollision)[1] = 1;
	};

	if ((sphere.position.y + sphere.velocity.y * t) < sphere.radius and sphere.velocity.y < 0)
	{
		(*changecollision)[1] = -1;
	};
};

void collisionChange(Sphere* sphere, int t, string changecollision)
{
	if (changecollision[0] != 0)
	{
		(*sphere).position.x += (*sphere).velocity.x * t;
		(*sphere).velocity.x = - (*sphere).velocity.x;
	};
	
	if (changecollision[1] != 0)
	{
		(*sphere).position.y += (*sphere).velocity.y * t;
		(*sphere).velocity.y = - (*sphere).velocity.y;
	};
};

void drawSphere(Sphere bufsp, sf::RenderWindow* window, int t, int X, int Y, int track)
{
	bufsp.velocity.x = -bufsp.velocity.x;
	bufsp.velocity.y = -bufsp.velocity.y;
	string gg = { 0,0 };
	for (int a = track; a > -1; a--)
	{
		gg = { 0, 0 };
		checkCollisionX(bufsp, t, X, &gg);
		checkCollisionY(bufsp, t, Y, &gg);
		collisionChange(&bufsp, t, gg);
		moveSphere(&bufsp, t);
	};

	bufsp.velocity.x = -bufsp.velocity.x;
	bufsp.velocity.y = -bufsp.velocity.y;
	float red = bufsp.red;
	float green = bufsp.green;
	float blue = bufsp.blue;
	float r = bufsp.radius;

	for (int z = 1; z < track + 1; z += 1)
	{   
		gg = { 0, 0 };
		checkCollisionX(bufsp, t, X, &gg);
		checkCollisionY(bufsp, t, Y, &gg);
		collisionChange(&bufsp, t, gg);
		moveSphere(&bufsp, t);

		sf::CircleShape circle(r - 10*(1 - (track - z) / track), 30 - 20*(1 - (track - z)/track));
		circle.setFillColor(sf::Color(red * z/track, green * z / track, blue * z / track, 255));
		circle.setPosition(bufsp.position.x, bufsp.position.y);
		window->draw(circle);
		
	};
};

void lawgHookeCheck(Sphere one, Sphere two, Spring *spring)
{
	if (pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5) < spring->l)
	{
		spring->vec.x = pow(pow((one.position.x - two.position.x), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);
		spring->vec.y = pow(pow((one.position.y - two.position.y), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);
	};
	if (pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5) > spring->l)
	{
		spring->vec.x = - pow(pow((one.position.x - two.position.x), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);
		spring->vec.y = - pow(pow((one.position.y - two.position.y), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);
	};
	if (pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5) == spring->l)
	{
		spring->vec.x = 0;
		spring->vec.y = 0;
	};
};

void accelerationSpring(Sphere* one, Sphere* two, Spring spring)
{
	(*one).velocity.x += spring.k * spring.vec.x * ((*one).position.x - (*two).position.x);
	(*one).velocity.y += spring.k * spring.vec.y * ((*one).position.y - (*two).position.y);
	(*two).velocity.x -= spring.k * spring.vec.x * ((*one).position.x - (*two).position.x);
	(*two).velocity.y -= spring.k * spring.vec.y * ((*one).position.y - (*two).position.y);
};

bool ballsDangerouslyClose(Sphere one, Sphere two)
{
	if (pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2) <= ((one.radius + 4) * (two.radius + 4)))
	{
		return true;
	};
	return false;
};

bool ballDangerouslyCloseVector(Sphere one, Sphere two)
{
	if (pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2) > pow((one.position.x + one.velocity.x - two.position.x - two.velocity.x), 2) + pow((one.position.y + one.velocity.y - two.position.y - +two.velocity.y), 2))
	{
		return true;
	};
	return false;
};

void checkCollisionTwoSpheres(Sphere* onesphere, Sphere* twosphere)
{
	if (ballsDangerouslyClose(*onesphere, *twosphere) and ballDangerouslyCloseVector(*onesphere, *twosphere))
	{
		int buffer1 = (*onesphere).velocity.x;
		int buffer2 = (*onesphere).velocity.y;
		(*onesphere).velocity.x = (*twosphere).velocity.x;
		(*onesphere).velocity.y = (*twosphere).velocity.y;
		(*twosphere).velocity.x = buffer1;
		(*twosphere).velocity.y = buffer2;
	};
};

void rainbowSphere(Sphere* one)
{
	if (one -> red <= 0 and one -> cr < 0)
	{
		one -> cr = 1;
	};
	if (one -> red >= 255 and one -> cr > 0)
	{
		one -> cr = - 1;
	};
	if (one -> green <= 0 and one -> cg < 0)
	{
		one -> cg = 1;
	};
	if (one -> green >= 255 and one -> cg > 0)
	{
		one -> cg = -1;
	};
	if (one -> blue <= 0 and one -> cb < 0)
	{
		one -> cb = 1;
	};
	if (one->blue >= 255 and one->cb > 0)
	{
		one->cb = -1;
	};

	one -> red += one->cr * (abs(rand() % 2));
	one -> green += one->cg * (abs(rand() % 2));
	one -> blue += one->cb * (abs(rand() % 2));
}


int main()
{
	int X = 1920;
	int Y = 1080;
	sf::RenderWindow window(sf::VideoMode(X, Y), "Window");

	float t = 1;
	const int n = 8;
	int track = 25;
	string changecollision = {0, 0};

    Sphere particles[n];
	Spring spring = { 0, 0, 0.000008, 50 };
    int spconnection[n][n - 1];

		for (int i = 0; i < n; i++)
		{
			for (int s = 0; s < n; s++)
			{   
				particles[i] = { {float(i * 3), float(i * 2)}, {((-1) ^ (rand() % 2)) * (float((rand() % 100)) / 100), ((-1) ^ (rand() % 2)) * (float(rand() % 100) / 100)}, 5, float(rand() % 255), float(rand() % 255), float(rand() % 255), 1, 1, 1 };

				if (s < i)
				{
					spconnection[i][s] = s;
				}
				if (s > i)
				{
					spconnection[i][s - 1] = s;
				} 

			};

		};

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

		for (int i = 0; i < n; i++)
		{
			changecollision = { 0, 0 };
			checkCollisionX(particles[i], t, X, &changecollision);
			checkCollisionY(particles[i], t, Y, &changecollision);
			collisionChange(&particles[i], t, changecollision);

			for (int j = i; j < n - 1; j++)
			{
				lawgHookeCheck(particles[i], particles[spconnection[i][j]], &spring);
				accelerationSpring(&particles[i], &particles[spconnection[i][j]], spring);

				//checkCollisionTwoSpheres(&particles[i], &particles[j + 1]);
			};

			rainbowSphere(&particles[i]);
		
			moveSphere(&particles[i], t);
			drawSphere(particles[i], &window, t, X, Y, track);
		};

		window.display();
	};

	return 0;
}
