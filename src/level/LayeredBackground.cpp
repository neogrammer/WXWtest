#include <level/LayeredBackground.h>
#include <SFML/Graphics/Sprite.hpp>
#include <core/globals.h>
LayeredBackground::LayeredBackground(sf::Texture& t1, sf::Texture& t2, sf::Texture& t3, sf::Texture& t4, sf::Texture& t5, float lag1, float lag2, float lag3, float lag4, float lag5)
	: bgLayers{}
	, layerVelocityLag{}
	, xPos{}
{
	bgLayers.clear();
	layerVelocityLag.clear();
	xPos.clear();
	bgLayers.reserve(5);
	layerVelocityLag.reserve(5);
	xPos.reserve(5);
	bgLayers.push_back(&t1);
	bgLayers.push_back(&t2);
	bgLayers.push_back(&t3);
	bgLayers.push_back(&t4);
	bgLayers.push_back(&t5);
	layerVelocityLag.push_back(lag1);
	layerVelocityLag.push_back(lag2);
	layerVelocityLag.push_back(lag3);
	layerVelocityLag.push_back(lag4);
	layerVelocityLag.push_back(lag5);
	xPos.push_back(0.f);
	xPos.push_back(0.f);
	xPos.push_back(0.f);
	xPos.push_back(0.f);
	xPos.push_back(0.f);

}

LayeredBackground::~LayeredBackground()
{
}

void LayeredBackground::renderForeground(sf::RenderWindow& gWnd_)
{
	for (int i = 4; i < 5; i++)
	{
		sf::Sprite spr = sf::Sprite{};
		spr.setTexture(*bgLayers[i]);
		spr.setPosition({ xPos[i], 900.f - spr.getTexture()->getSize().y });

		gWnd_.draw(spr);
	}
}
void LayeredBackground::render(sf::RenderWindow& gWnd_)
{
	if (!parallax)
	{
		for (int i = 0; i < 4; i++)
		{
			sf::Sprite spr = sf::Sprite{};
			spr.setTexture(*bgLayers[i]);
			spr.setPosition({ xPos[i],0.f });

			gWnd_.draw(spr);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			sf::Sprite spr = sf::Sprite{};
			spr.setTexture(*bgLayers[i]);
			if (i == 0)
			{
				spr.setPosition({ xPos[i], 0.f });

			}
			else if (i == 1)
			{
				spr.setPosition({ xPos[i], 180.f });
			}
			else
			{
				spr.setPosition({ xPos[i], 900.f - spr.getTexture()->getSize().y });
			}
			gWnd_.draw(spr);
		}
	}
}

