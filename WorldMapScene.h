#pragma once
#include "gameNode.h"
class WorldMapScene : public gameNode
{
	image* StageBar;
	image* MenuBar;
	image* WorldMap;
	image* WorldPip;
	image* WorldPipRun;
	UINT idlePipIndex;
	BOOL isLeft;
	UINT runPipIndex;

	bool zooming;
	bool zoomToggle;
	float pipZoom;
	float worldMapZoom;
	UINT totalAlpha;
	UINT counter;

	UINT upCounter;
	UINT downCounter;
	UINT rightCounter;
	UINT leftCounter;

	bool firstPhase;
	bool SecondPhase;
	bool FinalPhase;

	bool up;
	bool down;
	bool right;
	bool left;

public:
	void movePipRight();
	void movePipLeft();
	void movePipDown();
	void movePipUp();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	WorldMapScene() {}
	~WorldMapScene() {}
};
