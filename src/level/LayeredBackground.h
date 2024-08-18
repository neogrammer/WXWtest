#ifndef LAYEREDBACKGROUND_H__
#define LAYEREDBACKGROUND_H__

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class LayeredBackground
{
	bool parallax{ true };
	std::vector<sf::Texture*> bgLayers{};
	std::vector<float> layerVelocityLag{};
	std::vector<float> xPos{};
public:
	LayeredBackground() = default;
	LayeredBackground(sf::Texture& t1, sf::Texture& t2, sf::Texture& t3, sf::Texture& t4, sf::Texture& t5, float lag1, float lag2, float lag3, float lag4, float lag5);
	~LayeredBackground();
	LayeredBackground(const LayeredBackground&) = delete;
	LayeredBackground& operator=(const LayeredBackground&) = delete;
	LayeredBackground(LayeredBackground&&) = delete;
	LayeredBackground& operator=(LayeredBackground&&) = delete;

	void renderForeground(sf::RenderWindow& gWnd_);
	
	void render(sf::RenderWindow& gWnd_);

};
#endif