#pragma once
#include "gameNode.h"
//���� ����ü(�ȼ��浹�� ���� ����)
struct tagSensor
{
	RECT sensorRc;			//���� ��Ʈ
	float x, y;				//���� �߽���ǥ
	bool isJump;			//������ ���� �Һ���

};
class PlayerClass : public gameNode
{
private:
	enum tagEnum
	{
		IDLE,					//�÷��̾� ���
		RUN,					//�÷��̾� �ٱ�
		ATTACK,					//�÷��̾� ����
		JUMP,					//�÷��̾� ����
		GRAB,					//�÷��̾� �����
		DOWNATTACK				//�÷��̾� �Ʒ�����
	};
private:
	//�÷��̾� ����
	RECT playerRc;				//�÷��̾� ��Ʈ
	RECT attackRc;				//���ݽ� ���� ��Ʈ
	float x, y;					//�÷��̾� ��ǥ
	float width;				//�÷��̾� ����
	float height;				//�÷��̾� ����
	float speed;				//�÷��̾� ���ǵ�
	float gravity;				//�߷�
	float addtionalPower;		//���������� ���� �߰����� �Ŀ�
	float leftPower;			//�ݹ߷� ������ ���� ���ʿ��� ������� ��
	float rightPower;			//�ݹ߷� ������ ���� �����ʿ��� ������� ��
	bool isAttack;				//������ �ߴ��� �Ǵ�
	int imgCount;				//�̹��� ������ �ð�
	int imgIndex;				//�̹��� �ε��� ����
	bool isLeft;				//�¿� �̹��� ������ ���� ����
	bool isjumpCheck;			//���� �̹����� ���� ����

	tagEnum playerState;		//�÷��̾� ���� 

	//���� ����
	//RECT jellyRc;				//���� ĳ���� ��Ʈ
	//float x, y;					//���� ��ǥ
	//float width;				//�÷��̾� ����
	//float height;				//�÷��̾� ����
	//float speed;				//�÷��̾� ���ǵ�
	//float gravity;				//�߷�
	//float addtionalPower;		//���������� ���� �߰����� �Ŀ�


	//���� ����(�� �� �� ��)
	tagSensor sensorLeft;
	tagSensor sensorTop;
	tagSensor sensorRight;

	tagSensor sensorBottom;
	tagSensor sensorRightBottom;
	tagSensor sensorLeftBottom;
	//���� �밢��
	tagSensor sensorLeftDiagonal;
	tagSensor sensorRightDiagonal;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//��,�� �Լ�//
	float getX() { return x; }
	float getY() { return y; }
	float getLeftPower() { return leftPower; }
	float getRightPower() { return rightPower; }
	float getGravity() { return gravity; }
	RECT getRect() { return playerRc; }

	// �Լ� //
	void playerMove();			//�÷��̾� �����ӿ� ���� �Լ�(�̵�,����)
	void sensorMove();			//�÷��̾ ����ٴϴ� ������ �����ӿ� ���� �Լ�
	void pixelCollision();		//������ �ȼ��浹 ����
	void pipAttack();

	PlayerClass() {};
	~PlayerClass() {};
};

