// Draw user-defined points and eventual shape
// 
// Draw User-defined Points
for (int i = 0; i < vertices.size(); i++)
{
	RectangleShape rect(Vector2f(10, 10));
	rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
	rect.setFillColor(Color::Blue);
	rect.rotate(45);
	window.draw(rect);
}