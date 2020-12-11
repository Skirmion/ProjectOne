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
	string changingText = "";
	ifstream file;
	string myText;
	sf::RenderWindow myWindow;
	sf::Text mapping;
	sf::Font font;
	int lenghtrendergetline = 0;
	sf::View view;
	int numberoflines = 1;
	int buflines = 1;
	int positionY = 0;
	sf::Event event;
};

Hacker::Hacker() : myWindow(sf::VideoMode(1920, 1080), "Hack")
{
	file.open("text.txt");
	font.loadFromFile("CyrilicOld.ttf");
	mapping.setFont(font);
	mapping.setPosition(10, 0);
	mapping.setCharacterSize(16);
	sf::Color fillColor = sf::Color(0, 0, 0);
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
	if (lenghtrendergetline < 0)
	{
		getline(file, changingText);
		lenghtrendergetline += 1;
	}

	if (changingText.length() != 0)
	{
		myText = myText + changingText[lenghtrendergetline];
		lenghtrendergetline ++;
	}

	if (lenghtrendergetline >= changingText.length())
	{
		myText = myText + "\n";
		lenghtrendergetline = -1;
		buflines ++;
		numberoflines ++;
	}

	if (buflines > 1080 / 16)
	{
		view.move(0, 15);
		positionY += 15;
		buflines -= 1;
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
		view.setCenter(960.f, 540.f + numberoflines * 15 - 16);
		positionY = numberoflines * 16;
	}

	if (buflines > 1080 / 16)
	{
			view.move(0, 15);
			positionY += 15;
			buflines -= 1;
	}
}


int main()
{
	Hacker hacker;
	hacker.run();
	return 0;
}
