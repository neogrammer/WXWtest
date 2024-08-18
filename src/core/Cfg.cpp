#include <core/Cfg.h>
#include <core/ResourceManager.h>
#include <core/globals.h>


ResourceManager<sf::Texture, int> Cfg::textures = {};
ResourceManager<sf::Font, int> Cfg::fonts = {};
ResourceManager<sf::Music, int> Cfg::music = {};
ResourceManager<sf::SoundBuffer, int> Cfg::sounds = {};

ActionMap<int> Cfg::playerInputs = {};

void Cfg::Initialize()
{
    initTextures();
    initFonts();
    initMusic();
    initSounds();
	initPlayerInputs();


 
}

void Cfg::initMusic()
{
    
}

void Cfg::initSounds()
{
	

}

void Cfg::initTextures()
{

	textures.load((int)Textures::BG1_1, "assets/textures/bgs/bg1/1.png");
	textures.load((int)Textures::BG1_2, "assets/textures/bgs/bg1/2.png");
	textures.load((int)Textures::BG1_3, "assets/textures/bgs/bg1/3.png");
	textures.load((int)Textures::BG1_4, "assets/textures/bgs/bg1/4.png");
	textures.load((int)Textures::PlayerSheet, "assets/textures/playerSheet2.png");
	textures.load((int)Textures::BG_Par1_1, "assets/textures/bgs/parallax1/bgLayer1.png");
	textures.load((int)Textures::BG_Par1_2, "assets/textures/bgs/parallax1/bgLayer2.png");
	textures.load((int)Textures::BG_Par1_3, "assets/textures/bgs/parallax1/bgLayer3.png");
	textures.load((int)Textures::BG_Par1_4, "assets/textures/bgs/parallax1/bgLayer4.png");
	textures.load((int)Textures::BG_Par1_5, "assets/textures/bgs/parallax1/bgLayer5.png");

}

void Cfg::initPlayerInputs()
{
	// realtime events
	// Keyboard pressed commands
	playerInputs.map(Cfg::PlayerInputs::X, Action(sf::Keyboard::Num9));
	playerInputs.map(Cfg::PlayerInputs::Y, Action(sf::Keyboard::X));
	playerInputs.map(Cfg::PlayerInputs::A, Action(sf::Keyboard::Num0));
	playerInputs.map(Cfg::PlayerInputs::B, Action(sf::Keyboard::Space));
	playerInputs.map(Cfg::PlayerInputs::L1, Action(sf::Keyboard::Num7));
	playerInputs.map(Cfg::PlayerInputs::R1, Action(sf::Keyboard::Add));
	// menu controls
	playerInputs.map(Cfg::PlayerInputs::Start, Action(sf::Keyboard::Enter));
	playerInputs.map(Cfg::PlayerInputs::Select, Action(sf::Keyboard::Backspace));
	// direction controls
	playerInputs.map(Cfg::PlayerInputs::Up, Action(sf::Keyboard::Up));
	playerInputs.map(Cfg::PlayerInputs::Down, Action(sf::Keyboard::Down));
	playerInputs.map(Cfg::PlayerInputs::Left, Action(sf::Keyboard::Left));
	playerInputs.map(Cfg::PlayerInputs::Right, Action(sf::Keyboard::Right));

	// Joystick Controls
	// Axis mappings
	playerInputs.map(Cfg::PlayerInputs::AxisX, Action(sf::Joystick::Axis::X, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::AxisY, Action(sf::Joystick::Axis::Y, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::DPadX, Action(sf::Joystick::Axis::PovX, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::DPadY, Action(sf::Joystick::Axis::PovY, Action::Type::RealTime | Action::Type::Tilted));
	// Button mappings
	playerInputs.map(Cfg::PlayerInputs::JoyA, Action(JoystickBtn::A, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyB, Action(JoystickBtn::B, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyX, Action(JoystickBtn::X, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyY, Action(JoystickBtn::Y, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyL1, Action(JoystickBtn::L1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyR1, Action(JoystickBtn::R1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyStart, Action(JoystickBtn::Start, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoySelect, Action(JoystickBtn::Select, Action::Type::RealTime | Action::Type::Pressed));

}

void Cfg::initFonts()
{
	fonts.load((int)Fonts::Font1, "assets/fonts/font1.ttf");
}