#pragma once
#include "gameNode.h"

enum PetsTypes
{
	bat = 1,
	seal,
	shark
};

class PetsClass : public gameNode
{
	image* petImage;		//동물 이미지
	RECT petRc;				//동물 렉트

	float petX, petY;		//동물 중심좌표
	float petSpeed;			//동물 속도
	bool isPetRight;		//펫이 오른쪽을 보고있는가? true->오른쪽
	bool isPetCatch;		//펫을 잡았는가? true->잡음

	int petImgCount;		//펫 이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트

	int whichPet;			//어떤 펫을 선택했는가?

public:
	HRESULT init(int _whichPet, float _petX, float _petY);
	void release(void);
	void update(void);
	void render(void);

	float getPetX() { return petX; }
	void setPetX(float _petX) { petX = _petX; }

	float getPetY() { return petY; }
	void setPetY(float _petY) { petY = _petY; }

	bool getIsPetCatch() { return isPetCatch; }
	void setIsPetCatch(bool _isPetCatch) { isPetCatch = _isPetCatch; }


	PetsClass() {}
	~PetsClass() {}
};

