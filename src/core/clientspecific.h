#ifndef CLIENTSPECIFIC_H__
#define CLIENTSPECIFIC_H__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <core/Cfg.h>

struct Renderable
{
	sf::Vector2f pos;
	sf::IntRect texRect;
	Cfg::Textures textureId;
	int entityId;
};

#endif