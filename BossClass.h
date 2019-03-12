#pragma once
#include "gameNode.h"

class BossClass : public gameNode
{
	enum BossState
	{
		idle,		//���
		move,		//������
		attack1,	//����1
		attack2,	//����2
		attacked,	//�ǰݴ���
		die			//����
	}bossState;

	RECT bossRc;						//���� ��Ʈ
	RECT bossAttackRc;					//���� ���� ��Ʈ
	float bossSpeed;						//���� �ӵ�
	float bossGravity;					//���� �߷�
	float bossX, bossY;					//���� �߽���ǥ
	int bossHp;

	bool isStart;						//���� ������������ ������ �����ϴ°�?

	bool isRight;						//������ �������ΰ�?
	bool isMove;						//������ �����̴°�?
	bool isAttak;						//������ �����ϴ°�?

	image* bossIdleImg;					//������ ����ϴ� �̹���
	image* bossMoveImg;					//������ �����̴� �̹���
	image* bossAttack1Img;				//������ �����ϴ� �̹���1
	image* bossAttack2Img;				//������ �����ϴ� �̹���2
	image* bossAttackedImg;				//������ ���ݹ޴� �̹���
	image* bossDieImg;					//������ �״� �̹���

	int imgCount;
	int frameX;
	int frameY;

	int attCount;						//�÷��̾ ������ �������� ��Ȱ���� ī��Ʈ �� �̹���
	int alphaFrame;						//������ �ǰݴ��Ҷ� �� ���İ�

	RECT bEmpty;

	class PlayerClass* bPlayerPtr;		//���� Ŭ������ �ִ� �÷��̾� ������

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setBPLayerClass(class PlayerClass* _bPlayerPtr) { bPlayerPtr = _bPlayerPtr; }

	BossClass() {}
	~BossClass() {}
};

