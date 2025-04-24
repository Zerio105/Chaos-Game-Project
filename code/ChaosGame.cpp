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

// >> InitializeBackground - Stores individual Color values into a vector to easily be accessed when drawing the gradient background
// >> Arguments are a vector of colors to function as a container, the height of each background strip, and the current VideoMode object to reference height
void InitializeBackground(vector<Color>& gradientContainer, int stripHeight, VideoMode& inMode)
{
	// >> Define start and end colors
	Color BG1(100, 150, 180);
	Color BG2(0, 0, 0);
	// >> Calculate the amount each color should change per "step"
	Color ColorStep(((BG1.r - BG2.r) / (inMode.height / stripHeight)), ((BG1.g - BG2.g) / (inMode.height / stripHeight)), ((BG1.b - BG2.b) / (inMode.height / stripHeight)));
	// >> Add each iterated color to the container, then iterate it further
	for (int i = 0; i < inMode.height / (stripHeight); i++)
	{
		gradientContainer.push_back(BG1);
		BG1 += ColorStep;
	}
}

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

	vector<RectangleShape> visualVertices;
	vector<RectangleShape> visualPoints;

	// >> Initialize background gradient information
	const int BG_STRIP_HEIGHT = 20;
	vector<Color> gradient;
	InitializeBackground(gradient, BG_STRIP_HEIGHT, vm);

	// >> Load font: Berlin Sans FB Demi
	Font berlinSans;
	if (!berlinSans.loadFromFile("BRLNSDB.TTF"))
	{
		cout << "Error: Font cannot be loaded" << endl;
	}

	// >> Define starter user prompt and text style
	Text userPrompt;
	userPrompt.setFont(berlinSans);
	userPrompt.setString("Click on any three points to define a triangle.");
	userPrompt.setCharacterSize(24);
	userPrompt.setFillColor(Color::White);
	userPrompt.setStyle(Text::Bold);
	userPrompt.setPosition(10, 10);

	// >> For verifying fourth click message
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
			// >> Checks if triangle is formed, If yes, it asks for starting point.
			if (!fourthClick && vertices.size() >= 3)
			{
				// >> Changes prompt text
				userPrompt.setString("Click on a fourth point to begin the Chaos Algorithm.");
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
						RectangleShape nextVertex(Vector2f(10, 10));
						nextVertex.setOrigin(5, 5);
						nextVertex.setPosition(Vector2f(event.mouseButton.x, event.mouseButton.y));
						nextVertex.setFillColor(Color::Blue);
						nextVertex.rotate(45.0);
						visualVertices.push_back(nextVertex);
					}

					// >> Otherwise, if there are no points for the Chaos Algorithm, add the first one at the clicked area
					else if (points.size() == 0)
					{
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));

						RectangleShape nextPoint(Vector2f(2, 2));
						nextPoint.setPosition(event.mouseButton.x, event.mouseButton.y);
						nextPoint.setFillColor(Color::White);
						nextPoint.rotate(45.0);
						visualPoints.push_back(nextPoint);

						userPrompt.setString("Chaos Algorithm in progress...");
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

		// >> Display the gradient background
		int bgHeight = 0;
		for (Color currColor : gradient)
		{
			RectangleShape testLine(Vector2f(vm.width, bgHeight * BG_STRIP_HEIGHT));
			testLine.setPosition(Vector2f(0, (bgHeight - 1) * BG_STRIP_HEIGHT));
			testLine.setFillColor(currColor);
			window.draw(testLine);
			bgHeight++;
		}

		// >> Display text to prompt the user
		window.draw(userPrompt);

		// >> Draw user-defined points
		// >> Check if there are at least three points present, to determine if shape or vertices are rendered
		// >> (If squares and larger shapes are included, change the way this is checked)
		if (vertices.size() < 3)
		{
			// >> Display each vertex as its own point
			for (int i = 0; i < vertices.size(); i++)
			{
				// >> Create a RectangleShape, move it to the correct position, color it, and rotate it 45 degrees to become a diamond shape
				visualVertices[i].rotate(1);
				// >> Draw the created shape to the screen
				window.draw(visualVertices[i]);
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
			window.draw(visualPoints[i]);
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(Vector2f(points[i].x, points[i].y - 2.5));
			rect.setFillColor(Color::White);
			rect.rotate(45);
			// >> Draw the created shape to the screen
			window.draw(rect);
		}

		// >> Generate new Chaos Algorithm points
		if (points.size() != 0 && vertices.size() >= 3)
		{
			// >> Gets location of previous point and then chooses a corner at random.
			int prevPoint = points.size() - 1;
			int chosenCorner = rand() % 3;
			// >> Pushes back a new vector2f into points at the midpoint between points[prevPoint] and vertices[chosenCorner]
			Vector2f currentVector((vertices.at(chosenCorner).x + points.at(prevPoint).x) / 2, (vertices.at(chosenCorner).y + points.at(prevPoint).y) / 2);
			points.push_back(currentVector);

			RectangleShape nextPoint(Vector2f(2, 2));
			nextPoint.setPosition(currentVector);
			nextPoint.setFillColor(Color::White);
			nextPoint.rotate(45.0);
			visualPoints.push_back(nextPoint);
		}
		window.display();
	}
}
