#ifndef INTERRELATED_H__
#define INTERRELATED_H__
#include <vector>
struct ObjectRenderData
{
	int x{}, y{}, texRectPosX{}, texRectPosY{}, texRectW{}, texRectH{};
	int texId{}, entityId{};
};

struct WorldUpdate
{
	std::vector<ObjectRenderData> objectDataVec{};
};

enum class InputType : int
{
	Up = 0, Down = 1, Left = 2, Right = 3, Attack = 4, Run = 5, Start = 6, Escape = 7, Count = 8,
};

#endif