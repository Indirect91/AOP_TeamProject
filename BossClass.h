#pragma once
#include "gameNode.h"

class BossClass : public gameNode
{
	enum BossState
	{
		idle,		//���
		shout,		//����
		change,		//����
		walk,		//�ȱ�
		run,		//�޸���
		attack1,	//����1
		attack2,	//����2
		attacked,	//�ǰݴ���
		die,		//����
		end			//�ƹ� ���ǵ� ��
	}bossState;

	RECT bossRc;						//���� ��Ʈ
	RECT bossAttackRc;					//���� ���� ��Ʈ
	float bossSpeed;						//���� �ӵ�
	float bossGravity;					//���� �߷�
	float bossX, bossY;					//���� �߽���ǥ
	int bossHp;							//���� ü��

	bool isMeet;						//������ �����°�?
	bool isStart;						//���� ������������ ������ �����ϴ°�?
	bool isRight;						//������ �������ΰ�?
	bool isDie;							//������ �׾��°�?

	image* bossIdleImg;					//������ ����ϴ� �̹���
	image* bossShoutImg;				//������ ����ϴ� �̹���
	image* bossChangeImg;				//������ �����ϴ� �̹���
	image* bossWalkImg;					//������ �����̴� �̹���
	image* bossRunImg;					//������ �����̴� �̹���
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

	bool getIsDie() { return isDie; }

	BossClass() {}
	~BossClass() {}
};

