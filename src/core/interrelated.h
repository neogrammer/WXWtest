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


enum class PlayerAnimType : int
{
	Idle = 0, Run = 1, Attack = 2, Jump = 3, Hit = 4
};

#endif