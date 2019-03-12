#include "stdafx.h"
#include "BossClass.h"
#include "PlayerClass.h"

//=============초기화=============
HRESULT BossClass::init(void)
{
	BossMoveImg = IMAGEMANAGER->findImage("boss-걷기");
	BossAttack1Img = IMAGEMANAGER->findImage("boss-공격1");
	BossAttack2Img = IMAGEMANAGER->findImage("boss-공격2");
	BossDieImg = IMAGEMANAGER->findImage("boss-죽음");

	bSpeed = 1.f;
	bGravity = 0;
	bossX = bossY = 0;

	isRight = false;
	isMove = false;
	isAttak = false;

	return S_OK;
}
//=============해제=============
void BossClass::release(void)
{
}
//=============업데이트=============
void BossClass::update(float _playerX)
{
	if (bossX > _playerX)
	{
		isRight = false;
		bossX -= bSpeed;
	}
	else if (bossX < _playerX)
	{
		isRight = true;
		bossX += bSpeed;
	}

	BossRc = RectMakeCenter(bossX, bossY, 240, 165);
}
//=============렌더=============
void BossClass::render(void)
{

}
