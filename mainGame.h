#pragma once
#include "gameNode.h"
/*앞으로는 각각의 씬들의 헤더파일만 메인게임에 추가해둔다*/
#include "loadingScene.h"
#include "Stage1Class.h"
#include "BossStageClass.h"
#include "TitleClass.h"

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

