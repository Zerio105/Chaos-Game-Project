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

	//MOVE THIS
	//TO DO: CHANGE OUTPUT FROM CONSOLE TO GAME SCREEN
	cout << "Click three points on the screen to create your triangle" << endl;
	//FOR VERIFYING FOURTH CLICK MESSAGE
	bool fourthClick = false;

	}
	while (window.isOpen())
	{
		//MOVE THIS
		//THIS CHECKS IF TRIANGLE IS FORMED. IF YES, IT ASKS FOR STARTING POINT.
		if (!fourthClick && vertices.size() >= 3) {
			//TODO: CHANGE OUTPUT FROM CONSOLE TO GAME SCREEN
			cout << "Click a fourth point to begin the sequence" << endl;
			fourthClick = true;
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			// TEMPORARY MODULE - MOUSE CLICK EVENTS			
			#include "ClickEvents.cpp"
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
	
		// TEMPORARY MODULE - GENERATE NEW CHAOS GAME POINTS		
		#include "GenerateChaosPoints.cpp"
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		// TEMPORARY MODULE - GRADIENT BACKGROUND
		#include "GradientBackground.cpp"

		// TEMPORARY MODULE - TEXT PROMPTS
		#include "TextPrompts.cpp"

		// TEMPORARY MODULE - DRAW USER SHAPE / CLICKED VERTICES		
		#include "DrawUserShape.cpp"
		
		// TEMPORARY MODULE - DRAW CHAOS POINTS
		#include "DrawChaosPoints.cpp"


		window.display();
	}
}
