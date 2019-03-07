#pragma once
#include "gameNode.h"

class EnemyManagerClass : public gameNode
{
	class flyOctopus* eEnemy1;
	class crawlBug* eEnemy2;
	class flyCrystal* eEnemy3;

public:
	enum EnemyKind
	{
		octopus = 1,	//떠다니는 문어
		bug,			//기어다니는 벌레
		crystal			//날아다니는 크리스탈
	};
	EnemyKind whichEnemy;		//어떤 몬스터를 선택했는지 알려줄 변수

	HRESULT init(EnemyKind _which, int _x, int _y, int _scaleLeftX, int _scaleRightX);
	void release(void);
	void update(void);
	void render(void);

	flyOctopus* getEEnemy1() { return eEnemy1; }
	crawlBug* getEEnemy2() { return eEnemy2; }
	flyCrystal* getEEnemy3() { return eEnemy3; }

	EnemyKind getWhichEnemy() { return whichEnemy; }

	EnemyManagerClass() {}
	~EnemyManagerClass() {}
};

