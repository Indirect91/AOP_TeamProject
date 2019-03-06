#pragma once
#include "FieldManagerClass.h"


class ThorntrapClass : public FieldManagerClass
{

public:
	enum class stageNumber
	{
		Stage1 = 0,
		BossStage
	};

private:
	//스테이지 1번
	RECT ThornOne;
	RECT ThornTwo;
	RECT ThornThree;
	RECT ThornFour;
	RECT ThornFive;
	vector<RECT>ThornList;
	//보스 스테이지

public:

	HRESULT init(stageNumber Stage);
	void release(void);
	void update(void);
	void render(void);


	ThorntrapClass() {}
	~ThorntrapClass() {}
};

