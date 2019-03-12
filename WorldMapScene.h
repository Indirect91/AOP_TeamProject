#pragma once
#include "gameNode.h"
class WorldMapScene :	public gameNode
{
	image* StageBar;
	image* MenuBar;
	image* WorldMap;
public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	WorldMapScene() {}
	~WorldMapScene() {}
};

