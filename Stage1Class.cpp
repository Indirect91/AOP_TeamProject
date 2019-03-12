#include "stdafx.h"
#include "Stage1Class.h"
#include "PlayerClass.h"
#include "UIClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"

//=============�ʱ�ȭ=============
HRESULT Stage1Class::init(void)
{
	//�������� 1 �̹���
	stage1Img = IMAGEMANAGER->findImage("Stage1");
	stage1CollisionImg = IMAGEMANAGER->findImage("Stage1Collision");

	//�������� 1 ��� �̹���
	IMAGEMANAGER->findImage("�������1");
	loopX1 = loopY1 = 0;
	IMAGEMANAGER->findImage("�������2");
	loopX2 = loopY2 = 0;
	IMAGEMANAGER->findImage("�������3");
	loopX3 = loopY3 = 0;
	IMAGEMANAGER->findImage("�������4");
	loopX4 = loopY4 = 0;

	//UI Ŭ���� ���� �� �ʱ�ȭ
	s1UIPtr = new UIClass;
	s1UIPtr->init("Stage1");

	//�÷��̾� Ŭ���� ���� �� �ʱ�ȭ
	playerPtr = new PlayerClass;
	playerPtr->init(100,400,"Stage1Collision");

	//�ʵ� Ŭ���� ���� �� �ʱ�ȭ
	fieldPtr = new FieldManagerClass;
	fieldPtr->init("Stage1");

	//���ʹ� �Ŵ��� Ŭ���� ���� �� �ʱ�ȭ
	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(EnemyManagerClass::tagWhereStage::stage1);

	//�� ���� �� �ʱ�ȭ
	//����
	s1PetPtr = new PetsClass;
	s1PetPtr->init(PetsClass::PetsTypes::bat, 7748, 1705);
	s1PetPtrV.push_back(s1PetPtr);

	//����
	s1PetPtr = new PetsClass;
	s1PetPtr->init(PetsClass::PetsTypes::seal, 3317, 607);
	s1PetPtrV.push_back(s1PetPtr);

	//���
	s1PetPtr = new PetsClass;
	s1PetPtr->init(PetsClass::PetsTypes::shark, 13712, 249);
	s1PetPtrV.push_back(s1PetPtr);

	//���̺� ����Ʈ Ŭ���� ���� �� �ʱ�ȭ
	s1SaveMPtr = new savePoint;
	s1SaveMPtr->init(9393, 365);

	//Ŭ���� ����Ʈ Ŭ���� ���� �� �ʱ�ȭ
	s1ClearMPtr = new clearPoint;
	s1ClearMPtr->init(17150, 362);

	//�������� Ŭ���� ���� �� �ʱ�ȭ
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

//=============����=============
void Stage1Class::release(void)
{
	//���� Ŭ������ new �Ҵ������ ������ ���� ����
	playerPtr->release();
	SAFE_DELETE(playerPtr);

	fieldPtr->release();
	SAFE_DELETE(fieldPtr);

	//���ʹ� ����
	s1EnemyMPtr->release();

	//UI Ŭ���� ����
	s1UIPtr->release();
	SAFE_DELETE(s1UIPtr);

	//�� ����
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->release();
		SAFE_DELETE(s1PetPtrV[i]);
	}

	//���̺� ����Ʈ ����
	s1SaveMPtr->release();
	SAFE_DELETE(s1SaveMPtr);
	
	//Ŭ���� ����Ʈ Ŭ���� ����
	s1ClearMPtr->release();
	SAFE_DELETE(s1ClearMPtr);

	//��������
	for (int i = 0; i < s1TreasurePtrV.size(); i++)
	{
		s1TreasurePtrV[i]->release();
		SAFE_DELETE(s1TreasurePtrV[i])
	}

}

//=============������Ʈ=============
void Stage1Class::update(void)
{
	playerPtr->update();

	//UI ������Ʈ
	s1UIPtr->update();

	//���ʹ� ������Ʈ
	if (playerPtr->getChangeCount() == 0)
	{
		s1EnemyMPtr->update(playerPtr->getX(), playerPtr->getY());

		//�� ������Ʈ
		for (int i = 0; i < s1PetPtrV.size(); i++)
		{
			s1PetPtrV[i]->update();
		}
		fieldPtr->update("Stage1");
	}
	//���̺� ������ ������Ʈ
	s1SaveMPtr->update();
	//Ŭ���� ������ ������Ʈ
	s1ClearMPtr->update();
	
	//�������� ������Ʈ
	for (int i = 0; i < s1TreasurePtrV.size(); i++)
	{
		s1TreasurePtrV[i]->update();
	}

	//ī�޶� �ޱ��� �÷��̾�� ��
	CAMERA.cameraFollow(playerPtr->getX(), playerPtr->getY());

	//�Ϲݷ�Ʈ
	CAMERA.cameraRevision(0, 0, 2647, WINSIZEY);
	CAMERA.cameraRevision(2647, 0, 4013, WINSIZEY);
	CAMERA.cameraRevision(4014, 0, 5380, 2436);
	CAMERA.cameraRevision(5381, 1668, 6747, 2436);
	CAMERA.cameraRevision(6748, 0, 8114, 2436);
	CAMERA.cameraRevision(8115, 0, 10990, WINSIZEY);
	CAMERA.cameraRevision(10991, 0, 13212, WINSIZEY);
	CAMERA.cameraRevision(13213, 0, 14579, WINSIZEY);
	CAMERA.cameraRevision(14580, 0, 17520, WINSIZEY);

	//������Ʈ
	//���� �� ���ڰ��� ��
	CAMERA.cameraRevision(5381, 0, 6747, WINSIZEY);

	//����̹��� ����
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

//=============����=============
void Stage1Class::render(void)
{
	//�������� ��� �̹��� ����
	RECT bgRc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("�������1", getMemDC(), &bgRc, loopX1, loopY1);
	IMAGEMANAGER->loopRender("�������3", getMemDC(), &bgRc, loopX3, loopY3);
	IMAGEMANAGER->loopRender("�������2", getMemDC(), &bgRc, loopX2, loopY2);
	if (CAMERA.getCRc().left >= 4014 && CAMERA.getCRc().left < 8114)
	{
		IMAGEMANAGER->loopRender("�������4", getMemDC(), &bgRc, loopX4, loopY4);
	}

	//�������� �̹��� ����
	stage1Img->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);

	//�ȼ��浹�� �̹��� �� ���Ű
	if (KEYMANAGER->isToggleKey('W'))
	{
		stage1CollisionImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);
	}

	//�÷��̾� Ŭ���� ����
	playerPtr->render();

	//UI Ŭ���� ����
	s1UIPtr->render();

	//���̺� ����Ʈ ����
	s1SaveMPtr->render();
	//Ŭ���� ����Ʈ ����
	s1ClearMPtr->render();
	
	//�������� ����
	for (int i = 0; i < s1TreasurePtrV.size(); i++)
	{
		s1TreasurePtrV[i]->render();
	}

	//���ʹ� ����
	s1EnemyMPtr->render();
	//�� ����
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->render();
	}

	fieldPtr->render("Stage1");

	/*��ǥ Ȯ�ο�*/
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOutfloat(getMemDC(), 10, 10, "���콺 X", _ptMouse.x + CAMERA.getCRc().left);
	TextOutfloat(getMemDC(), 10, 30, "���콺 Y", _ptMouse.y + CAMERA.getCRc().top);
	TextOutfloat(getMemDC(), 10, 50, "ī�޶� left", CAMERA.getCRc().left);
}
