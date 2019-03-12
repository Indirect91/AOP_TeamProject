#include "stdafx.h"
#include "EnemyManagerClass.h"
#include "EnemyClass.h"
#include "bullet.h"

//=============초기화=============
HRESULT EnemyManagerClass::init(tagWhereStage _whereStage)
{
	switch (_whereStage)
	{
	case EnemyManagerClass::stage1:
		collisionS = "Stage1Collision";
		//떠다니는 문어
		eEnemy1 = new flyOctopus;
		eEnemy1->init(1844, 582);
		eEnemy1V.push_back(eEnemy1);

		eEnemy1 = new flyOctopus;
		eEnemy1->init(1959, 483);
		eEnemy1V.push_back(eEnemy1);

		//기어다니는 벌레
		eEnemy2 = new crawlBug;
		eEnemy2->init(946, 630, 794, 1082);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(1289, 545, 1158, 1409);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(2455, 630, 2000, 2600);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(5618, 501, 5538, 5695);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(7127, 586, 7029, 7194);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(7166, 1570, 7122, 7273);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(7500, 1228, 7416, 7607);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(13813, 677, 13666, 13898);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(14064, 326, 13916, 14150);
		eEnemy2V.push_back(eEnemy2);

		//날아다니는 크리스탈
		eEnemy3 = new flyCrystal;
		eEnemy3->init(7218, 2170, 7156, 7283);
		eEnemy3V.push_back(eEnemy3);

		eEnemy3 = new flyCrystal;
		eEnemy3->init(8934, 640, 8846, 9096);
		eEnemy3V.push_back(eEnemy3);

		eEnemy3 = new flyCrystal;
		eEnemy3->init(10112, 630, 9880, 10320);
		eEnemy3V.push_back(eEnemy3);

		eEnemy3 = new flyCrystal;
		eEnemy3->init(15539, 458, 0, 0);
		eEnemy3V.push_back(eEnemy3);

		break;

	case EnemyManagerClass::bossStage:
		collisionS = "BossStageCollision";
		//떠다니는 문어
		eEnemy1 = new flyOctopus;
		eEnemy1->init(4414, 480);
		eEnemy1V.push_back(eEnemy1);

		eEnemy1 = new flyOctopus;
		eEnemy1->init(4664, 480);
		eEnemy1V.push_back(eEnemy1);

		//기어다니는 벌레
		eEnemy2 = new crawlBug;
		eEnemy2->init(3197, 629, 2991, 3413);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(4855, 1229, 4744, 4997);
		eEnemy2V.push_back(eEnemy2);

		eEnemy2 = new crawlBug;
		eEnemy2->init(5148, 1314, 5078, 5332);
		eEnemy2V.push_back(eEnemy2);

		//크리스탈
		eEnemy3 = new flyCrystal;
		eEnemy3->init(1858, 645, 0, 0);
		eEnemy3V.push_back(eEnemy3);

		eEnemy3 = new flyCrystal;
		eEnemy3->init(2557, 598, 2404, 2756);
		eEnemy3V.push_back(eEnemy3);

		eEnemy3 = new flyCrystal;
		eEnemy3->init(6082, 1222, 0, 0);
		eEnemy3V.push_back(eEnemy3);

		eEnemy3 = new flyCrystal;
		eEnemy3->init(7273, 2010, 7141, 7673);
		eEnemy3V.push_back(eEnemy3);

		eEnemy3 = new flyCrystal;
		eEnemy3->init(9336, 1358, 9266, 9376);
		eEnemy3V.push_back(eEnemy3);

		//둥둥이 유령으로 바꿔주기
		eEnemy4 = new flyGhost;
		eEnemy4->init(4603, 1073);
		eEnemy4V.push_back(eEnemy4);

		eEnemy4 = new flyGhost;
		eEnemy4->init(5843, 1017);
		eEnemy4V.push_back(eEnemy4);

		break;
	}

	if (eEnemy4V.size() > 0)
	{
		//둥둥이가 쏘는 총알
		for (UINT i = 0; i < eEnemy4V.size(); i++)
		{
			eBullet = new bullet;
			eBullet->init("총알", 1, 400);
			eBulletV.push_back(eBullet);
		}

		eAngle = 0;
		eCount = 0;
	}

	return S_OK;
}

//=============해제=============
void EnemyManagerClass::release(void)
{
	for (UINT i = 0; i < eEnemy1V.size(); i++)
	{
		eEnemy1V[i]->release();
		SAFE_DELETE(eEnemy1V[i]);
	}

	for (UINT i = 0; i < eEnemy2V.size(); i++)
	{
		eEnemy2V[i]->release();
		SAFE_DELETE(eEnemy2V[i]);
	}

	for (UINT i = 0; i < eEnemy3V.size(); i++)
	{
		eEnemy3V[i]->release();
		SAFE_DELETE(eEnemy3V[i]);
	}

	for (UINT i = 0; i < eEnemy4V.size(); i++)
	{
		eEnemy4V[i]->release();
		SAFE_DELETE(eEnemy4V[i]);
	}

	for (UINT i = 0; i < eBulletV.size(); i++)
	{
		eBulletV[i]->release();
		SAFE_DELETE(eBulletV[i]);
	}
}

//=============업데이트=============
void EnemyManagerClass::update(float _ePlayerX, float _ePlayerY)
{
	for (UINT i = 0; i < eEnemy1V.size(); i++)
	{
		eEnemy1V[i]->update();
	}

	for (UINT i = 0; i < eEnemy2V.size(); i++)
	{
		eEnemy2V[i]->update();
	}

	for (UINT i = 0; i < eEnemy3V.size(); i++)
	{
		eEnemy3V[i]->update();
	}

	for (UINT i = 0; i < eEnemy4V.size(); i++)
	{
		eEnemy4V[i]->update();
	}

	eCount++;
	if (eCount % 60 == 0)
	{
		for (UINT i = 0; i < eBulletV.size(); i++)
		{
			if (eEnemy4V[i]->getIsDie() == true) continue;

			eAngle = GetAngle(eEnemy4V[i]->getEnemyX(), eEnemy4V[i]->getEnemyY(), _ePlayerX, _ePlayerY);
			eBulletV[i]->fire(eEnemy4V[i]->getEnemyX(), eEnemy4V[i]->getEnemyY(), eAngle, 3.f);
		}
	}

	for (UINT i = 0; i < eBulletV.size(); i++)
	{
		eBulletV[i]->update();

		//바닥충돌
		COLORREF colorB = GetPixel(IMAGEMANAGER->findImage(collisionS)->getMemDC(), eBulletV[i]->getVBullet()[0].x, eBulletV[i]->getVBullet()[0].y);
		int rB = GetRValue(colorB);
		int gB = GetGValue(colorB);
		int bB = GetBValue(colorB);

		if (rB == 255 && gB == 255 && bB == 0)
		{
			eBulletV[i]->getVBullet()[0].fire = false;
		}
		else if (rB == 0 && gB == 255 && bB == 0)
		{
			eBulletV[i]->getVBullet()[0].fire = false;
		}
		else if (rB == 0 && gB == 0 && bB == 255)
		{
			eBulletV[i]->getVBullet()[0].fire = false;
		}
	}


}

//=============렌더=============
void EnemyManagerClass::render(void)
{
	for (UINT i = 0; i < eEnemy1V.size(); i++)
	{
		eEnemy1V[i]->render();
	}

	for (UINT i = 0; i < eEnemy2V.size(); i++)
	{
		eEnemy2V[i]->render();
	}

	for (UINT i = 0; i < eEnemy3V.size(); i++)
	{
		eEnemy3V[i]->render();
	}

	for (UINT i = 0; i < eEnemy4V.size(); i++)
	{
		eEnemy4V[i]->render();
	}

	for (UINT i = 0; i < eBulletV.size(); i++)
	{
		eBulletV[i]->render();
	}
}
