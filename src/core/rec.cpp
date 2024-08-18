#include <core/rec.h>
#include<core/globals.h>
rec::rec()
	: pos{ 0.f,0.f }
	, size{ 0.f,0.f }
	, texType{ Cfg::Textures::Count }
	, texRectPos{ 0,0 }
	, texPosOffset{ 0,0 }
	, texRectSize{ 0,0 }
	, vel{ 0.f,0.f }
{}

void rec::set(olc::vf2d pos_, olc::vf2d size_, Cfg::Textures texType_, olc::vi2d texRectTilePos_, olc::vi2d texRectSize_, olc::vi2d texOffset_ , olc::vf2d vel_ )
{
	pos = pos_;
	size = size_;
	texType = texType_;
	texRectPos = { texRectTilePos_.x * texRectSize_.x, texRectTilePos_.y * texRectSize_.y };
	texPosOffset = texOffset_;
	texRectSize = texRectSize_;

	vel = vel_;
}
sf::IntRect rec::getTexRect()
{
	return { {texRectPos.x,texRectPos.y},{texRectSize.x,texRectSize.y} };
};

void rec::setTexRect(int col_, int row_)
{
	texRectPos = { col_ * texRectSize.x, row_ * texRectSize.y };
};

olc::vf2d rec::getImagePos()
{
	return { pos.x - texPosOffset.x, pos.y - texPosOffset.y };
};

void rec::applyExternalForces()
{

}

void rec::tickPos()
{
	pos += vel * gTime;
};