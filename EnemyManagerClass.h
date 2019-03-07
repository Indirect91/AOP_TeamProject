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
		octopus = 1,	//���ٴϴ� ����
		bug,			//���ٴϴ� ����
		crystal			//���ƴٴϴ� ũ����Ż
	};
	EnemyKind whichEnemy;		//� ���͸� �����ߴ��� �˷��� ����

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

