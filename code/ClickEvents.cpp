// Behavior for left and right clicks
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

		if (vertices.size() < 3)
		{
			vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
		}
		else if (points.size() == 0)
		{
			///fourth click
			///push back to points vector
		}
	}
}