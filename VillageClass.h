#pragma once
#include "gameNode.h"

class VillageClass : public gameNode
{
	image* villageImg;				//마을 이미지
	image* villageBgImg;			//마을 배경 이미지
	int loopX;						//배경 돌릴 루프X

	RECT merchantRc;				//상인 렉트
	image* merchantImg;				//상인 이미지
	int imgVCount;
	int frameVX;

	class PlayerClass* vPlayerPtr;	//마을 스테이지에 있는 플레이어 포인터

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	VillageClass() {}
	~VillageClass() {}
};

