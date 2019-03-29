#pragma once
#include "gameNode.h"
class BossStageClass :public gameNode
{
	image* BossStageImg;
	image* BossCollisionImg;

	float loopX1, loopY1;		//��� �̹��� 1�� ������ǥ
	float loopX2, loopY2;		//��� �̹��� 2�� ������ǥ
	float loopX3, loopY3;		//��� �̹��� 3�� ������ǥ
	float loopX4, loopY4;		//��� �̹��� 4�� ������ǥ

	class UIClass* bUIPtr;

	class PlayerClass* playerPtr;				//���� ���������� �ִ� �÷��̾� Ŭ���� ������

	class FieldManagerClass* fieldPtr;

	class EnemyManagerClass* bEnemyMPtr;		//���� ���������� �ִ� �� �Ŵ��� Ŭ���� ������

	class PetsClass* bPetPtr;					//���� ���������� �ִ� �� Ŭ���� ������
	vector <PetsClass*> bPetPtrV;				//���� ���������� �ִ� �� Ŭ���� �����͸� ��� ����
	image * respawnImg;							
	UINT respawnFrame;							

	class savePoint* bSaveMPtr;					//���� ���������� �ִ� ���̺������� Ŭ���� ������
	class clearPoint* bClearMPtr;				//���� ���������� �ִ� Ŭ���������� Ŭ���� ������

	class treasureBox* bTreasurePtr;			//���� ���������� �ִ� �������� Ŭ���� ������
	vector <treasureBox*> bTreasurePtrV;		//���� ���������� �ִ� �������� Ŭ���� �����͸� ��� ����

	class BossClass* bBossPtr;					//���� ���������� �ִ� ���� Ŭ���� ������


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	BossStageClass() {}
	~BossStageClass() {}
};

