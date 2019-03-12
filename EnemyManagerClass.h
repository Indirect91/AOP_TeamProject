#pragma once
#include "gameNode.h"

class EnemyManagerClass : public gameNode
{
	class flyOctopus* eEnemy1;				//떠다니는 문어
	float eEnemy1X, eEnemy1Y;				//떠다니는 문어 좌표
	vector<class flyOctopus*> eEnemy1V;		//떠다니는 문어를 담는 벡터

	class crawlBug* eEnemy2;				//기어다니는 벌레
	float eEnemy2X, eEnemy2Y;				//기어다니는 벌레 좌표
	vector<class crawlBug*> eEnemy2V;		//기어다니는 벌레 담는 벡터

	class flyCrystal* eEnemy3;				//날아다니는 크리스탈
	float eEnemy3X, eEnemy3Y;				//날아다니는 크리스탈 좌표
	vector<class flyCrystal*> eEnemy3V;		//날앋니는 크리스탈 담는 벡터

	class flyGhost* eEnemy4;				//둥둥이 유령
	float eEnemy4X, eEnemy4Y;				//둥둥이 유령 좌표
	vector<class flyGhost*> eEnemy4V;		//둥둥이 유령 담는 벡터

	class bullet* eBullet;					//둥둥이가 쏠 총알
	vector<class bullet*> eBulletV;			//둥둥이가 쏠 총알을 담는 벡터

	//둥둥이가 쏠때 필요한것
	float eAngle;							//에너미 매니저에 있는 각도
	int eCount;								//에너미 매니저에 있는 총알 자동으로 발사할 카운트
	string collisionS;					//총알이랑 픽셀 충돌할 스테이지가 어딘지 입력하기위해

public:
	enum tagWhereStage
	{
		stage1 = 1,
		bossStage
	};

	HRESULT init(tagWhereStage _whereStage);
	void release(void);
	void update(float _ePlayerX, float _ePlayerY);
	void render(void);

	vector<class flyOctopus*> getEEnemy1V() { return eEnemy1V; }
	vector<class crawlBug*> getEEnemy2V() { return eEnemy2V; }
	vector<class flyCrystal*> getEEnemy3V() { return eEnemy3V; }
	vector<class flyGhost*> getEEnemy4V() { return eEnemy4V; }

	vector<class bullet*>& getEBullet() { return eBulletV; }

	EnemyManagerClass() {}
	~EnemyManagerClass() {}
};

