#pragma once
#include "gameNode.h"
class WorldMapScene :	public gameNode
{
	image* StageBar;
	image* MenuBar;
	image* WorldMap;
	
	bool zooming;
	bool zoomToggle;
	float worldMapZoom;
	UINT totalAlpha;
	UINT counter;

	
	bool firstPhase;
	bool SecondPhase;
	bool FinalPhase;

public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	WorldMapScene() {}
	~WorldMapScene() {}
};

