#pragma once
#include "gameNode.h"
/*�����δ� ������ ������ ������ϸ� ���ΰ��ӿ� �߰��صд�*/
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

