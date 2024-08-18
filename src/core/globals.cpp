#include <core/globals.h>
#include <SFML/Graphics/Sprite.hpp>
#include <core/Cfg.h>


sf::RenderWindow gWnd = {};
sf::ContextSettings gWndSettings = { sf::ContextSettings{} };
unsigned int gWW = {};
unsigned int gWH = {};
sf::Vector2f mpos = {};
bool gWndFull = false;

sf::View gameView = {};
sf::Sound dieSound = {};

float gTime = 0.f;
float gPrevTime = 0.f;

void wndw::CreateSFMLWindow(std::string title_, unsigned int w_, unsigned int h_)
{
	gWW = w_;
	gWH = h_;
	gWndSettings.antialiasingLevel = 8;
	if (gWndFull == true)
		gWnd.create({ gWW,gWH,32U }, title_, sf::Style::Fullscreen, gWndSettings);
	else if (gWndFull == false)
		gWnd.create({ gWW,gWH,32U }, title_, sf::Style::Close, gWndSettings);
	gameView = gWnd.getDefaultView();
}



std::unique_ptr<sf::Sprite> phys::spr(rec& r)
{
	std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
	if (r.texType != Cfg::Textures::Count)
	{
		sprite->setTexture(Cfg::textures.get((int)r.texType));
		sprite->setTextureRect({ {r.texRectPos.x, r.texRectPos.y},{r.texRectSize.x,r.texRectSize.y} });
	}
	sprite->setPosition({r.getImagePos().x , r.getImagePos().y });
	return std::move(sprite);
}



bool phys::PointVsRect(const olc::vf2d& p, const rec& r)
{
	return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}

bool phys::RectVsRect(const rec& r1, const rec& r2)
{
	return (r1.pos.x < r2.pos.x + r2.size.x && r1.pos.x + r1.size.x > r2.pos.x && r1.pos.y < r2.pos.y + r2.size.y && r1.pos.y + r1.size.y > r2.pos.y);
}

bool phys::RayVsRect(const olc::vf2d& ray_origin, const olc::vf2d& ray_dir, const rec& target, olc::vf2d& contact_point, olc::vi2d& contact_normal, float& t_hit_near)
{
	olc::vf2d t_near = (target.pos - ray_origin) / ray_dir;
	olc::vf2d t_far = (target.pos + target.size - ray_origin) / ray_dir;
	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;
	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;
	t_hit_near = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);
	if (t_hit_far < 0) return false;
	contact_point = ray_origin + t_hit_near * ray_dir;
	if (t_near.x > t_near.y)
	{
		if (ray_dir.x < 0)
		{
			contact_normal = { 1, 0 };
		}
		else
		{
			contact_normal = { -1, 0 };
		}
	}
	else if (t_near.x < t_near.y)
	{
		if (ray_dir.y < 0)
		{
			contact_normal = { 0, 1 };
		}
		else
		{
			contact_normal = { 0, -1 };
		}
	}
	return true;
}

bool phys::DynamicRectVsRect(const rec& in, const rec& target, olc::vf2d& contact_point, olc::vi2d& contact_normal, float& contact_time, float fElapsedTime)
{
	if (in.vel.x == 0 && in.vel.y == 0)
	{
		return false;
	}
	rec expanded_target;
	expanded_target.pos = target.pos - in.size / 2.f;
	expanded_target.size = target.size + in.size;
	if (RayVsRect(in.pos + in.size / 2.f, in.vel * fElapsedTime, expanded_target, contact_point, contact_normal, contact_time))
	{
		if (contact_time <= 1.0f && contact_time >= 0.f)
			return true;
	}
	return false;
}

