// Construct a gradient background
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