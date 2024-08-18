#include <action/Action.h>



Action::Action(const sf::Keyboard::Key& key,int type) : _type(type)
{
    _event.type = sf::Event::EventType::KeyPressed;
    _event.key.code = key;
}

Action::Action(const sf::Mouse::Button& button,int type) : _type(type)
{
    _event.type = sf::Event::EventType::MouseButtonPressed;
    _event.mouseButton.button = button;
}

Action::Action(const JoystickBtn& joyButtonNum, int type) : _type(type)
{
	_event.type = sf::Event::EventType::JoystickButtonPressed;
	_event.joystickButton.button = static_cast<unsigned int>(joyButtonNum);
}
Action::Action(const unsigned int& joybuttonnum, int type) : _type(type)
{
    _event.type = sf::Event::EventType::JoystickButtonPressed;
    _event.joystickButton.button = joybuttonnum;
}

Action::Action(const sf::Joystick::Axis& axis, int type) : _type(type)
{
    _event.type = sf::Event::EventType::JoystickMoved;
    _event.joystickMove.axis = axis;

}


bool Action::operator==(const sf::Event& event)const
{
    bool res = false;

    switch(event.type)
    {
        case sf::Event::EventType::KeyPressed:
        {
            if(_type & Type::Pressed and _event.type == sf::Event::EventType::KeyPressed)
                res = event.key.code == _event.key.code;
        }break;
        case sf::Event::EventType::KeyReleased:
        {
            if(_type & Type::Released and _event.type == sf::Event::EventType::KeyPressed)
                res = event.key.code == _event.key.code;
        }break;
        case sf::Event::EventType::MouseButtonPressed:
        {
            if(_type & Type::Pressed and _event.type == sf::Event::EventType::MouseButtonPressed)
                res = event.mouseButton.button == _event.mouseButton.button;
        }break;
        case sf::Event::EventType::MouseButtonReleased:
        {
            if(_type & Type::Released and _event.type == sf::Event::EventType::MouseButtonReleased)
                res = event.mouseButton.button == _event.mouseButton.button;
        }break;
        case sf::Event::EventType::JoystickButtonPressed:
        {
            if (_type & Type::Pressed and _event.type == sf::Event::EventType::JoystickButtonPressed)
                res = event.joystickButton.button == _event.joystickButton.button;

        }break;
        case sf::Event::EventType::JoystickButtonReleased:
        {
            if (_type & Type::Pressed and _event.type == sf::Event::EventType::JoystickButtonReleased)
                res = event.joystickButton.button == _event.joystickButton.button;

        }break;
        case sf::Event::EventType::JoystickMoved:
        {
            if (_type & Type::Tilted and _event.type == sf::Event::EventType::JoystickMoved)
                res = event.joystickMove.axis == _event.joystickMove.axis;

        }break;
        default: break;
    }
    return res;
}

bool Action::operator==(const Action& other)const
{
    return _type == other._type and other == _event;
}

bool Action::test()const
{
    bool res = false;
    if(_event.type == sf::Event::EventType::KeyPressed)
    {
        if(_type & Type::Pressed)
            res = sf::Keyboard::isKeyPressed(_event.key.code);
    }
    else if (_event.type == sf::Event::EventType::MouseButtonPressed)
    {
        if(_type & Type::Pressed)
            res = sf::Mouse::isButtonPressed(_event.mouseButton.button);
    }
    else if (_event.type == sf::Event::EventType::JoystickButtonPressed)
    {
        sf::Joystick::update();

        if (_type & Type::Pressed)
            res = sf::Joystick::isButtonPressed(0, _event.joystickButton.button);
    }
    else if (_event.type == sf::Event::EventType::JoystickMoved)
    {
        float speed{};
        if (_type & Type::Tilted)
            speed = sf::Joystick::getAxisPosition(0, _event.joystickMove.axis);

        if (speed <= -50.0f || speed >= 50.0f)
            res = true;
            
    }
    return res;
}

