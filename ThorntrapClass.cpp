#include "stdafx.h"
#include "ThorntrapClass.h"


HRESULT ThorntrapClass::init(stageNumber Stage)
{

	switch (Stage)
	{
	case stageNumber::Stage1:
		//스테이지 1번 렉트
		ThornOne = RectMake(2987, 754, 141, 22);
		ThornTwo = RectMake(3502, 754, 139, 23);
		ThornThree = RectMake(5979, 624, 267, 21);
		ThornFour = RectMake(11146, 669, 137, 17);
		ThornFive = RectMake(11580, 668, 173, 22);
		//스테이지 1번 벡터
		ThornList.push_back(ThornOne);
		ThornList.push_back(ThornTwo);
		ThornList.push_back(ThornThree);
		ThornList.push_back(ThornFour);
		ThornList.push_back(ThornFive);
		break;

	case stageNumber::BossStage:
		break;
	default:
		break;
	}


	//보스스테이지 렉트


	return S_OK;
}

void ThorntrapClass::release(void)
{
}

void ThorntrapClass::update(void)
{
}

void ThorntrapClass::render(void)
{
	//스테이지 1번 랜더
	for (int i = 0; i < ThornList.size(); i++)
	{
		Rectangle(getMemDC(), RelativeCameraRect(ThornList[i]));
	}
	//보스스테이지 렌더
}
