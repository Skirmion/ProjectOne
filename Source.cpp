#include "TXLib.h"
#include <math.h>
#include <string>
#include <cstdlib>
#include "iostream"
#include "string"




struct Spring
{
	float k;
	float l;
};


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

void lawgHookeCheck(Sphere one, Sphere two, Spring spring)
{
	if (pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2) < spring.l)
	{
		string c = {};
	};
	if (pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2) > spring.l)
	{
		float c_x = pow(pow((one.position.x - two.position.x), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);  
		float c_y = pow(pow((one.position.y - two.position.y), 2), 0.5) / pow(pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2), 0.5);
	};
	if (pow((one.position.x - two.position.x), 2) + pow((one.position.y - two.position.y), 2) == spring.l)
	{
		string c = {};
	};
};


int main()
{
	int X = 1920;
	int Y = 1080;
	txCreateWindow(X, Y);
	txSetFillColor(RGB(0, 0, 0));

	Spring spring = { 0,0 };

	float t = 1;
	int n = 3;

	int spconnection[3][2] = { {2, 3}, {1, 3}, {1, 2} };

	Sphere particles[3];
	for (int i = 0; i < n; i++)
	{
		particles[i] = { {float(rand() % 1920), float(rand() % 1080)}, {float(2 * (-1) ^ (rand() % 2)), float(1 * (-1) ^ (rand() % 2))}, 5, {0, 100, 10} };
	};



	Sphere sp1 = { {200, 300}, {30,0}, 5, {100, 100, 10} };
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
	    for (int u = 0; u < n; u++)
	    {
		    for (int j = 0; j < sizeof(spconnection[u]); j += 1)
		    {
				cout << u << j << '\n';

		       lawgHookeCheck(particles[u], particles[spconnection[u][j]], spring);


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