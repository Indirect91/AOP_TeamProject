#pragma once
#include "gameNode.h"

class BossClass : public gameNode
{
	enum hahahaha
	{
		a,
		b,
		c
	};

	enum DOLTAN
	{
		stupid,
		smartALittle,
		lol
	};

	RECT BossRc;						//보스 렉트
	RECT bossAttackRc;					//보스 공격 렉트
	float bSpeed;						//보스 속도
	float bGravity;						//보스 중력
	float bossX, bossY;						//보스 중심좌표
	bool isRight;						//보스가 오른쪽인가?
	bool isMove;						//보스가 움직이는가?
	bool isAttak;						//보스가 공격하는가?

	image* BossMoveImg;					//보스가 움직이는 이미지
	image* BossAttack1Img;				//보스가 공격하는 이미지1
	image* BossAttack2Img;				//보스가 공격하는 이미지2
	image* BossDieImg;					//보스가 죽는 이미지

	//class PlayerClass* bPlayerPtr;		//보스 클래스에 있는 플레이어 포인터

public:
	HRESULT init(void);
	void release(void);
	void update(float _playerX);
	void render(void);

	//void setBPLayerClass(class PlayerClass* _bPlayerPtr) { bPlayerPtr = _bPlayerPtr; }

	BossClass() {}
	~BossClass() {}
};

