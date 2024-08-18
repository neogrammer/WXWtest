#ifndef RESOURCEMANAGER_H__
#define RESOURCEMANAGER_H__

#include <unordered_map> //unordered_map
#include <string> //string
#include <memory> //unique_ptr

#include <SFML/Audio.hpp> //sf::Music

template<typename RESOURCE,typename IDENTIFIER = int>
struct ResourceManager
{
	ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;


    template<typename ... Args>
    void load(const IDENTIFIER& id,Args&& ... args);

    RESOURCE& get(const IDENTIFIER& id)const;

private:
    std::unordered_map<IDENTIFIER,std::unique_ptr<RESOURCE>> _map;
};

template<typename IDENTIFIER>
struct ResourceManager<sf::Music,IDENTIFIER>
{
	ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;


    template<typename ... Args>
    void load(const IDENTIFIER& id,Args&& ... args);

    sf::Music& get(const IDENTIFIER& id)const;

private:
    std::unordered_map<IDENTIFIER,std::unique_ptr<sf::Music>> _map;
};

#include "tpl/ResourceManager.tpl"
#endif
