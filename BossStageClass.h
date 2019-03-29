#pragma once
#include "gameNode.h"
class BossStageClass :public gameNode
{
	image* BossStageImg;
	image* BossCollisionImg;

	float loopX1, loopY1;		//배경 이미지 1의 루프좌표
	float loopX2, loopY2;		//배경 이미지 2의 루프좌표
	float loopX3, loopY3;		//배경 이미지 3의 루프좌표
	float loopX4, loopY4;		//배경 이미지 4의 루프좌표

	class UIClass* bUIPtr;

	class PlayerClass* playerPtr;				//보스 스테이지에 있는 플레이어 클래스 포인터

	class FieldManagerClass* fieldPtr;

	class EnemyManagerClass* bEnemyMPtr;		//보스 스테이지에 있는 적 매니저 클래스 포인터

	class PetsClass* bPetPtr;					//보스 스테이지에 있는 펫 클래스 포인터
	vector <PetsClass*> bPetPtrV;				//보스 스테이지에 있는 펫 클래스 포인터를 담는 벡터
	image * respawnImg;							
	UINT respawnFrame;							

	class savePoint* bSaveMPtr;					//보스 스테이지에 있는 세이브포인터 클래스 포인터
	class clearPoint* bClearMPtr;				//보스 스테이지에 있는 클리어포인터 클래스 포인터

	class treasureBox* bTreasurePtr;			//보스 스테이지에 있는 보물상자 클래스 포인터
	vector <treasureBox*> bTreasurePtrV;		//보스 스테이지에 있는 보물상자 클래스 포인터를 담는 벡터

	class BossClass* bBossPtr;					//보스 스테이지에 있는 보스 클래스 포인터


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	BossStageClass() {}
	~BossStageClass() {}
};

