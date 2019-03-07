#include "stdafx.h"
#include "BossStageClass.h"
#include "PlayerClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"

//=============초기화=============
HRESULT BossStageClass::init(void)
{
	//보스 스테이지 이미지 렌더
	BossStageImg = IMAGEMANAGER->findImage("BossStage");
	BossCollisionImg = IMAGEMANAGER->findImage("BossStageCollision");

	IMAGEMANAGER->findImage("나무배경1");
	loopX1 = loopY1 = 0;
	IMAGEMANAGER->findImage("나무배경2");
	loopX2 = loopY2 = 0;
	IMAGEMANAGER->findImage("나무배경3");
	loopX3 = loopY3 = 0;
	IMAGEMANAGER->findImage("나무배경4");
	loopX4 = loopY4 = 0;

	//보스스테이지 초기화
	fieldPtr = new FieldManagerClass;
	fieldPtr->init("BossStage");

	playerPtr = new PlayerClass;
	playerPtr->init(100,100,"BossStageCollision");


	fieldPtr->setPlayerPtr(playerPtr);



	//적 생성 및 초기화
#pragma region 에너미
	//떠다니는 문어
	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::octopus, 4414, 480, 0, 0);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::octopus, 4664, 480, 0, 0);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::octopus, 4714, 1053, 0, 0);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::octopus, 5843, 1017, 0, 0);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	//기어다니는 벌레
	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::bug, 3197, 629, 2991, 3413);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::bug, 4855, 1229, 4744, 4997);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::bug, 5148, 1314, 5078, 5332);
	bEnemyMPtrV.push_back(bEnemyMPtr);
	 
	//크리스탈
	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::crystal, 1858, 645, 0,  0);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::crystal, 2557, 598, 2404, 2756);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::crystal, 6082, 1160, 0, 0);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::crystal, 7273, 2010, 7141, 7673);
	bEnemyMPtrV.push_back(bEnemyMPtr);

	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::EnemyKind::crystal, 9336, 1358, 9266, 9376);
	bEnemyMPtrV.push_back(bEnemyMPtr);

#pragma endregion 에너미

	//펫 생성 및 초기화
	bPetPtr = new PetsClass;
	bPetPtr->init(PetsClass::PetsTypes::seal, 7087, 1166);
	bPetPtrV.push_back(bPetPtr);

	//세이브 포인트 생성 및 초기화
	bSaveMPtr = new savePoint;
	bSaveMPtr->init(8530, 1306);

	//보물상자 생성 및 초기화
	bTreasurePtr = new treasureBox;
	bTreasurePtr->init(2261, 577, true, "BossStageCollision");
	bTreasurePtrV.push_back(bTreasurePtr);

	bTreasurePtr = new treasureBox;
	bTreasurePtr->init(2881, 578, true, "BossStageCollision");
	bTreasurePtrV.push_back(bTreasurePtr);

	bTreasurePtr = new treasureBox;
	bTreasurePtr->init(4677, 921, true, "BossStageCollision");
	bTreasurePtrV.push_back(bTreasurePtr);

	bTreasurePtr = new treasureBox;
	bTreasurePtr->init(4480, 1304, true, "BossStageCollision");
	bTreasurePtrV.push_back(bTreasurePtr);

	COLLISION.setPlayer(playerPtr);
	COLLISION.setEnemyManagerClass(&bEnemyMPtrV);
	COLLISION.setPetsClass(&bPetPtrV);
	COLLISION.setSavePoint(bSaveMPtr);
	COLLISION.setTreasureBox(&bTreasurePtrV);

	return S_OK;
}

//=============해제=============
void BossStageClass::release(void)
{
	playerPtr->release();
	SAFE_DELETE(playerPtr);

	fieldPtr->release();
	SAFE_DELETE(fieldPtr);

	//적 클래스 해제
	for (int i = 0; i < bEnemyMPtrV.size(); i++)
	{
		bEnemyMPtrV[i]->release();
		SAFE_DELETE(bEnemyMPtrV[i]);
	}
	
	//펫 클래스 해제
	for (int i = 0; i < bPetPtrV.size(); i++)
	{
		bPetPtrV[i]->release();
		SAFE_DELETE(bPetPtrV[i]);
	}

	//세이브 포인트 클래스 해제
	bSaveMPtr->release();
	SAFE_DELETE(bSaveMPtr);

	//보물상자 클래스 해제
	for (int i = 0; i < bTreasurePtrV.size(); i++)
	{
		bTreasurePtrV[i]->release();
		SAFE_DELETE(bTreasurePtrV[i]);
	}
}

//=============업데이트=============
void BossStageClass::update(void)
{
	//업데이트 돌리는곳
	fieldPtr->update();
	playerPtr->update();

	//적 클래스 업데이트
	for (int i = 0; i < bEnemyMPtrV.size(); i++)
	{
		bEnemyMPtrV[i]->update();
	}

	//펫 클래스 업데이트
	for (int i = 0; i < bPetPtrV.size(); i++)
	{
		bPetPtrV[i]->update();
	}

	//세이브 포인트 업데이트
	bSaveMPtr->update();

	//보물상자 클래스 업데이트
	for (int i = 0; i < bTreasurePtrV.size(); i++)
	{
		bTreasurePtrV[i]->update();
	}


	//카메라 업데이트
	CAMERA.cameraFollow(playerPtr->getX(), playerPtr->getY());

	//카메라 구간
	CAMERA.cameraRevision(0, 0, 1366, 768);
	CAMERA.cameraRevision(1367, 0, 4069, 768);
	CAMERA.cameraRevision(4070, 0, 5436, 1422);
	CAMERA.cameraRevision(5436, 654, 6802, 2256);
	CAMERA.cameraRevision(6804, 851, 8170, 2144);
	CAMERA.cameraRevision(8171, 735, 9537, 1503);
	CAMERA.cameraRevision(8171, 1504, 9537, 2436);
	CAMERA.cameraRevision(9538, 1668, 10904, 2436);

	//배경이미지 루프
	loopX1 = CAMERA.getCRc().left / 5;
	loopX2 = CAMERA.getCRc().left / 2;
	loopX3 = CAMERA.getCRc().left / 3;
	loopX4 = CAMERA.getCRc().left / 2;
	loopY4 = CAMERA.getCRc().top / 2;

	COLLISION.playerStepEnemy();
	COLLISION.playerCrashedEnemy();
	COLLISION.playerFindPets();
	COLLISION.playerSavePoint();
	COLLISION.playerFindTreasureBox();
	COLLISION.playerGetJewel();

}

//=============렌더=============
void BossStageClass::render(void)
{
	//스테이지 배경 이미지 렌더
	RECT bgRc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("나무배경1", getMemDC(), &bgRc, loopX1, loopY1);
	IMAGEMANAGER->loopRender("나무배경3", getMemDC(), &bgRc, loopX3, loopY3);
	IMAGEMANAGER->loopRender("나무배경2", getMemDC(), &bgRc, loopX2, loopY2);
	//if (CAMERA.getCRc().left >= 4014 && CAMERA.getCRc().left < 8114)
	//{
	//	IMAGEMANAGER->loopRender("나무배경4", getMemDC(), &bgRc, loopX4, loopY4);
	//}

	BossStageImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);
	
	fieldPtr->render();

	//보물상자 클래스 렌더
	for (int i = 0; i < bTreasurePtrV.size(); i++)
	{
		bTreasurePtrV[i]->render();
	}

	//세이브 포인트 클래스 렌더
	bSaveMPtr->render();

	//적 클래스 렌더
	for (int i = 0; i < bEnemyMPtrV.size(); i++)
	{
		bEnemyMPtrV[i]->render();
	}

	//펫 클래스 렌더
	for (int i = 0; i < bPetPtrV.size(); i++)
	{
		bPetPtrV[i]->render();
	}
	
	//플레이어 클래스 렌더
	playerPtr->render();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		BossCollisionImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);
	}

	/*좌표 확인용*/
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOutfloat(getMemDC(), 10, 10, "마우스 X", _ptMouse.x + CAMERA.getCRc().left);
	TextOutfloat(getMemDC(), 10, 30, "마우스 Y", _ptMouse.y + CAMERA.getCRc().top);
	TextOutfloat(getMemDC(), 10, 50, "카메라 left", CAMERA.getCRc().left);
}
