#pragma once
#include "gameNode.h"

class EnemyManagerClass : public gameNode
{
	enum EnemyKind
	{
		octopus = 1,	//���ٴϴ� ����
		bug,			//���ٴϴ� ����
		crystal			//���ƴٴϴ� ũ����Ż
	};

	class flyOctopus* eEnemy1;
	class crawlBug* eEnemy2;
	class flyCrystal* eEnemy3;

	int whichEnemy;		//� ���͸� �����ߴ��� �˷��� ����

public:
	HRESULT init(int _which, int _x, int _y, int _scaleLeftX, int _scaleRightX);
	void release(void);
	void update(void);
	void render(void);

	EnemyManagerClass() {}
	~EnemyManagerClass() {}
};

