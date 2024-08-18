#ifndef ACTIONMAP_H__
#define ACTIONMAP_H__

#include <action/Action.h>
#include <unordered_map> //unordered_map


template<typename T = int>
struct ActionMap
{
    ActionMap(const ActionMap<T>&) = delete;
    ActionMap<T>& operator=(const ActionMap<T>&) = delete;

    ActionMap() = default;

    void map(const T& key, const Action& action);
    const Action& get(const T& key)const;

private:
    std::unordered_map<T,Action> _map;
};
#include "tpl/ActionMap.tpl"

#endif
