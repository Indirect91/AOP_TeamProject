#include "stdafx.h"
#include "Stage1Class.h"
#include "PlayerClass.h"
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

	//플레이어 클래스 생성 및 초기화
	playerPtr = new PlayerClass;
	playerPtr->init();

	//필드 클래스 생성 및 초기화
	fieldPtr = new FieldManagerClass;
	fieldPtr->init("Stage1");

	//에너미 매니저 생성 및 초기화 -> 이 부분에 인자값만 넣어 생성및 초기화 해주면 됨
#pragma region 에너미
	//1. 날으는 문어
	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(1, 1844, 575, 0, 0);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(1, 1959, 483, 0, 0);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	//2. 기어다니는 애벌레
	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(2, 2455, 630, 2000, 2600);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(2, 5618, 501, 5538, 5695);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(2, 7127, 586, 7029, 7194);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(2, 7166, 1570, 7122, 7273);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(2, 7500, 1228, 7416, 7607);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(2, 13813, 677, 13666, 13898);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(2, 14064, 326, 13916, 14150);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	//3.날아다니는 크리스탈
	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(3, 7218, 2170, 7156, 7283);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(3, 8934, 640, 8846, 9096);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(3, 10112, 630, 9880, 10320);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

#pragma endregion 에너미

	//펫 생성 및 초기화
	//박쥐
	s1PetPtr = new PetsClass;
	s1PetPtr->init(1, 7748, 1705);
	s1PetPtrV.push_back(s1PetPtr);

	//물개
	s1PetPtr = new PetsClass;
	s1PetPtr->init(2, 3317, 607);
	s1PetPtrV.push_back(s1PetPtr);

	//상어
	s1PetPtr = new PetsClass;
	s1PetPtr->init(3, 13712, 249);
	s1PetPtrV.push_back(s1PetPtr);

	//세이브 포인트 클래스 생성 및 초기화
	s1SaveMPtr = new savePoint;
	s1SaveMPtr->init(9393, 365);
	s1SaveMPtrV.push_back(s1SaveMPtr);

	//보물상자 클래스 생성 및 초기화
	s1TreasurePtr = new treasureBox;
	s1TreasurePtr->init(WINSIZEX / 2, 500, true);
	s1TreasurePtrV.push_back(s1TreasurePtr);

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
	for (int i = 0; i < s1EnemyMPtrV.size(); i++)
	{
		s1EnemyMPtrV[i]->release();
		SAFE_DELETE(s1EnemyMPtrV[i]);
	}

	//펫 해제
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->release();
		SAFE_DELETE(s1PetPtrV[i]);
	}

	//세이브 포인트 해제
	for (int i = 0; i < s1SaveMPtrV.size(); i++)
	{
		s1SaveMPtrV[i]->release();
		SAFE_DELETE(s1SaveMPtrV[i]);
	}

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

	//에너미 업데이트
	for (int i = 0; i < s1EnemyMPtrV.size(); i++)
	{
		s1EnemyMPtrV[i]->update();
	}

	//펫 업데이트
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->update();
	}

	fieldPtr->update();

	//세이브 포인터 업데이트
	for (int i = 0; i < s1SaveMPtrV.size(); i++)
	{
		s1SaveMPtrV[i]->update();
	}
	
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
	CAMERA.cameraRevision(13213, 0, 15770, WINSIZEY);
	CAMERA.cameraRevision(15771, 0, 17520, WINSIZEY);

	//숨은루트
	//절벽 위 상자가는 길
	CAMERA.cameraRevision(5381, 0, 6747, WINSIZEY);

	//배경이미지 루프
	loopX1 = CAMERA.getCRc().left / 5;
	loopX2 = CAMERA.getCRc().left / 2;
	loopX3 = CAMERA.getCRc().left / 3;
	loopX4 = CAMERA.getCRc().left / 2;
	loopY4 = CAMERA.getCRc().top / 2;

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

	//세이브 포인트 렌더
	for (int i = 0; i < s1SaveMPtrV.size(); i++)
	{
		s1SaveMPtrV[i]->render();
	}
	//보물상자 렌더
	for (int i = 0; i < s1TreasurePtrV.size(); i++)
	{
		s1TreasurePtrV[i]->render();
	}

	//에너미 렌더
	for (int i = 0; i < s1EnemyMPtrV.size(); i++)
	{
		s1EnemyMPtrV[i]->render();
	}
	//펫 렌더
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->render();
	}

	fieldPtr->render();

	/*좌표 확인용*/
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOutfloat(getMemDC(), 10, 10, "마우스 X", _ptMouse.x + CAMERA.getCRc().left);
	TextOutfloat(getMemDC(), 10, 30, "마우스 Y", _ptMouse.y + CAMERA.getCRc().top);
	TextOutfloat(getMemDC(), 10, 50, "카메라 left", CAMERA.getCRc().left);

}
