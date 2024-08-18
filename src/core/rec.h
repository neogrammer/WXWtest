#ifndef REC_H__
#define REC_H__
#include <3rdParty/olcUTIL_Geometry2D.h>
#include <SFML/Graphics/Rect.hpp>
#include <core/Cfg.h>
struct rec
{
	olc::vf2d pos;
	olc::vf2d size;
	Cfg::Textures  texType;
	olc::vi2d texRectPos;
	olc::vi2d texPosOffset;
	olc::vi2d texRectSize;
	olc::vf2d vel;

	rec();
	~rec() = default;
	rec(const rec&) = default;
	rec(rec&&) = default;
	rec& operator=(const rec&) = default;
	rec& operator=(rec&&) = default;
	void set(olc::vf2d pos_, olc::vf2d size_, Cfg::Textures texType_ = Cfg::Textures::Count, olc::vi2d texRectTilePos_ = { 0,0 }, olc::vi2d texRectSize_ = { 50,50 }, olc::vi2d texOffset_ = { 0,0 }, olc::vf2d vel_ = { 0.f,0.f });

	sf::IntRect getTexRect();

	void setTexRect(int col_, int row_);


	olc::vf2d getImagePos();


	void applyExternalForces();


	void tickPos();

};
#endif