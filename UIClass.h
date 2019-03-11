#pragma once
#include "gameNode.h"

class UIClass : public gameNode
{
	image* jewelShapeImg;		//게임에서 보석의 숫자 옆에있는 보석문양

	image* HPImg;				//플레이어 체력
	int frameHP;				//0->체력x, 1=체력o

	struct tagPetCheck
	{
		image* CheckImg;		//체크용 이미지
		bool isCheck;			//스테이지1에서 찾았는가?
		int framePet;			//프레임 이미지
		POINT position;
	};

	tagPetCheck checkSealS1;
	tagPetCheck checkBatS1;
	tagPetCheck checkSharkS1;

	tagPetCheck checkSealB;
	tagPetCheck checkBatB;
	tagPetCheck checkSharkB;

	string petsWhere;

public:

	HRESULT init(string _petsWhere);
	void release();
	void update();
	void render();


	UIClass() {}
	~UIClass() {}
};

