#pragma once
#include "gameNode.h"

class PetsClass : public gameNode
{
public:
	enum class PetsTypes
	{
		seal = 1,
		bat,
		shark
	};
private:


	image* petImg;			//동물 이미지
	RECT petRc;				//동물 렉트

	float petX, petY;		//동물 중심좌표
	float petSpeed;			//동물 속도
	bool isPetRight;		//펫이 오른쪽을 보고있는가? true->오른쪽
	bool isPetFind;			//펫을 찾았는가? true->찾음
	bool isPetCatch;		//펫을 잡았는가? true->잡음

	int petImgCount;		//펫 이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트

	PetsTypes whichPet;			//어떤 펫을 선택했는가?

	image* petHeartImg;		//동물 발견시 뜰 하트 이미지
	int petHImgCount;		//하트 이미지 카운트
	int frameHX;			//하트 이미지 프레임

public:

	HRESULT init(PetsTypes _whichPet, float _petX, float _petY, bool _isFind);
	void release(void);
	void update(void);
	void render(void);

	RECT getPetRc() { return petRc; }

	float getPetX() { return petX; }
	void setPetX(float _petX) { petX = _petX; }

	float getPetY() { return petY; }
	void setPetY(float _petY) { petY = _petY; }

	bool getIsPetFind() { return isPetFind; }
	void setIsPetFind(bool _isPetFind) { isPetFind = _isPetFind; }

	PetsTypes getWhichPet() { return whichPet; }

	PetsClass() {}
	~PetsClass() {}
};

