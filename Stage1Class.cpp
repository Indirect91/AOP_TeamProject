#include "stdafx.h"
#include "Stage1Class.h"
#include "PlayerClass.h"
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

	//�÷��̾� Ŭ���� ���� �� �ʱ�ȭ
	playerPtr = new PlayerClass;
	playerPtr->init();

	//�ʵ� Ŭ���� ���� �� �ʱ�ȭ
	fieldPtr = new FieldManagerClass;
	fieldPtr->init("Stage1");

	//���ʹ� �Ŵ��� ���� �� �ʱ�ȭ -> �� �κп� ���ڰ��� �־� ������ �ʱ�ȭ ���ָ� ��
#pragma region ���ʹ�
	//1. ������ ����
	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(1, 1844, 575, 0, 0);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(1, 1959, 483, 0, 0);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	//2. ���ٴϴ� �ֹ���
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

	//3.���ƴٴϴ� ũ����Ż
	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(3, 7218, 2170, 7156, 7283);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(3, 8934, 640, 8846, 9096);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

	s1EnemyMPtr = new EnemyManagerClass;
	s1EnemyMPtr->init(3, 10112, 630, 9880, 10320);
	s1EnemyMPtrV.push_back(s1EnemyMPtr);

#pragma endregion ���ʹ�

	//�� ���� �� �ʱ�ȭ
	//����
	s1PetPtr = new PetsClass;
	s1PetPtr->init(1, 7748, 1705);
	s1PetPtrV.push_back(s1PetPtr);

	//����
	s1PetPtr = new PetsClass;
	s1PetPtr->init(2, 3317, 607);
	s1PetPtrV.push_back(s1PetPtr);

	//���
	s1PetPtr = new PetsClass;
	s1PetPtr->init(3, 13712, 249);
	s1PetPtrV.push_back(s1PetPtr);

	//���̺� ����Ʈ Ŭ���� ���� �� �ʱ�ȭ
	s1SaveMPtr = new savePoint;
	s1SaveMPtr->init(9393, 365);
	s1SaveMPtrV.push_back(s1SaveMPtr);

	//�������� Ŭ���� ���� �� �ʱ�ȭ
	s1TreasurePtr = new treasureBox;
	s1TreasurePtr->init(WINSIZEX / 2, 500, true);
	s1TreasurePtrV.push_back(s1TreasurePtr);

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
	for (int i = 0; i < s1EnemyMPtrV.size(); i++)
	{
		s1EnemyMPtrV[i]->release();
		SAFE_DELETE(s1EnemyMPtrV[i]);
	}

	//�� ����
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->release();
		SAFE_DELETE(s1PetPtrV[i]);
	}

	//���̺� ����Ʈ ����
	for (int i = 0; i < s1SaveMPtrV.size(); i++)
	{
		s1SaveMPtrV[i]->release();
		SAFE_DELETE(s1SaveMPtrV[i]);
	}

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

	//���ʹ� ������Ʈ
	for (int i = 0; i < s1EnemyMPtrV.size(); i++)
	{
		s1EnemyMPtrV[i]->update();
	}

	//�� ������Ʈ
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->update();
	}

	fieldPtr->update();

	//���̺� ������ ������Ʈ
	for (int i = 0; i < s1SaveMPtrV.size(); i++)
	{
		s1SaveMPtrV[i]->update();
	}
	
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
	CAMERA.cameraRevision(13213, 0, 15770, WINSIZEY);
	CAMERA.cameraRevision(15771, 0, 17520, WINSIZEY);

	//������Ʈ
	//���� �� ���ڰ��� ��
	CAMERA.cameraRevision(5381, 0, 6747, WINSIZEY);

	//����̹��� ����
	loopX1 = CAMERA.getCRc().left / 5;
	loopX2 = CAMERA.getCRc().left / 2;
	loopX3 = CAMERA.getCRc().left / 3;
	loopX4 = CAMERA.getCRc().left / 2;
	loopY4 = CAMERA.getCRc().top / 2;

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

	//���̺� ����Ʈ ����
	for (int i = 0; i < s1SaveMPtrV.size(); i++)
	{
		s1SaveMPtrV[i]->render();
	}
	//�������� ����
	for (int i = 0; i < s1TreasurePtrV.size(); i++)
	{
		s1TreasurePtrV[i]->render();
	}

	//���ʹ� ����
	for (int i = 0; i < s1EnemyMPtrV.size(); i++)
	{
		s1EnemyMPtrV[i]->render();
	}
	//�� ����
	for (int i = 0; i < s1PetPtrV.size(); i++)
	{
		s1PetPtrV[i]->render();
	}

	fieldPtr->render();

	/*��ǥ Ȯ�ο�*/
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOutfloat(getMemDC(), 10, 10, "���콺 X", _ptMouse.x + CAMERA.getCRc().left);
	TextOutfloat(getMemDC(), 10, 30, "���콺 Y", _ptMouse.y + CAMERA.getCRc().top);
	TextOutfloat(getMemDC(), 10, 50, "ī�޶� left", CAMERA.getCRc().left);

}
