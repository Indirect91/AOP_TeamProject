#include "stdafx.h"
#include "EnemyManagerClass.h"
#include "EnemyClass.h"

//=============�ʱ�ȭ=============
//�ȿ����̴� �༮�� �����Ͽ� 0,0�� ����
HRESULT EnemyManagerClass::init(int _which, int _x, int _y, int _scaleLeftX, int _scaleRightX)
{
	whichEnemy = _which;

	switch (_which)
	{
	case octopus:
		eEnemy1 = new flyOctopus;
		eEnemy1->init();
		eEnemy1->setEnemyX(_x);
		eEnemy1->setEnemyY(_y);
		break;

	case bug:
		eEnemy2 = new crawlBug;
		eEnemy2->init();
		eEnemy2->setEnemyX(_x);
		eEnemy2->setEnemyY(_y);
		eEnemy2->setScaleLeftX(_scaleLeftX);
		eEnemy2->setScaleRightX(_scaleRightX);
		break;

	case crystal:
		eEnemy3 = new flyCrystal;
		eEnemy3->init();
		eEnemy3->setEnemyX(_x);
		eEnemy3->setEnemyY(_y);
		eEnemy3->setScaleLeftX(_scaleLeftX);
		eEnemy3->setScaleRightX(_scaleRightX);
		break;
	}

	return S_OK;
}

//=============����=============
void EnemyManagerClass::release(void)
{
	switch (whichEnemy)
	{
	case octopus:
		eEnemy1->release();
		SAFE_DELETE(eEnemy1);
		break;

	case bug:
		eEnemy2->release();
		SAFE_DELETE(eEnemy2);
		break;

	case crystal:
		eEnemy3->release();
		SAFE_DELETE(eEnemy3);
		break;
	}
}

//=============������Ʈ=============
void EnemyManagerClass::update(void)
{
	switch (whichEnemy)
	{
	case octopus:
		eEnemy1->update();
		break;

	case bug:
		eEnemy2->update();
		break;

	case crystal:
		eEnemy3->update();
		break;
	}
}

//=============����=============
void EnemyManagerClass::render(void)
{
	switch (whichEnemy)
	{
	case octopus:
		eEnemy1->render();
		break;

	case bug:
		eEnemy2->render();
		break;

	case crystal:
		eEnemy3->render();
		break;
	}
}

