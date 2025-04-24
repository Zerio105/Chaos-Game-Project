// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

// >> DrawLine - Draws a simple thin line between two vector points.
// >> Arguments are the window to render to, followed by the start and end points.
void DrawLine(RenderWindow& inWindow, Vector2f point1, Vector2f point2)
{
	// >> Creates array of the two points
	sf::Vertex line[] =
	{
		sf::Vertex(point1),
		sf::Vertex(point2)
	};
	// >> Draws the line between them
	inWindow.draw(line, 2, sf::Lines);
}

		// >> !! UNFINISHED !! Has issues with determining which angle to rotate the shape to

// >> ConfigureLine - Creates a "line" RectangleShape between two points returns the object.
// >> Arguments are its start and end point as a Vector2f, as well as optional variables for color and line thickness
RectangleShape ConfigureLine(Vector2f point1, Vector2f point2, Color lineColor = Color::White, float lineThickness = 5.0)
{
	// >> Calculates distance and slope; error likely lies within the slope formula
	float distance = sqrt(pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2));
	float slope = ((point2.y - point1.y) / (point2.x - point1.x)) * 45.0;
	// >> Creates new rectangle of appropriate distance and thickness
	RectangleShape outShape(Vector2f(distance, lineThickness));
	// >> Moves rectangle to the appropriate location, colors it, and rotates it according to the slope
	outShape.setPosition(Vector2f(point1.x, point1.y));
	outShape.setFillColor(lineColor);
	outShape.rotate(slope);
	// >> Returns shape to be rendered or assigned to another variable
	return outShape;
}

int main()
{
	// Create a video mode object (>>original default is 1920 x 1080)
	VideoMode vm(960, 540);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	//TO DO: CHANGE OUTPUT FROM CONSOLE TO GAME SCREEN
	cout << "Click three points on the screen to create your triangle" << endl;

	//FOR VERIFYING FOURTH CLICK MESSAGE
	bool fourthClick = false;

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
			//THIS CHECKS IF TRIANGLE IS FORMED. IF YES, IT ASKS FOR STARTING POINT.
			if (!fourthClick && vertices.size() >= 3)
			{
				//TODO: CHANGE OUTPUT FROM CONSOLE TO GAME SCREEN
				cout << "Click a fourth point to begin the sequence" << endl;
				fourthClick = true;
			}

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

					// >> If there are not enough vertices to form a triangle, add the clicked area to the shape
					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}

					// >> Otherwise, if there are no points for the Chaos Algorithm, add the first one at the clicked area
					else if (points.size() == 0)
					{
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
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

		if (points.size() > 0)
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

		// >> Construct a gradient background
		// >> (Note to maybe find a way to optimize this once the rest of the project works; probably isn't best to make this all calculate every frame whoops)

		// >> Define start and end colors and height of each strip of color
		Color BG1(100, 150, 180);
		Color BG2(0, 0, 0);
		const int BG_STRIP_HEIGHT = 20;

		// >> Calculate the amount each color should change per "step"
		Color ColorStep(((BG1.r - BG2.r) / (vm.height / BG_STRIP_HEIGHT)), ((BG1.g - BG2.g) / (vm.height / BG_STRIP_HEIGHT)), ((BG1.b - BG2.b) / (vm.height / BG_STRIP_HEIGHT)));

		// >> Create and display each step of the background, iterate the color through each time
		for (int i = 0; i < vm.height / (BG_STRIP_HEIGHT); i++)
		{
			RectangleShape testLine(Vector2f(vm.width, i * BG_STRIP_HEIGHT));
			testLine.setPosition(Vector2f(0, (i - 1) * BG_STRIP_HEIGHT));
			testLine.setFillColor(BG1);
			window.draw(testLine);
			BG1 += ColorStep;
		}

		// >> Draw user-defined points
		// >> Check if there are at least three points present, to determine if shape or vertices are rendered
		// >> (If squares and larger shapes are included, change the way this is checked)
		if (vertices.size() < 3)
		{
			// >> Display each vertex as its own point
			for (int i = 0; i < vertices.size(); i++)
			{
				// >> Create a RectangleShape, move it to the correct position, color it, and rotate it 45 degrees to become a diamond shape
				RectangleShape rect(Vector2f(10, 10));
				rect.setPosition(Vector2f(vertices[i].x, vertices[i].y - 5));
				rect.setFillColor(Color::Blue);
				rect.rotate(45);
				// >> Draw the created shape to the screen
				window.draw(rect);
			}
		}
		// >> If not in "individual vertices" mode, draw the triangle itself
		else
		{
			// >> Display a line between each vertex
			for (int i = 0; i < vertices.size(); i++)
			{
				// >> Use DrawLine function to draw a line between each vertex. If on the final vertex, draw it to the first one.
				DrawLine(window, vertices[i], (i == vertices.size() - 1 ? vertices[0] : vertices[i + 1]));

					// >> Following code is temporarily commented out, as it uses the faulty "thick line" function. If that can be fixed, switch back to this method.
				//RectangleShape line = ConfigureLine(vertices[i], vertices[i + 1]);
				//window.draw(line);
			}
		}

		// >> Draw all existing points for Chaos Algorithm
		for (int i = 0; i < points.size(); i++)
		{
			// >> Create a RectangleShape, move it to the correct position, color it, and rotate it 45 degrees to become a diamond shape
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(Vector2f(points[i].x, points[i].y - 2.5));
			rect.setFillColor(Color::White);
			rect.rotate(45);
			// >> Draw the created shape to the screen
			window.draw(rect);
		}

		///TODO:  Draw points
		window.display();
	}
}
