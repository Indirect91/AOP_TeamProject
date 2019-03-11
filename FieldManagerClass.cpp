#include "stdafx.h"
#include "FieldManagerClass.h"
#include "PlayerClass.h"
#include "FlowerClass.h"
#include "UniClass.h"
HRESULT FieldManagerClass::init(string stage)
{
	//�������� Ŭ���� �Ҵ�
	thornPtr = new ThorntrapClass;
	if (stage == "Stage1")
	{
		thornPtr->init(ThorntrapClass::stageNumber::Stage1);
	}
	else if (stage == "BossStage")
	{
		thornPtr->init(ThorntrapClass::stageNumber::BossStage);
	}

	//��������Ÿ�� Ŭ���� �Ҵ�
	breakTilePtr = new BreakTileClass;
	if (stage == "Stage1")
	{
		breakTilePtr->init(BreakTileClass::BreakTile::Stage1);
	}
	else if (stage == "BossStage")
	{
		breakTilePtr->init(BreakTileClass::BreakTile::BossStage);
	}

	//�����ϸ� ������ Ÿ�� Ŭ���� �Ҵ�
	hideTilePtr = new HideTileClass;
	if (stage == "Stage1")
	{
		hideTilePtr->init(HideTileClass::HideTile::Stage1);
	}
	else if (stage == "BossStage")
	{
		hideTilePtr->init(HideTileClass::HideTile::BossStage);
	}

	//�ɿ��� ���̾ ������ Ÿ�� Ŭ���� �Ҵ�
	flowerPtr = new FlowerClass;
	if (stage == "Stage1")
	{
		flowerPtr->init(FlowerClass::FlowerTile::Stage1);
	}
	else if (stage == "BossStage")
	{
		flowerPtr->init(FlowerClass::FlowerTile::BossStage);
	}

	uniPtr = new UniClass;
	if (stage == "Stage1")
	{
		uniPtr->init(UniClass::Jumpstate::Stage1);
	}
	else if (stage == "BossStage")
	{
		uniPtr->init(UniClass::Jumpstate::BossStage);
	}

	hideTilePtr->setPlayer(playerPtr);
	breakTilePtr->setPlayer(playerPtr);
	flowerPtr->setPlayer(playerPtr);


	return S_OK;
}

void FieldManagerClass::release(void)
{
	thornPtr->release();
	breakTilePtr->release();
	hideTilePtr->release();
	flowerPtr->release();
	uniPtr->release();
}

void FieldManagerClass::update(string stage)
{
	thornPtr->update();
	hideTilePtr->update();
	flowerPtr->update();
	breakTilePtr->update();
	uniPtr->update();
}

void FieldManagerClass::render(string stage)
{
	thornPtr->render();
	breakTilePtr->render();
	hideTilePtr->render();
	flowerPtr->render();
	uniPtr->render();

}
