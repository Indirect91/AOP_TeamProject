#pragma once
#include "gameNode.h"

class BossClass : public gameNode
{
	enum BossState
	{
		idle,		//대기
		shout,		//고함
		change,		//변신
		walk,		//걷기
		run,		//달리기
		attack1,	//공격1
		attack2,	//공격2
		attacked,	//피격당함
		die,		//죽음
		end			//아무 조건도 끝
	}bossState;

	RECT bossRc;						//보스 렉트
	RECT bossAttackRc;					//보스 공격 렉트
	float bossSpeed;						//보스 속도
	float bossGravity;					//보스 중력
	float bossX, bossY;					//보스 중심좌표
	int bossHp;							//보스 체력

	bool isMeet;						//보스와 만났는가?
	bool isStart;						//보스 스테이지에서 전투가 시작하는가?
	bool isRight;						//보스가 오른쪽인가?
	bool isDie;							//보스가 죽었는가?

	image* bossIdleImg;					//보스가 대기하는 이미지
	image* bossShoutImg;				//보스가 대기하는 이미지
	image* bossChangeImg;				//보스가 변신하는 이미지
	image* bossWalkImg;					//보스가 움직이는 이미지
	image* bossRunImg;					//보스가 움직이는 이미지
	image* bossAttack1Img;				//보스가 공격하는 이미지1
	image* bossAttack2Img;				//보스가 공격하는 이미지2
	image* bossAttackedImg;				//보스가 공격받는 이미지
	image* bossDieImg;					//보스가 죽는 이미지

	int imgCount;
	int frameX;
	int frameY;

	int attCount;						//플레이어가 보스를 공격한후 부활까지 카운트 줄 이미지
	int alphaFrame;						//보스가 피격당할때 줄 알파값

	RECT bEmpty;

	class PlayerClass* bPlayerPtr;		//보스 클래스에 있는 플레이어 포인터

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setBPLayerClass(class PlayerClass* _bPlayerPtr) { bPlayerPtr = _bPlayerPtr; }

	bool getIsDie() { return isDie; }

	BossClass() {}
	~BossClass() {}
};

