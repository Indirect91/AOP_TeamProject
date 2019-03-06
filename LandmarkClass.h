#pragma once
#include "gameNode.h"

//===================================
//	## 세이브 포인트 ##
//===================================
class savePoint : public gameNode
{
	image* savePointImg;		//세이브 포인트 이미지
	RECT savePointRc;			//세이브 포인트 렉터

	image* savePointFireImg;	//세이브 포인트 불꽃 이미지
	RECT savePointFireRc;		//세이브 포인트 불꽃 렉터

	bool isSave;				//세이브 포인트에 닿았는가?
	bool isFire;				//한번 불꽃이 일어났는가?

	float savePX, savePY;		//지형물 중심좌표

	int imgCount;				//이미지 카운팅 변수
	int frameX1;				//상 이미지 프레임 변수
	int frameX2;				//불꽃 이미지 프레임 변수

public:
	HRESULT init(float _x, float _y);
	void release(void);
	void update(void);
	void render(void);

	RECT getSavePointRc() { return savePointRc; }

	void setIsSave(bool _isSave) { isSave = _isSave; }

	savePoint() {}
	~savePoint() {}
};

//===================================
//	## 보물상자 ##
//===================================
class treasureBox : public gameNode
{
	image* treasureBoxImg;			//보물상자 이미지
	RECT treasureBoxRc;				//보물상자 렉트

	bool isOpen;					//오픈되었는가?
	bool isRight;					//오른쪽을 향하고 있는가?

	float treasureX, treasureY;		//보물상자 중심좌표

	int imgCount;
	int frameX, frameY;

public:
	HRESULT init(float _x, float _y, bool _isRight);
	void release(void);
	void update(void);
	void render(void);

	treasureBox() {}
	~treasureBox() {}
};