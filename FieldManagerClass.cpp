#include "stdafx.h"
#include "FieldManagerClass.h"
#include "ThorntrapClass.h"
#include "BreakTileClass.h"
#include "PlayerClass.h"
HRESULT FieldManagerClass::init(string stage)
{
	thornPtr = new ThorntrapClass;
	if (stage == "Stage1")
	{
		thornPtr->init(ThorntrapClass::stageNumber::Stage1);
	}
	else if (stage == "BossStage")
	{
		thornPtr->init(ThorntrapClass::stageNumber::BossStage);
	}

	breakTilePtr = new BreakTileClass;
	if (stage == "Stage1")
	{
		breakTilePtr->init(BreakTileClass::BreakTile::Stage1);
	}
	else if (stage == "BossStage")
	{
		breakTilePtr->init(BreakTileClass::BreakTile::BossStage);
	}

	breakTilePtr->setPlayer(playerPtr);


	return S_OK;
}

void FieldManagerClass::release(void)
{
	thornPtr->release();
	breakTilePtr->release();
}

void FieldManagerClass::update(void)
{
	thornPtr->update();
	breakTilePtr->update(playerPtr);
}

void FieldManagerClass::render(void)
{
	thornPtr->render();
	breakTilePtr->render();
}
