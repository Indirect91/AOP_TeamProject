#include "stdafx.h"
#include "Stage1Class.h"
#include "PlayerClass.h"
#include "UIClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"

//=============초기화=============
HRESULT Stage1Class::init(void)
{
	//스테이지 1 이미지
	stage1Img = IMAGEMANAGER->findImage("Stage1");
	stage1CollisionImg = IMAGEMANAGER->findImage("Stage1Collision");

	//스테이지 1 배경 이미지
	IMAGEMANAGER->findImage("나무배경1");
	loopX1 = loopY1 = 0;
	IMAGEMANAGER->findImage("나무배경2");
	loopX2 = loopY2 = 0;
	IMAGEMANAGER->findImage("나무배경3");
	loopX3 = loopY3 = 0;
	IMAGEMANAGER->findImage("나무배경4");
	loopX4 = loopY4 = 0;

	//UI 클래스 생성 및 초기화
	s1UIPtr = new UIClass;
	s1UIPtr->init("Stage1");

	//플레이어 클래스 생성 및 초기화
	playerPtr = new PlayerClass;
	playerPtr->init(100,400,"Stage1Collision");

	//필드 클래스 생성 및 초기화
	fieldPtr = new FieldManagerClass;
	fieldPtr->init("Stage1");

	//에너미 매니저 클래스 생성 및 초기화
	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(EnemyManagerClass::tagWhereStage::stage1);

	//펫 생성 및 초기화
	//박쥐
	s1PetPtr = new PetsClass;
	s1PetPtr->init(PetsClass::PetsTypes::bat, 7748, 1705);
	s1PetPtrV.push_back(s1PetPtr);

	//물개
	s1PetPtr = new PetsClass;
	s1PetPtr->init(PetsClass::PetsTypes::seal, 3317, 607);
	s1PetPtrV.push_back(s1PetPtr);

	//상어
	s1PetPtr = new PetsClass;
	s1PetPtr->init(PetsClass::PetsTypes::shark, 13712, 249);
	s1PetPtrV.push_back(s1PetPtr);

	//세이브 포인트 클래스 생성 및 초기화
	s1SaveMPtr = new savePoint;
	s1SaveMPtr->init(9393, 365);

	//클리어 포인트 클래스 생성 및 초기화
	s1ClearMPtr = new clearPoint;
	s1ClearMPtr->init(17150, 362);

	//보물상자 클래스 생성 및 초기화
	s1TreasurePtr = new treasureBox;
	s1TreasurePtr->init(2189, 406, true, "Stage1Collision");
	s1TreasurePtrV.push_back(s1TreasurePtr);
	
	s1TreasurePtr = new treasureBox;
	s1TreasurePtr->init(4922, 620, false, "Stage1Collision");
	s1TreasurePtrV.push_back(s1TreasurePtr);
	
	s1TreasurePtr = new treasureBox;
	s1TreasurePtr->init(6890, 1261, true, "Stage1Collision");
	s1TreasurePtrV.push_back(s1TreasurePtr);
	
	s1TreasurePtr = new treasureBox;
	s1TreasurePtr->init(9591, 578, true, "Stage1Collision");
	s1TreasurePtrV.push_back(s1TreasurePtr);

	COLLISION.setPlayer(playerPtr);
	COLLISION.setEnemyManagerClass(s1EnemyMPtr);
	COLLISION.setPetsClass(&s1PetPtrV);
	COLLISION.setSavePoint(s1SaveMPtr);
	COLLISION.setTreasureBox(&s1TreasurePtrV);
	COLLISION.setClearPoint(s1ClearMPtr);
	COLLISION.setUIClass(s1UIPtr);
	COLLISION.setFieldManagerClass(fieldPtr);

	return S_OK;
}

//=============해제=============
void Stage1Class::release(void)
{
	//여기 클래스서 new 할당받은거 있으면 해제 하자
	playerPtr->release();
	SAFE_DELETE(playerPtr);

	fieldPtr->release();
	SAFE_DELETE(fieldPtr);

	//에너미 해제
	s1EnemyMPtr->release();

	//UI 클래스 해제
	s1UIPtr->release();
	SAFE_DELETE(s1UIPtr);

	//펫 해제
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->release();
		SAFE_DELETE(s1PetPtrV[i]);
	}

	//세이브 포인트 해제
	s1SaveMPtr->release();
	SAFE_DELETE(s1SaveMPtr);
	
	//클리어 포인트 클래스 해제
	s1ClearMPtr->release();
	SAFE_DELETE(s1ClearMPtr);

	//보물상자
	for (int i = 0; i < s1TreasurePtrV.size(); i++)
	{
		s1TreasurePtrV[i]->release();
		SAFE_DELETE(s1TreasurePtrV[i])
	}

}

//=============업데이트=============
void Stage1Class::update(void)
{
	playerPtr->update();

	//UI 업데이트
	s1UIPtr->update();

	//에너미 업데이트
	if (playerPtr->getChangeCount() == 0)
	{
		s1EnemyMPtr->update(playerPtr->getX(), playerPtr->getY());

		//펫 업데이트
		for (int i = 0; i < s1PetPtrV.size(); i++)
		{
			s1PetPtrV[i]->update();
		}
		fieldPtr->update("Stage1");
	}
	//세이브 포인터 업데이트
	s1SaveMPtr->update();
	//클리어 포인터 업데이트
	s1ClearMPtr->update();
	
	//보물상자 업데이트
	for (int i = 0; i < s1TreasurePtrV.size(); i++)
	{
		s1TreasurePtrV[i]->update();
	}

	//카메라 앵글을 플레이어에게 줌
	CAMERA.cameraFollow(playerPtr->getX(), playerPtr->getY());

	//일반루트
	CAMERA.cameraRevision(0, 0, 2647, WINSIZEY);
	CAMERA.cameraRevision(2647, 0, 4013, WINSIZEY);
	CAMERA.cameraRevision(4014, 0, 5380, 2436);
	CAMERA.cameraRevision(5381, 1668, 6747, 2436);
	CAMERA.cameraRevision(6748, 0, 8114, 2436);
	CAMERA.cameraRevision(8115, 0, 10990, WINSIZEY);
	CAMERA.cameraRevision(10991, 0, 13212, WINSIZEY);
	CAMERA.cameraRevision(13213, 0, 14579, WINSIZEY);
	CAMERA.cameraRevision(14580, 0, 17520, WINSIZEY);

	//숨은루트
	//절벽 위 상자가는 길
	CAMERA.cameraRevision(5381, 0, 6747, WINSIZEY);

	//배경이미지 루프
	loopX1 = CAMERA.getCRc().left / 5;
	loopX2 = CAMERA.getCRc().left / 2;
	loopX3 = CAMERA.getCRc().left / 3;
	loopX4 = CAMERA.getCRc().left / 2;
	loopY4 = CAMERA.getCRc().top / 2;

	COLLISION.playerStepEnemy();
	COLLISION.playerCrashedEnemy();
	COLLISION.playerCrashedEBullet();
	COLLISION.playerChangeEnemyCrash();
	COLLISION.playerAttackEnemy();
	COLLISION.playerFindPets(1);
	COLLISION.playerSavePoint();
	COLLISION.playerFindTreasureBox();
	COLLISION.playerGetJewel();
	COLLISION.playerClearPoint();
	COLLISION.playerDamegeThorn();
	COLLISION.playerChangeTile();
	COLLISION.playerCollisionHideTile();
}

//=============렌더=============
void Stage1Class::render(void)
{
	//스테이지 배경 이미지 렌더
	RECT bgRc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("나무배경1", getMemDC(), &bgRc, loopX1, loopY1);
	IMAGEMANAGER->loopRender("나무배경3", getMemDC(), &bgRc, loopX3, loopY3);
	IMAGEMANAGER->loopRender("나무배경2", getMemDC(), &bgRc, loopX2, loopY2);
	if (CAMERA.getCRc().left >= 4014 && CAMERA.getCRc().left < 8114)
	{
		IMAGEMANAGER->loopRender("나무배경4", getMemDC(), &bgRc, loopX4, loopY4);
	}

	//스테이지 이미지 렌더
	stage1Img->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);

	//픽셀충돌용 이미지 볼 토글키
	if (KEYMANAGER->isToggleKey('W'))
	{
		stage1CollisionImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);
	}

	//플레이어 클래스 렌더
	playerPtr->render();

	//UI 클래스 렌더
	s1UIPtr->render();

	//세이브 포인트 렌더
	s1SaveMPtr->render();
	//클리어 포인트 렌더
	s1ClearMPtr->render();
	
	//보물상자 렌더
	for (int i = 0; i < s1TreasurePtrV.size(); i++)
	{
		s1TreasurePtrV[i]->render();
	}

	//에너미 렌더
	s1EnemyMPtr->render();
	//펫 렌더
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->render();
	}

	fieldPtr->render("Stage1");

	/*좌표 확인용*/
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOutfloat(getMemDC(), 10, 10, "마우스 X", _ptMouse.x + CAMERA.getCRc().left);
	TextOutfloat(getMemDC(), 10, 30, "마우스 Y", _ptMouse.y + CAMERA.getCRc().top);
	TextOutfloat(getMemDC(), 10, 50, "카메라 left", CAMERA.getCRc().left);
}
