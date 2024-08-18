#ifndef ACTION_H__
#define ACTION_H__

#include <SFML/Window/Event.hpp>

enum class JoystickBtn : unsigned int
{
	X = 0,
	B = 1,
	A = 2,
	Y = 3,

	L1 = 4,
	R1 = 5,

	Select = 8,
	Start = 9
};

struct Action
{
    enum Type
    {
        RealTime = 1,
        Pressed = 1 << 1,
        Released = 1 << 2,
        Tilted = 1 << 3
    };

    Action(const sf::Keyboard::Key& key,int type=Type::RealTime | Type::Pressed);
    Action(const sf::Mouse::Button& button,int type=Type::RealTime | Type::Pressed);
	Action(const JoystickBtn& joyButtonNum, int type = Type::RealTime | Type::Pressed);
    Action(const unsigned int& joyButtonNum, int type = Type::RealTime | Type::Pressed);
    Action(const sf::Joystick::Axis& axis, int type = Type::RealTime | Type::Tilted);


    bool test()const;

    bool operator==(const sf::Event& event)const;
    bool operator==(const Action& other)const;


private:
    template<typename> friend struct ActionTarget;
    sf::Event _event;
    int _type;
};

#endif
