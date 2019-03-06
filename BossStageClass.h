#pragma once
#include "gameNode.h"
class BossStageClass :
	public gameNode
{
public:



	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	BossStageClass() {}
	~BossStageClass() {}
};

