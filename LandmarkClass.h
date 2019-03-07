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
	void setIsFire(bool _isFire) { isFire = _isFire; }

	savePoint() {}
	~savePoint() {}
};

//===================================
//	## 보물상자 ##
//===================================
class treasureBox : public gameNode
{
public:
	//보석
	struct tagJewel
	{
		image* jewelImg;			//보석이미지
		int jewelType;				//일단 쥬얼 모양 랜덤 넣을것
		RECT jewelRc;				//보석 렉트
		float jewelX, jewelY;		//보석 중심좌표
		float jAngle;				//보석이 날아갈 앵글
		float jGravity;				//보석 날아갔다가 떨어트릴 중력
		float jSpeed;				//보석이 날아갈 속도
		int jewelPrice;				//보석이 얼마인가?
	};
private:

	image* treasureBoxImg;			//보물상자 이미지
	RECT treasureBoxRc;				//보물상자 렉트

	bool isOpen;					//오픈되었는가?
	bool isRight;					//오른쪽을 향하고 있는가?

	float treasureX, treasureY;		//보물상자 중심좌표

	int imgCount;
	int frameX, frameY;



	int jewelNum;					//보석이 몇개가 나올것인가?
	tagJewel jewel;					//보석 구조체
	vector <tagJewel>jewelV;		//보석 구조체를 담는 벡터

	string collisionStage;			//픽셀 충돌할 스테이지가 어딘지 입력하기위해

public:
	HRESULT init(float _x, float _y, bool _isRight, string _collisionStage);
	void release(void);
	void update(void);
	void render(void);

	RECT getTreasureBoxRc() { return treasureBoxRc; }
	vector <tagJewel> & getJewels() { return jewelV; }
	void setIsOpen(bool _isOpen) { isOpen = _isOpen; }
	bool getIsOpen() { return isOpen; }

	treasureBox() {}
	~treasureBox() {}
};