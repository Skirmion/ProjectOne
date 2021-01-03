#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert> 
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(suppress : 4996) 


using namespace std;

class Hacker
{
public:
	Hacker();
	void run();

private:
	void ProcessEvents();
	void render();
	void handleInput(sf::Keyboard::Key, bool);
	void moveView();
	int lenFile();
private:
	ifstream file;
	char* changingText;
	string myText;

	sf::RenderWindow myWindow;
	sf::Text mapping;
	sf::Font font;
	sf::View view;
	sf::Event event;

	int lenghtrendergetline = 0;
	int numberoflines = 1;
	int positionY = 0;
	int sizetext = 16;
	int windowsizeX = 1920; int windowsizeY = 1080;
};

Hacker::Hacker() : myWindow(sf::VideoMode(1920, 1080), "Hack")
{
	///file.open("d:\\1\\файл.txt");
	file.open("text.txt");
	int sizeCode = lenFile();
	char* buffer = new char[sizeCode];
	file.read(buffer, sizeCode);
	changingText = buffer;
	changingText += '\0';
	///delete buffer;
	file.close();
	font.loadFromFile("CyrilicOld.ttf");
	mapping.setFont(font);
	mapping.setPosition(10, 0);
	mapping.setCharacterSize(sizetext);
	mapping.setFillColor(sf::Color::Green);
	view = myWindow.getView();
};

int Hacker::lenFile()
{
	file.seekg(0, ios_base::end); //Стать в конец файла
	int lenf = file.tellg();
	file.seekg(0, ios_base::beg);
	return lenf + 2;
}

void Hacker::run()
{
	while (myWindow.isOpen())
	{
		ProcessEvents();
		render();
	}
}

void Hacker::ProcessEvents()
{
	while (myWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed: handleInput(event.key.code, true); break;
		case sf::Event::KeyReleased: handleInput(event.key.code, false); break;
		case sf::Event::Closed: myWindow.close(); break;
		}
		moveView();
	}
}

void Hacker::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (changingText[lenghtrendergetline] != '"\"' and changingText[lenghtrendergetline + 1] != '0')

	{
		myText = myText + changingText[lenghtrendergetline];
		lenghtrendergetline++;

		if (changingText[lenghtrendergetline] == '\n')
		{
			numberoflines++;
		}
	}

	mapping.setString(myText);
}

void Hacker::render()
{
	myWindow.clear();
	myWindow.setView(view);
	myWindow.draw(mapping);
	myWindow.display();
}

void Hacker::moveView()
{
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		view.move(0, -event.mouseWheelScroll.delta * (sizetext + 4));
		positionY -= event.mouseWheelScroll.delta * (sizetext + 4);
	}

	if (positionY < 0)
	{
		view.setCenter(960.f, 540.f);
		positionY = 0;
	}

	if (positionY > numberoflines * sizetext)
	{
		view.setCenter(windowsizeX / 2, windowsizeY / 2 + numberoflines * (sizetext - 1) - sizetext);
		positionY = numberoflines * sizetext;
	}

	if (numberoflines > windowsizeY / sizetext)
	{
		view.move(0, sizetext - 1);
		positionY += sizetext - 1;
		numberoflines -= 1;
	}
}


int main()
{
	Hacker hacker;
	hacker.run();
	return 0;
}
