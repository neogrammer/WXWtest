#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Vector2.hpp>

#include <core/rec.h>

#include <string>



extern sf::RenderWindow gWnd;
extern sf::ContextSettings gWndSettings;
extern sf::Vector2f mpos;
extern unsigned int gWW;
extern unsigned int gWH;
extern bool gWndFull;

extern float gTime;
extern float gPrevTime;

extern sf::View gMainView;

namespace wndw
{
	extern void CreateSFMLWindow(std::string title_, unsigned int w_, unsigned int h_);
	
}





namespace phys
{

	

	extern std::unique_ptr<sf::Sprite> spr(rec& r);


	extern bool PointVsRect(const olc::vf2d& p, const rec& r);


	extern bool RectVsRect(const rec& r1, const rec& r2);


	extern bool RayVsRect(const olc::vf2d& ray_origin, const olc::vf2d& ray_dir, const rec& target, olc::vf2d& contact_point, olc::vi2d& contact_normal, float& t_hit_near);


	extern bool DynamicRectVsRect(const rec& in, const rec& target, olc::vf2d& contact_point, olc::vi2d& contact_normal, float& contact_time, float fElapsedTime);


}
