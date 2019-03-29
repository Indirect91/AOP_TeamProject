#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "Stage1Class.h"
#include "BossStageClass.h"
#include "TitleClass.h"
#include "WorldMapScene.h"
#include "VillageClass.h"
#include "CinematicClass.h"
#include "EndingSceneClass.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

