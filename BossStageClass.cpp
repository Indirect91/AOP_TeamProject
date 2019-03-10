#include "stdafx.h"
#include "BossStageClass.h"
#include "UIClass.h"
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

	//보스스테이지 UI이미지 생성
	bUIPtr = new UIClass;
	bUIPtr->init();

	//보스스테이지 초기화
	fieldPtr = new FieldManagerClass;
	fieldPtr->init("BossStage");

	playerPtr = new PlayerClass;
	playerPtr->init(100,340,"BossStageCollision");

	fieldPtr->setPlayerPtr(playerPtr);

	//적 생성 및 초기화
	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::tagWhereStage::bossStage);	

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
	bTreasurePtr->init(2881, 578, false, "BossStageCollision");
	bTreasurePtrV.push_back(bTreasurePtr);

	bTreasurePtr = new treasureBox;
	bTreasurePtr->init(4677, 921, true, "BossStageCollision");
	bTreasurePtrV.push_back(bTreasurePtr);

	bTreasurePtr = new treasureBox;
	bTreasurePtr->init(4480, 1304, true, "BossStageCollision");
	bTreasurePtrV.push_back(bTreasurePtr);

	COLLISION.setPlayer(playerPtr);
	COLLISION.setPetsClass(&bPetPtrV);
	COLLISION.setSavePoint(bSaveMPtr);
	COLLISION.setTreasureBox(&bTreasurePtrV);
	COLLISION.setEnemyManagerClass(bEnemyMPtr);

	return S_OK;
}

//=============해제=============
void BossStageClass::release(void)
{
	playerPtr->release();
	SAFE_DELETE(playerPtr);

	fieldPtr->release();
	SAFE_DELETE(fieldPtr);

	//보스스테이지 UI이미지 해제
	bUIPtr->release();
	SAFE_DELETE(bUIPtr);

	//적 클래스 해제
	bEnemyMPtr->release();
	SAFE_DELETE(bEnemyMPtr);
	
	//펫 클래스 해제
	for (UINT i = 0; i < bPetPtrV.size(); i++)
	{
		bPetPtrV[i]->release();
		SAFE_DELETE(bPetPtrV[i]);
	}

	//세이브 포인트 클래스 해제
	bSaveMPtr->release();
	SAFE_DELETE(bSaveMPtr);

	//보물상자 클래스 해제
	for (UINT i = 0; i < bTreasurePtrV.size(); i++)
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
	bUIPtr->update();

	//적 클래스 업데이트
	bEnemyMPtr->update(playerPtr->getX(), playerPtr->getY());

	//펫 클래스 업데이트
	for (UINT i = 0; i < bPetPtrV.size(); i++)
	{
		bPetPtrV[i]->update();
	}

	//세이브 포인트 업데이트
	bSaveMPtr->update();

	//보물상자 클래스 업데이트
	for (UINT i = 0; i < bTreasurePtrV.size(); i++)
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
	
	COLLISION.playerCrashedEnemy();
	COLLISION.playerStepEnemy();
	COLLISION.playerCrashedEBullet();
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
	//if (CAMERA.getCRc().left >= 4070 && CAMERA.getCRc().left < 9538)
	//{
	//	IMAGEMANAGER->loopRender("나무배경4", getMemDC(), &bgRc, loopX4, loopY4);
	//}

	BossStageImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);
	
	fieldPtr->render();

	bUIPtr->render();

	//보물상자 클래스 렌더
	for (UINT i = 0; i < bTreasurePtrV.size(); i++)
	{
		bTreasurePtrV[i]->render();
	}

	//세이브 포인트 클래스 렌더
	bSaveMPtr->render();

	//적 클래스 렌더
	bEnemyMPtr->render();

	//펫 클래스 렌더
	for (UINT i = 0; i < bPetPtrV.size(); i++)
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
