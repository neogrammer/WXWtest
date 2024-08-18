#ifndef CFG_H__
#define CFG_H__

#include <SFML/Graphics.hpp>
#include <core/ResourceManager.h>
#include <action/ActionMap.h>
#include <vector>


struct Cfg
{
	Cfg() = delete;
	Cfg(const Cfg&) = delete;
	Cfg& operator=(const Cfg&) = delete;


	//globals 
	//static sol::state lua; // globals are bad, but we'll use it for simpler implementation
	static void Initialize();

	// Resource Enums 
	enum class Textures : int { BG1_1,BG1_2, BG1_3, BG1_4, BG_Par1_1, BG_Par1_2, BG_Par1_3, BG_Par1_4, BG_Par1_5
		, PlayerSheet, Count };
	enum class Fonts : int { Font1, Count };
	enum class Music : int { Count };
	enum class Sounds : int {  Count };

	// inputs the player will be able to use
	enum PlayerInputs : int
	{
		// Keyboard mappable Keypresses
		Up, Down, Left, Right, A, X, Y, B, Start, Select, R1, L1,

		//// Joystick input, like a ps5 controller, DPad* and Axis* are handled differently than the rest of the joystick
		DPadX, DPadY, AxisX, AxisY,
		JoyA, JoyB, JoyX, JoyY, JoyR1, JoyL1, JoyStart, JoySelect
	};

	// resource buckets for each type of resource
	static ResourceManager<sf::Texture, int> textures;
	static ResourceManager<sf::Font, int> fonts;
	static ResourceManager<sf::Music, int> music;
	static ResourceManager<sf::SoundBuffer, int> sounds;

	static ActionMap<int> playerInputs;

private:
    // initalize the resources for the entire game
    static void initFonts();
    static void initMusic();
    static void initSounds();
    static void initTextures();
	static void initPlayerInputs();
};


#endif