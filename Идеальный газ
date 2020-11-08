#include "TXLib.h"
#include <math.h>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>




struct Vector2i
{
	int x;
	int y;
};


struct Sphere
{
	Vector2i position;
	Vector2i velocity;
	int radius;
	RGBTRIPLE color;
};

void drawSphere(Sphere sphere)
{


	txSetColor(RGB(sphere.color.rgbtRed, sphere.color.rgbtGreen, sphere.color.rgbtBlue));
	txSetFillColor(RGB(sphere.color.rgbtRed, sphere.color.rgbtGreen, sphere.color.rgbtBlue));
	txCircle(sphere.position.x, sphere.position.y, sphere.radius);

	txSetFillColor(RGB(0, 0, 0));

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

void specSphere(Sphere particles, int i = 0)
{

};




int main()
{
	int X = 1920;
	int Y = 1080;
	txCreateWindow(X, Y);
	txSetFillColor(RGB(0, 0, 0));

	float t = 1;
	int n = 200;

	Sphere particles[200];
	for (int i = 0; i < 200; i++)
	{
		particles[i] = { {rand() % 1920, rand() % 1080}, {2 * (-1) ^ (rand() % 2), 1 * (-1) ^ (rand() % 2)}, 5, {0, 100, 10} };
	};



	Sphere sp1 = { {200, 300}, {3,0}, 5, {100, 100, 10} };
	Sphere sp2 = { {400, 300}, {-1,0}, 5, {0, 0, 100} };

	while (true)
	{
		txClear();

		txBegin();

		for (int i = 0; i < n; i++)
		{
			drawSphere(particles[i]);
			moveSphere(&particles[i], t);
			checkCollision(&particles[i], t, X, Y);
			checkCollisionTwoSpheres(&sp1, &particles[i]);
			checkCollisionTwoSpheres(&sp2, &particles[i]);
			for (int j = i + 1; j < n; j++)
			{
				checkCollisionTwoSpheres(&particles[i], &particles[j]);
			};
		};


		drawSphere(sp1);
		drawSphere(sp2);
		txEnd();

		moveSphere(&sp1, t);
		moveSphere(&sp2, t);

		checkCollision(&sp1, t, X, Y);
		checkCollision(&sp2, t, X, Y);

		checkCollisionTwoSpheres(&sp1, &sp2);


	};



	return 0;
}
