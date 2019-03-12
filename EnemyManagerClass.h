#pragma once
#include "gameNode.h"

class EnemyManagerClass : public gameNode
{
	class flyOctopus* eEnemy1;				//���ٴϴ� ����
	float eEnemy1X, eEnemy1Y;				//���ٴϴ� ���� ��ǥ
	vector<class flyOctopus*> eEnemy1V;		//���ٴϴ� ��� ��� ����

	class crawlBug* eEnemy2;				//���ٴϴ� ����
	float eEnemy2X, eEnemy2Y;				//���ٴϴ� ���� ��ǥ
	vector<class crawlBug*> eEnemy2V;		//���ٴϴ� ���� ��� ����

	class flyCrystal* eEnemy3;				//���ƴٴϴ� ũ����Ż
	float eEnemy3X, eEnemy3Y;				//���ƴٴϴ� ũ����Ż ��ǥ
	vector<class flyCrystal*> eEnemy3V;		//���Ҵϴ� ũ����Ż ��� ����

	class flyGhost* eEnemy4;				//�յ��� ����
	float eEnemy4X, eEnemy4Y;				//�յ��� ���� ��ǥ
	vector<class flyGhost*> eEnemy4V;		//�յ��� ���� ��� ����

	class bullet* eBullet;					//�յ��̰� �� �Ѿ�
	vector<class bullet*> eBulletV;			//�յ��̰� �� �Ѿ��� ��� ����

	//�յ��̰� �� �ʿ��Ѱ�
	float eAngle;							//���ʹ� �Ŵ����� �ִ� ����
	int eCount;								//���ʹ� �Ŵ����� �ִ� �Ѿ� �ڵ����� �߻��� ī��Ʈ
	string collisionS;					//�Ѿ��̶� �ȼ� �浹�� ���������� ����� �Է��ϱ�����

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

