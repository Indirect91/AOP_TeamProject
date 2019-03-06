#pragma once
#include "gameNode.h"

class Stage1Class : public gameNode
{
private:

	//�������� �̹���
	image * stage1Img;
	image * stage1CollisionImg;

	//��� �̹���
	float loopX1, loopY1;		//��� �̹��� 1�� ������ǥ
	float loopX2, loopY2;		//��� �̹��� 2�� ������ǥ
	float loopX3, loopY3;		//��� �̹��� 3�� ������ǥ
	float loopX4, loopY4;		//��� �̹��� 4�� ������ǥ

	class PlayerClass* playerPtr;				//��������1�� �ִ� �÷��̾� Ŭ���� ������
	
	class EnemyManagerClass* s1EnemyMPtr;		//��������1�� �ִ� �� �Ŵ��� Ŭ���� ������
	vector < EnemyManagerClass*> s1EnemyMPtrV;	//��������1�� �ִ� �� �Ŵ��� Ŭ���� �����͸� ��� ����
	
	class PetsClass* s1PetPtr;					//��������1�� �ִ� �� Ŭ���� ������
	vector <PetsClass*> s1PetPtrV;				//��������1�� �ִ� �� Ŭ���� �����͸� ��� ����
	
	class FieldManagerClass* fieldPtr;

	class savePoint* s1SaveMPtr;				//��������1�� �ִ� ���̺������� Ŭ���� ������
	vector <savePoint*> s1SaveMPtrV;			//��������1�� �ִ� ���̺������� Ŭ���� �����͸� ��� ����

	class treasureBox* s1TreasurePtr;			//��������1�� �ִ� �������� Ŭ���� ������
	vector <treasureBox*> s1TreasurePtrV;		//��������1�� �ִ� �������� Ŭ���� �����͸� ��� ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Stage1Class() {};
	~Stage1Class() {};
};

