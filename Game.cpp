#include "Game.h"

Game::Game()
	: connSocket{ cid::IPVersion::IPv4, INVALID_SOCKET }
	, frames{}
	, animFrameRanges{}
	, frameIndex{ 0 }
{
	frames.clear();
	frames.reserve(114);
	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (y * 11 + x >= 114)
				break;

			frames.emplace_back(sf::IntRect{ {x * 96, y * 96},{96, 96} });
		}
	}

	animFrameRanges.emplace(std::pair{ PlayerAnimType::Idle, std::pair{0, 8} });
	animFrameRanges.emplace(std::pair{ PlayerAnimType::Run, std::pair{15, 22} });
	animFrameRanges.emplace(std::pair{ PlayerAnimType::Attack, std::pair{57, 61} });
	animFrameRanges.emplace(std::pair{ PlayerAnimType::Hit, std::pair{23, 33} });
	animFrameRanges.emplace(std::pair{ PlayerAnimType::Jump, std::pair{44, 56} });


}

Game::~Game()
{
}

bool Game::init(std::string ip_)
{
	// connect to ip (the server host)

	std::string result = ip_;
	
	wchar_t* wstr = stringToWChar(result);

	if (!cid::net::initialize())
	{
		return false;
	}
	else
	{
		std::cout << "Success on initialization of winsock!" << std::endl;
	}


	// set up the socket configuration
	
	{
		auto result = connSocket.Create();
		if (result != cid::CResult::C_Success)
		{
			std::cout << "Error at socket creation for main connection listener, exiting game" << std::endl;
			cid::net::shutdown();
			return false;
		}
		else
		{
			std::cout << "socket connector created" << std::endl;
		}
	}


	if (connSocket.Connect(cid::IPEndpoint(result.c_str(), 55555)) == cid::CResult::C_Success)
	{
		std::cout << "connected to server" << std::endl;
	}
	else
	{
		std::cout << "unable to connect to server" << std::endl;
		connSocket.Close();
		cid::net::shutdown();
		return false;
	}


	return true;
}

void Game::run(int client)
{




		Cfg::Initialize();
		setupAnims();

		bg2 = std::make_unique<LayeredBackground>(Cfg::textures.get((int)Cfg::Textures::BG_Par1_1), Cfg::textures.get((int)Cfg::Textures::BG_Par1_2), Cfg::textures.get((int)Cfg::Textures::BG_Par1_3), Cfg::textures.get((int)Cfg::Textures::BG_Par1_4), Cfg::textures.get((int)Cfg::Textures::BG_Par1_5), .25f, .5f, .75f, 1.f, 1.f);

		gWnd.create({ 1600U,900U,32U }, "GameWindow", sf::Style::None);
		gWnd.setPosition({ 150,50 });



		std::cout << "receiving client id  from server" << std::endl;

		{
			char buffer[2];
			cid::CResult result = cid::CResult::C_Success;
			result = connSocket.RecvAll(buffer, 2);
			if (result != cid::CResult::C_Success)
			{
				connSocket.Close();
				cid::net::shutdown();
				gWnd.close();
				return;
			}
			std::cout << "received clientID from server" << buffer << std::endl;
			gClientID = atoi(buffer);
		}
		//int numBytes = 2;
		//int totalReceived = 0;
		//while (totalReceived < numBytes)
		//{
		//	int bytesRemaining = numBytes - totalReceived;
		//	int bytesReceived = 0;
		//	char* bufferOffset = (char*)buffer + totalReceived;

		//	bytesReceived = recv(connSocket.GetHandle(), bufferOffset, bytesRemaining, NULL);
		//	if (bytesReceived == 0)
		//	{
		//		connSocket.Close();
		//		cid::net::shutdown();
		//		wnd.close();
		//		return;
		//	}
		//	if (bytesReceived == SOCKET_ERROR)
		//	{
		//		int error = WSAGetLastError();
		//		connSocket.Close();
		//		cid::net::shutdown();
		//		wnd.close();
		//		return;
		//	}

		//	//CResult result = Recv(bufferOffset, bytesRemaining, bytesReceived);
		//	if (result != cid::CResult::C_Success)
		//	{
		//		connSocket.Close();
		//		cid::net::shutdown();
		//		wnd.close();
		//		return;
		//	}
		//	totalReceived += bytesReceived;
		//}



		startover:
		if (gClientID == 1)
		{
			sf::Text waitText;
			waitText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
			waitText.setPosition({ 700.f,350.f });
			waitText.setCharacterSize(44U);
			waitText.setFillColor(sf::Color::White);
			waitText.setString("waiting on other player...");


			if (gWnd.isOpen())
			{
				gWnd.clear(sf::Color::Blue);
				gWnd.draw(waitText);
				gWnd.display();
			}

			std::cout << "waiting to be told to go" << std::endl;
			if (gClientID == 1)
			{
				char bufferGo[2];
				cid::CResult result = cid::CResult::C_Success;
				result = connSocket.RecvAll(bufferGo, 2);
				if (result != cid::CResult::C_Success)
				{
					connSocket.Close();
					cid::net::shutdown();
					gWnd.close();
					return;
				}
				bufferGo[1] = '\0';
				if (bufferGo[0] != 'y')
				{
					connSocket.Close();
					cid::net::shutdown();
					gWnd.close();
					return;
				}
			}
			std::cout << "client 1 told to go, beginning game" << std::endl;

		}

	sf::Clock frameTimer{};
	float gElapsed{ 0 };
	bool aborted = false;
	while (gWnd.isOpen())
	{
		abort:
		if (aborted)
		{
			sf::Text waitText;
			waitText.setFont(Cfg::fonts.get((int)Cfg::Fonts::Font1));
			waitText.setPosition({ 700.f,350.f });
			waitText.setCharacterSize(44U);
			waitText.setFillColor(sf::Color::White);
			waitText.setString("waiting on other player...");


			if (gWnd.isOpen())
			{
				gWnd.clear(sf::Color::Blue);
				gWnd.draw(waitText);
				gWnd.display();
			}

			std::cout << "waiting to be told to go" << std::endl;
			char bufferGo[2];
			cid::CResult result = cid::CResult::C_Success;
			result = connSocket.RecvAll(bufferGo, 2);
			if (result != cid::CResult::C_Success)
			{
				connSocket.Close();
				cid::net::shutdown();
				gWnd.close();
				return;
			}
			bufferGo[1] = '\0';
			if (bufferGo[0] != 'y')
			{
				connSocket.Close();
				cid::net::shutdown();
				gWnd.close();
				return;
			}
			std::cout << "client 1 told to go, beginning game" << std::endl;
			aborted = false;
		}


		std::string tmp = input();
		char mystr[9];
		tmp.copy(mystr, 8);
		mystr[8] = '\0';

		char sendbuf[9];
		strcpy_s(sendbuf, mystr);



		std::cout << "about to send to server the input data" << std::endl;

		{
			cid::CResult result = cid::CResult::C_Success;

			result = connSocket.SendAll(sendbuf, 9);
			if (result != cid::CResult::C_Success)
			{
				if (result == cid::CResult::C_NotYetImplemented)
				{
					aborted = true;
					goto abort;
				} 

				if (connSocket.GetHandle() != INVALID_SOCKET)
				{
					goto startover;
				}
				else
				{
					connSocket.Close();
					cid::net::shutdown();
					gWnd.close();
					return;
				}
			}
			std::cout << "Attempting to send chunk of data..." << std::endl;

		}
		std::cout << "sent to server the input data" << std::endl;

		std::cout << "waiting to receive world data from server" << std::endl;

		{

			char recvbuff[17];
			cid::CResult result = cid::CResult::C_Success;

			result = connSocket.RecvAll(recvbuff, 17);
			if (result != cid::CResult::C_Success)
			{
				if (result == cid::CResult::C_NotYetImplemented)
				{
					aborted = true;
					goto abort;
				}

				if (connSocket.GetHandle() != INVALID_SOCKET)
				{
					goto startover;
				}
				else
				{
					connSocket.Close();
					cid::net::shutdown();
					gWnd.close();
					return;
				}
			}

			recvbuff[16] = '\0';



			std::cout << "Got message from server: " << recvbuff << std::endl;

			std::string p1X{ "0000" }, p1Y{ "000" }, p2X{ "0000" }, p2Y{ "000" };
			for (int i = 0; i < 4; i++)
			{
				p1X[i] = recvbuff[i];
			}
			for (int i = 0; i < 3; i++)
			{
				p1Y[i] = recvbuff[i + 4];
			}
			for (int i = 0; i < 4; i++)
			{
				p2X[i] = recvbuff[i + 7];
			}
			for (int i = 0; i < 3; i++)
			{
				p2Y[i] = recvbuff[i + 11];
			}

			if (gClientID == 1)
			{
				char tmp[2] = { recvbuff[14], '\0' };
				int currentAnimInt1 = atoi(tmp);
				if ((PlayerAnimType)currentAnimInt1 == PlayerAnimType::Idle)
				{
					if (currentAnim != "idle")
					{
						currentAnim = "idle";
						playerSpr.setTextureRect(animMap[currentAnim].at(0));
					}
				}
				else if ((PlayerAnimType)currentAnimInt1 == PlayerAnimType::Run)
				{
					if (currentAnim != "run")
					{
						currentAnim = "run";
						playerSpr.setTextureRect(animMap[currentAnim].at(0));
					}
				}

				char tmp2[2] = { recvbuff[15], '\0' };
				int currentAnimInt2 = atoi(tmp2);
				if ((PlayerAnimType)currentAnimInt2 == PlayerAnimType::Idle)
				{
					if (currentAnim2 != "idle")
					{
						currentAnim2 = "idle";
						player2Spr.setTextureRect(animMap2[currentAnim2].at(0));
					}
				}
				else if ((PlayerAnimType)currentAnimInt2 == PlayerAnimType::Run)
				{
					if (currentAnim2 != "run")
					{
						currentAnim2 = "run";
						player2Spr.setTextureRect(animMap2[currentAnim2].at(0));
					}
				}
		/*		if (stoi(p1X) - playerSpr.getPosition().x > 0.f)
				{
					if (currentAnim != "idle2")
					{
						currentAnim = "idle2";
						playerSpr.setTextureRect(animMap[currentAnim].at(0));
					}
				}
				else if (stoi(p1X) - playerSpr.getPosition().x < 0.f)
				{
					currentAnim = "idle3";
					playerSpr.setTextureRect(animMap[currentAnim].at(0));

				}
				else
				{
					currentAnim = "idle";
					playerSpr.setTextureRect(animMap[currentAnim].at(0));

				}

				if (stoi(p2X) - player2Spr.getPosition().x > 0.f)
				{
					currentAnim2 = "idle2";
					player2Spr.setTextureRect(animMap2[currentAnim2].at(0));

				}
				else if (stoi(p2X) - player2Spr.getPosition().x < 0.f)
				{
					currentAnim2 = "idle3";
					player2Spr.setTextureRect(animMap2[currentAnim2].at(0));

				}
				else
				{
					currentAnim2 = "idle";
					player2Spr.setTextureRect(animMap2[currentAnim2].at(0));

				}*/
				animType = (PlayerAnimType)currentAnimInt1;
				animType2 = (PlayerAnimType)currentAnimInt2;
				playerSpr.setPosition({ (float)stoi(p1X), (float)stoi(p1Y) });
				player2Spr.setPosition({ (float)stoi(p2X), (float)stoi(p2Y) });

			}
			else
			{
				char tmp[2] = { recvbuff[14], '\0' };
				int currentAnimInt1 = atoi(tmp);
				if ((PlayerAnimType)currentAnimInt1 == PlayerAnimType::Idle)
				{
					if (currentAnim2 != "idle")
					{
						currentAnim2 = "idle";
						player2Spr.setTextureRect(animMap2[currentAnim2].at(0));
					}
				}
				else if ((PlayerAnimType)currentAnimInt1 == PlayerAnimType::Run)
				{
					if (currentAnim2 != "run")
					{
						currentAnim2 = "run";
						player2Spr.setTextureRect(animMap2[currentAnim2].at(0));
					}
				}

				char tmp2[2] = { recvbuff[15], '\0' };
				int currentAnimInt2 = atoi(tmp2);
				if ((PlayerAnimType)currentAnimInt2 == PlayerAnimType::Idle)
				{
					if (currentAnim != "idle")
					{
						currentAnim = "idle";
						playerSpr.setTextureRect(animMap[currentAnim].at(0));
					}
				}
				else if ((PlayerAnimType)currentAnimInt2 == PlayerAnimType::Run)
				{
					if (currentAnim != "run")
					{
						currentAnim = "run";
						playerSpr.setTextureRect(animMap[currentAnim].at(0));
					}
				}
				/*if (stoi(p2X) - playerSpr.getPosition().x > 0.f)
				{
					if (currentAnim != "idle2")
					{
						currentAnim = "idle2";
						playerSpr.setTextureRect(animMap[currentAnim].at(0));
					}
				}
				else if (stoi(p2X) - playerSpr.getPosition().x < 0.f)
				{
					currentAnim = "idle3";
					playerSpr.setTextureRect(animMap[currentAnim].at(0));

				}
				else
				{
					currentAnim = "idle";
					playerSpr.setTextureRect(animMap[currentAnim].at(0));

				}

				if (stoi(p1X) - player2Spr.getPosition().x > 0.f)
				{
					currentAnim2 = "idle2";
					player2Spr.setTextureRect(animMap2[currentAnim2].at(0));

				}
				else if (stoi(p1X) - player2Spr.getPosition().x < 0.f)
				{
					currentAnim2 = "idle3";
					player2Spr.setTextureRect(animMap2[currentAnim2].at(0));

				}
				else
				{
					currentAnim2 = "idle";
					player2Spr.setTextureRect(animMap2[currentAnim2].at(0));

				}*/
				animType = (PlayerAnimType)currentAnimInt2;
				animType2 = (PlayerAnimType)currentAnimInt1;
				playerSpr.setPosition({ (float)stoi(p2X), (float)stoi(p2Y) });
				player2Spr.setPosition({ (float)stoi(p1X), (float)stoi(p1Y) });
			}
		}
		std::cout << "received world data from the server" << std::endl;
		
		animElapsed1 += frameTimer.restart().asSeconds();

		if (animElapsed1 >= animDelay)
		{
			animElapsed1 = 0.f;

			++index;
			++index2;
			int topBoundP1 = animFrameRanges.at(animType).second;
			int bottomBoundP1 = animFrameRanges.at(animType).first;
			if (index < bottomBoundP1)
			{
				index = bottomBoundP1;
			}
			else if (index > topBoundP1)
			{
				index = bottomBoundP1;
			}
			int topBoundP2 = animFrameRanges.at(animType2).second;
			int bottomBoundP2 = animFrameRanges.at(animType2).first;
			if (index2 < bottomBoundP2)
			{
				index2 = bottomBoundP2;
			}
			else if (index2 > topBoundP2)
			{
				index2 = bottomBoundP2;
			}
			playerSpr.setTextureRect(frames[index]);
			player2Spr.setTextureRect(frames[index2]);
		}

		sf::Event e;
		while (gWnd.pollEvent(e))
		{
			if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape)
			{
				gWnd.close();
			}
		}
		if (gWnd.isOpen())
		{

			std::string clientInputString = input();

			gElapsed = frameTimer.restart().asSeconds();
			update(gElapsed);

			gWnd.clear(sf::Color::Blue);
			render();
			gWnd.display();

		}
	}


	//close any open sockets
	if (connSocket.GetHandle() != INVALID_SOCKET)
	{
		cid::CResult result = connSocket.Close();
		if (result != cid::CResult::C_Success)
		{
			std::cout << "Trouble with closing the socket with the server" << std::endl;
			cid::net::shutdown();
			return;
		}
	}

	cid::net::shutdown();
	return;
}



void Game::update(float dt_)
{
}

void Game::runCheckConns()
{
	if (connSocket.GetHandle() != INVALID_SOCKET)
	{
		run(gClientID);
		return;
	}
	else
	{
		return;
	}
}


std::string Game::input()
{
	std::string s = "00000000";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		s[0] = '1';
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		s[1] = '1';
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		s[2] = '1';
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		s[3] = '1';
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		s[4] = '1';
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		s[5] = '1';
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		s[6] = '1';
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		s[7] = '0';
	}
	return s;
}




void Game::render()
{
	bg2->render(gWnd);

	gWnd.draw(playerSpr);
	gWnd.draw(player2Spr);

	bg2->renderForeground(gWnd);


}

wchar_t* Game::stringToWChar(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
	wchar_t* wstr = new wchar_t[size_needed + 1];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), wstr, size_needed);
	wstr[size_needed] = L'\0'; // Null-terminate the wide string
	return wstr;
}

void Game::setupAnims()
{
	animMap.clear();

	animMap.emplace(std::pair("idle", std::vector<sf::IntRect>{}));
	animMap["idle"].clear();
	for (int i = 0; i < 9; i++)
	{

		animMap["idle"].push_back({ {i * 96, 0},{96,96} });
	}
	animMap.emplace(std::pair("run", std::vector<sf::IntRect>{}));
	animMap["run"].clear();
	for (int i = 15; i < 23; i++)
	{
		int col = i % 11;
		int row = i / 11;
		animMap["run"].push_back({ {col * 96, row * 96},{96,96} });
	}
	animMap.emplace(std::pair("attack", std::vector<sf::IntRect>{}));
	animMap["attack"].clear();
	for (int i = 57; i < 62; i++)
	{
		int col = i % 11;
		int row = i / 11;
		animMap["attack"].push_back({ {col * 96, row * 96},{96,96} });
	}
	animMap.emplace(std::pair("jump", std::vector<sf::IntRect>{}));
	animMap["jump"].clear();
	for (int i = 44; i < 57; i++)
	{
		int col = i % 11;
		int row = i / 11;
		animMap["jump"].push_back({ {col * 96, row * 96},{96,96} });
	}
	animMap.emplace(std::pair("hit", std::vector<sf::IntRect>{}));
	animMap["hit"].clear();
	for (int i = 23; i < 34; i++)
	{
		int col = i % 11;
		int row = i / 11;
		animMap["hit"].push_back({ {col * 96, row * 96},{96,96} });
	}
	animMap.emplace(std::pair("idle6", std::vector<sf::IntRect>{}));
	animMap["idle6"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap["idle6"].push_back({ {i * 96, 96 * 5},{96,96} });
	}
	animMap.emplace(std::pair("idle7", std::vector<sf::IntRect>{}));
	animMap["idle7"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap["idle7"].push_back({ {i * 96, 96 * 6},{96,96} });
	}
	animMap.emplace(std::pair("idle8", std::vector<sf::IntRect>{}));
	animMap["idle8"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap["idle8"].push_back({ {i * 96, 96 * 7},{96,96} });
	}
	animMap.emplace(std::pair("idle9", std::vector<sf::IntRect>{}));
	animMap["idle9"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap["idle9"].push_back({ {i * 96, 96 * 8},{96,96} });
	}

	animMap.emplace(std::pair("idle10", std::vector<sf::IntRect>{}));
	animMap["idle10"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap["idle10"].push_back({ {i * 96, 96 * 9},{96,96} });
	}
	animMap.emplace(std::pair("idle11", std::vector<sf::IntRect>{}));
	animMap["idle11"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap["idle11"].push_back({ {i * 96, 96 * 10},{96,96} });
	}
	playerSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::PlayerSheet));
	playerSpr.setTextureRect(animMap[currentAnim].at(index));
	if (gClientID == 1)
	{
		playerSpr.setPosition({ 50.f,600.f });
	}
	else
	{
		playerSpr.setPosition({ 350.f,600.f });

	}


	animMap2.emplace(std::pair("idle", std::vector<sf::IntRect>{}));
	animMap2["idle"].clear();
	for (int i = 0; i < 9; i++)
	{

		animMap2["idle"].push_back({ {i * 96, 0},{96,96} });
	}
	animMap2.emplace(std::pair("run", std::vector<sf::IntRect>{}));
	animMap2["run"].clear();
	for (int i = 15; i < 23; i++)
	{
		int col = i % 11;
		int row = i / 11;
		animMap2["run"].push_back({ {col * 96, row * 96},{96,96} });
	}
	animMap2.emplace(std::pair("attack", std::vector<sf::IntRect>{}));
	animMap2["attack"].clear();
	for (int i = 57; i < 62; i++)
	{
		int col = i % 11;
		int row = i / 11;
		animMap2["attack"].push_back({ {col * 96, row * 96},{96,96} });
	}
	animMap2.emplace(std::pair("jump", std::vector<sf::IntRect>{}));
	animMap2["jump"].clear();
	for (int i = 44; i < 57; i++)
	{
		int col = i % 11;
		int row = i / 11;
		animMap2["jump"].push_back({ {col * 96, row * 96},{96,96} });
	}
	animMap2.emplace(std::pair("hit", std::vector<sf::IntRect>{}));
	animMap2["hit"].clear();
	for (int i = 23; i < 34; i++)
	{
		int col = i % 11;
		int row = i / 11;
		animMap2["hit"].push_back({ {col * 96, row * 96},{96,96} });
	}
	animMap2.emplace(std::pair("idle6", std::vector<sf::IntRect>{}));
	animMap2["idle6"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap2["idle6"].push_back({ {i * 96, 96 * 5},{96,96} });
	}
	animMap2.emplace(std::pair("idle7", std::vector<sf::IntRect>{}));
	animMap2["idle7"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap2["idle7"].push_back({ {i * 96, 96 * 6},{96,96} });
	}
	animMap2.emplace(std::pair("idle8", std::vector<sf::IntRect>{}));
	animMap2["idle8"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap2["idle8"].push_back({ {i * 96, 96 * 7},{96,96} });
	}
	animMap2.emplace(std::pair("idle9", std::vector<sf::IntRect>{}));
	animMap2["idle9"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap2["idle9"].push_back({ {i * 96, 96 * 8},{96,96} });
	}

	animMap2.emplace(std::pair("idle10", std::vector<sf::IntRect>{}));
	animMap2["idle10"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap2["idle10"].push_back({ {i * 96, 96 * 9},{96,96} });
	}
	animMap2.emplace(std::pair("idle11", std::vector<sf::IntRect>{}));
	animMap2["idle11"].clear();
	for (int i = 0; i < 11; i++)
	{

		animMap2["idle11"].push_back({ {i * 96, 96 * 10},{96,96} });
	}
	player2Spr.setTexture(Cfg::textures.get((int)Cfg::Textures::PlayerSheet));
	player2Spr.setTextureRect(animMap2[currentAnim2].at(index2));
	if (gClientID == 2)
	{
		player2Spr.setPosition({ 50.f,600.f });
	}
	else
	{
		player2Spr.setPosition({ 350.f,600.f });

	}
}
