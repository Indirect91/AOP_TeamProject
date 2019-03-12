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
	class UniClass* uniPtr;

	void setPlayerPtr(class PlayerClass* player) { playerPtr = player; }



	HRESULT init(string stage);
	void release(void);
	void update(string stage);
	void render(string stage);


	FieldManagerClass() {}
	~FieldManagerClass() {}
};

