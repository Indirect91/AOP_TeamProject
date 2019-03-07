#pragma once
#include "gameNode.h"
//���� ����ü(�ȼ��浹�� ���� ����)
struct tagSensor
{
	RECT sensorRc;			//���� ��Ʈ
	float x, y;				//���� �߽���ǥ
	bool isJump;			//������ ���� �Һ���
	bool isTouch;			//������ �浹���ΰ�?

};
class PlayerClass : public gameNode
{
private:
	//�÷��̾� �ൿ ����ó���� ���� �̳ѹ�~
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
	int imgCount;				//�̹��� ������ �ð�
	int imgIndex;				//�̹��� �ε��� ����
	bool isAttack;				//������ �ߴ��� �Ǵ�
	bool isAttackOrMove;		//�����߿� �̵��Ұ�
	bool isLeft;				//�¿� ������ �̹��� ������ ���� ����
	bool isJumpCheck;			//���� ������ �̹����� ���� ����
	bool isWallGrab;			//���� ����ִ���?
	string CollisionStage;		//��� ���������� �浹������

	tagEnum playerState;		//�÷��̾� ���� (������ �̹��� ��������)

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

	tagSensor sensorBottom;			//���� �Ⱦ�
	tagSensor sensorRightBottom;	//
	tagSensor sensorLeftBottom;
	//���� �밢��
	tagSensor sensorLeftDiagonal;
	tagSensor sensorRightDiagonal;

public:

	HRESULT init(float x, float y, string stage);
	void release(void);
	void update(void);
	void render(void);

	//��,�� �Լ�//
	RECT getRect() { return playerRc; }
	RECT getAttackRect() { return attackRc; }
	float getX() { return x; }
	float getY() { return y; }
	float getLeftPower() { return leftPower; }
	float getRightPower() { return rightPower; }
	float getGravity() { return gravity; }
	void setGravity(float _gravity) { gravity = _gravity; }


	// �Լ� //
	void playerMove();			//�÷��̾� �����ӿ� ���� �Լ�(�̵�,����)
	void playerAttack();		//�÷��̾� ����~
	void sensorMove();			//�÷��̾ ����ٴϴ� ������ �����ӿ� ���� �Լ�
	void pixelCollision();		//������ �ȼ��浹 ����

	void playerStateFrameImageRender(float x, float y);		//������ �̹��� ������ ���� �Լ�

	RECT getSensorRcBottom() { return sensorBottom.sensorRc; }

	PlayerClass() {};
	~PlayerClass() {};
};

