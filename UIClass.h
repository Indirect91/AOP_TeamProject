#pragma once
#include "gameNode.h"

class UIClass : public gameNode
{
	image* moneyBar;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	UIClass() {}
	~UIClass() {}
};

