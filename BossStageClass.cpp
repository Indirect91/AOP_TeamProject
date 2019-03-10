#include "stdafx.h"
#include "BossStageClass.h"
#include "UIClass.h"
#include "PlayerClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"

//=============�ʱ�ȭ=============
HRESULT BossStageClass::init(void)
{
	//���� �������� �̹��� ����
	BossStageImg = IMAGEMANAGER->findImage("BossStage");
	BossCollisionImg = IMAGEMANAGER->findImage("BossStageCollision");

	IMAGEMANAGER->findImage("�������1");
	loopX1 = loopY1 = 0;
	IMAGEMANAGER->findImage("�������2");
	loopX2 = loopY2 = 0;
	IMAGEMANAGER->findImage("�������3");
	loopX3 = loopY3 = 0;
	IMAGEMANAGER->findImage("�������4");
	loopX4 = loopY4 = 0;

	//������������ UI�̹��� ����
	bUIPtr = new UIClass;
	bUIPtr->init();

	//������������ �ʱ�ȭ
	fieldPtr = new FieldManagerClass;
	fieldPtr->init("BossStage");

	playerPtr = new PlayerClass;
	playerPtr->init(100,340,"BossStageCollision");

	fieldPtr->setPlayerPtr(playerPtr);

	//�� ���� �� �ʱ�ȭ
	bEnemyMPtr = new EnemyManagerClass;
	bEnemyMPtr->init(EnemyManagerClass::tagWhereStage::bossStage);	

	//�� ���� �� �ʱ�ȭ
	bPetPtr = new PetsClass;
	bPetPtr->init(PetsClass::PetsTypes::seal, 7087, 1166);
	bPetPtrV.push_back(bPetPtr);

	//���̺� ����Ʈ ���� �� �ʱ�ȭ
	bSaveMPtr = new savePoint;
	bSaveMPtr->init(8530, 1306);

	//�������� ���� �� �ʱ�ȭ
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

//=============����=============
void BossStageClass::release(void)
{
	playerPtr->release();
	SAFE_DELETE(playerPtr);

	fieldPtr->release();
	SAFE_DELETE(fieldPtr);

	//������������ UI�̹��� ����
	bUIPtr->release();
	SAFE_DELETE(bUIPtr);

	//�� Ŭ���� ����
	bEnemyMPtr->release();
	SAFE_DELETE(bEnemyMPtr);
	
	//�� Ŭ���� ����
	for (UINT i = 0; i < bPetPtrV.size(); i++)
	{
		bPetPtrV[i]->release();
		SAFE_DELETE(bPetPtrV[i]);
	}

	//���̺� ����Ʈ Ŭ���� ����
	bSaveMPtr->release();
	SAFE_DELETE(bSaveMPtr);

	//�������� Ŭ���� ����
	for (UINT i = 0; i < bTreasurePtrV.size(); i++)
	{
		bTreasurePtrV[i]->release();
		SAFE_DELETE(bTreasurePtrV[i]);
	}
}

//=============������Ʈ=============
void BossStageClass::update(void)
{
	//������Ʈ �����°�
	fieldPtr->update();
	playerPtr->update();
	bUIPtr->update();

	//�� Ŭ���� ������Ʈ
	bEnemyMPtr->update(playerPtr->getX(), playerPtr->getY());

	//�� Ŭ���� ������Ʈ
	for (UINT i = 0; i < bPetPtrV.size(); i++)
	{
		bPetPtrV[i]->update();
	}

	//���̺� ����Ʈ ������Ʈ
	bSaveMPtr->update();

	//�������� Ŭ���� ������Ʈ
	for (UINT i = 0; i < bTreasurePtrV.size(); i++)
	{
		bTreasurePtrV[i]->update();
	}


	//ī�޶� ������Ʈ
	CAMERA.cameraFollow(playerPtr->getX(), playerPtr->getY());

	//ī�޶� ����
	CAMERA.cameraRevision(0, 0, 1366, 768);
	CAMERA.cameraRevision(1367, 0, 4069, 768);
	CAMERA.cameraRevision(4070, 0, 5436, 1422);
	CAMERA.cameraRevision(5436, 654, 6802, 2256);
	CAMERA.cameraRevision(6804, 851, 8170, 2144);
	CAMERA.cameraRevision(8171, 735, 9537, 1503);
	CAMERA.cameraRevision(8171, 1504, 9537, 2436);
	CAMERA.cameraRevision(9538, 1668, 10904, 2436);

	//����̹��� ����
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

//=============����=============
void BossStageClass::render(void)
{
	//�������� ��� �̹��� ����
	RECT bgRc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("�������1", getMemDC(), &bgRc, loopX1, loopY1);
	IMAGEMANAGER->loopRender("�������3", getMemDC(), &bgRc, loopX3, loopY3);
	IMAGEMANAGER->loopRender("�������2", getMemDC(), &bgRc, loopX2, loopY2);
	//if (CAMERA.getCRc().left >= 4070 && CAMERA.getCRc().left < 9538)
	//{
	//	IMAGEMANAGER->loopRender("�������4", getMemDC(), &bgRc, loopX4, loopY4);
	//}

	BossStageImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);
	
	fieldPtr->render();

	bUIPtr->render();

	//�������� Ŭ���� ����
	for (UINT i = 0; i < bTreasurePtrV.size(); i++)
	{
		bTreasurePtrV[i]->render();
	}

	//���̺� ����Ʈ Ŭ���� ����
	bSaveMPtr->render();

	//�� Ŭ���� ����
	bEnemyMPtr->render();

	//�� Ŭ���� ����
	for (UINT i = 0; i < bPetPtrV.size(); i++)
	{
		bPetPtrV[i]->render();
	}
	
	//�÷��̾� Ŭ���� ����
	playerPtr->render();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		BossCollisionImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);
	}

	/*��ǥ Ȯ�ο�*/
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOutfloat(getMemDC(), 10, 10, "���콺 X", _ptMouse.x + CAMERA.getCRc().left);
	TextOutfloat(getMemDC(), 10, 30, "���콺 Y", _ptMouse.y + CAMERA.getCRc().top);
	TextOutfloat(getMemDC(), 10, 50, "ī�޶� left", CAMERA.getCRc().left);
}
