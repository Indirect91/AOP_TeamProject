#pragma once
#include "gameNode.h"

class BossClass : public gameNode
{
	enum hahahaha
	{
		a,
		b,
		c
	};

	enum DOLTAN
	{
		stupid,
		smartALittle,
		lol
	};

	RECT BossRc;						//���� ��Ʈ
	RECT bossAttackRc;					//���� ���� ��Ʈ
	float bSpeed;						//���� �ӵ�
	float bGravity;						//���� �߷�
	float bossX, bossY;						//���� �߽���ǥ
	bool isRight;						//������ �������ΰ�?
	bool isMove;						//������ �����̴°�?
	bool isAttak;						//������ �����ϴ°�?

	image* BossMoveImg;					//������ �����̴� �̹���
	image* BossAttack1Img;				//������ �����ϴ� �̹���1
	image* BossAttack2Img;				//������ �����ϴ� �̹���2
	image* BossDieImg;					//������ �״� �̹���

	//class PlayerClass* bPlayerPtr;		//���� Ŭ������ �ִ� �÷��̾� ������

public:
	HRESULT init(void);
	void release(void);
	void update(float _playerX);
	void render(void);

	//void setBPLayerClass(class PlayerClass* _bPlayerPtr) { bPlayerPtr = _bPlayerPtr; }

	BossClass() {}
	~BossClass() {}
};

