#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
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
	void update();
	void moveView();

private:
	ifstream file;

	string changingText = "";
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
	file.open("text.txt");
	string str = "";
	while (str != "return 0;\n}")
	{
		getline(file, str);
		changingText = changingText + str + "\n";
	}
	file.close();
	font.loadFromFile("CyrilicOld.ttf");
	mapping.setFont(font);
	mapping.setPosition(10, 0);
	mapping.setCharacterSize(sizetext);
	mapping.setFillColor(sf::Color::Green);
	view = myWindow.getView();
};

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
	if (changingText[lenghtrendergetline] != false)
	{
		myText = myText + changingText[lenghtrendergetline];
		lenghtrendergetline ++;

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
		view.move(0, -event.mouseWheelScroll.delta * 20);
		positionY -= event.mouseWheelScroll.delta * 20;
	}

	if (positionY < 0)
	{
		view.setCenter(960.f, 540.f);
		positionY = 0;
	}

	if (positionY > numberoflines * 16)
	{
		view.setCenter(windowsizeX / 2, windowsizeY / 2 + numberoflines * (sizetext - 1)  - sizetext);
		positionY = numberoflines * 16;
	}

	if (numberoflines > windowsizeY / sizetext)
	{
		view.move(0, 15 - 1);
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
