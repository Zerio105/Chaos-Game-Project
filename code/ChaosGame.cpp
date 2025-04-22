// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Fullscreen);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	//TO DO: CHANGE OUTPUT FROM CONSOLE TO GAME SCREEN
	cout << "Click three points on the screen to create your triangle" << endl;

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		// Draw gradient background
		Color BG1(100, 150, 180);
		Color BG2(0, 0, 0);
		const int BG_STRIP_HEIGHT = 10;

		Color ColorStep(((BG1.r - BG2.r) / (vm.height / BG_STRIP_HEIGHT)), ((BG1.g - BG2.g) / (vm.height / BG_STRIP_HEIGHT)), ((BG1.b - BG2.b) / (vm.height / BG_STRIP_HEIGHT)));

		for (int i = 0; i < vm.height / BG_STRIP_HEIGHT; i++)
		{
			RectangleShape testLine(Vector2f(vm.width, i * BG_STRIP_HEIGHT));
			testLine.setPosition(Vector2f(0, i * BG_STRIP_HEIGHT));
			testLine.setFillColor(BG1);
			window.draw(testLine);
			BG1 += ColorStep;
		}

		// Draw User-defined Points
		for(int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			rect.rotate(45);
			window.draw(rect);
		}
		
		///TODO:  Draw points


		window.display();
	}
}
