#include "stdafx.h"
#include "BossClass.h"
#include "PlayerClass.h"

//=============�ʱ�ȭ=============
HRESULT BossClass::init(void)
{
	BossMoveImg = IMAGEMANAGER->findImage("boss-�ȱ�");
	BossAttack1Img = IMAGEMANAGER->findImage("boss-����1");
	BossAttack2Img = IMAGEMANAGER->findImage("boss-����2");
	BossDieImg = IMAGEMANAGER->findImage("boss-����");

	bSpeed = 1.f;
	bGravity = 0;
	bossX = bossY = 0;

	isRight = false;
	isMove = false;
	isAttak = false;

	return S_OK;
}
//=============����=============
void BossClass::release(void)
{
}
//=============������Ʈ=============
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
//=============����=============
void BossClass::render(void)
{

}
