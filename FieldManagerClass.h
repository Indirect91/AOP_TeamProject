#pragma once
#include "gameNode.h"
class FieldManagerClass :public gameNode
{
public:

	class BreakTileClass* breakTilePtr;
	class HideTileClass* hideTilePtr;
	class ThorntrapClass* thornPtr;
	class PlayerClass* playerPtr;
	class FlowerClass* flowerPtr;
	void setPlayerPtr(class PlayerClass* player) { playerPtr = player; }

	HRESULT init(string stage);
	void release(void);
	void update(void);
	void render(void);


	FieldManagerClass() {}
	~FieldManagerClass() {}
};

