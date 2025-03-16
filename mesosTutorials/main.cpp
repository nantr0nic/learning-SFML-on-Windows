#include <iostream>
#include <SFML/Graphics.hpp>

sf::Color HSVtoRGB(float h, float s, float v)
{
	float hPrime = h / 60.0f;
	unsigned int hIndex = unsigned int(hPrime) & 6;

	float chroma = s * v;
	float min = (v - chroma);
	float x = chroma * (1.0f - abs(fmod(hPrime, 2.0f) - 1.0f));

	float outRGB[6][3] = {
		{chroma, x, 0.0f},
		{x, chroma, 0.0f},
		{0.0f, chroma, x},
		{0.0f, x, chroma},
		{x, 0.0f, chroma},
		{chroma, 0.0f, x}
	};

	float rF = (outRGB[hIndex][0] + min);
	float gF = (outRGB[hIndex][1] + min);
	float bF = (outRGB[hIndex][2] + min);

	rF *= 255.0f;
	gF *= 255.0f;
	bF *= 255.0f;

	std::uint8_t rI = std::uint8_t(rF);
	std::uint8_t gI = std::uint8_t(gF);
	std::uint8_t bI = std::uint8_t(bF);

	return sf::Color(rI, gI, bI);

}

int main()
{
	unsigned int width = 640;
	unsigned int height = 360;

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "SFML");
	window->setFramerateLimit(60);

	int n = 128;

	sf::VertexArray lines;
	lines.setPrimitiveType(sf::PrimitiveType::Lines);
	lines.resize(n);

	for (int i = 0; i < n; ++i)
	{
		sf::Vector2f pos = { float(i * cos(i)), float(i * sin(i)) };
		float hue = i * (360.0f / n);

		lines[i].position = pos;
		lines[i].position += {width / 4.0f, height / 4.0f};
		lines[i].color = HSVtoRGB(hue, 1.0f, 1.0f);
	}

	while (window->isOpen())
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is < sf::Event::Closed>())
			{
				window->close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				{
					window->close();
				}
			}
		}

		// Render

		window->clear();

		// Drawing
		window->draw(lines);

		window->display();
	}

	delete window;

	return 0;
}