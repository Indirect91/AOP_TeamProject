#pragma once
#include "FieldManagerClass.h"
class BreakTileClass :	public FieldManagerClass
{
public:
	enum class BreakTile
	{
		Stage1 = 0,
		BossStage
	};

private:
	struct Tile
	{
		RECT rc;
		POINT point;
		bool isTouch;
		bool isMode;
		int TouchCount;
		int Count;
	};
	vector<Tile>TileList;

public:
	Tile tile;

	class PlayerClass* player;
	void setPlayer(PlayerClass* play) { player = play; }


	HRESULT init(BreakTile Stage);
	void release(void);
	void update(PlayerClass * player);
	void render(void);


	BreakTileClass() {}
	~BreakTileClass() {}
};

