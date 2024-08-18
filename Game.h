#ifndef GAME_H__
#define GAME_H__
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <core/Cfg.h>
#include <core/globals.h>
#include <level/LayeredBackground.h>
#include <memory>
#include <core/clientspecific.h>
#include <core/interrelated.h>
#include <sstream>
#include <CidNet64.h>

class Game
{
	sf::RenderWindow gWnd;

	const int INPUT_BFR_SIZE{ 9 };
	SOCKADDR_IN ThisSenderInfo{};

	sf::Texture* playerTex{};
	std::map<std::string, std::vector<sf::IntRect> > animMap{};
	std::string currentAnim{ "idle" };
	int index{ 0 };
	sf::Sprite playerSpr{};

	sf::Texture* player2Tex{};
	std::map<std::string, std::vector<sf::IntRect> > animMap2{};
	std::string currentAnim2{ "idle" };
	int index2{ 0 };
	sf::Sprite player2Spr{};

	float gElapsed{0.f};

	int gPort{ 55555 };

	int gClientID{ 10 };

	//sf::Font gFont;

	cid::Socket connSocket;

	std::unique_ptr<LayeredBackground> bg2{};


public:
	Game();
	~Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	bool init(std::string ip_);
	void run(int client = 10);
	std::string input();
	void render();
	void update(float dt_);
	void runCheckConns();

	wchar_t* stringToWChar(const std::string& str);
	void setupAnims();

};

#endif