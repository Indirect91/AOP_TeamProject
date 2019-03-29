#pragma once
#include "gameNode.h"
class EndingSceneClass : public gameNode
{

private:
	float alpha1;
	float alpha2;
	image * firstImage;
	image * secondImage;
	image * curtain;
	int curtainY;

	BOOL firstDone;
	BOOL secondDone;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	EndingSceneClass() {};
	~EndingSceneClass() {};
};

