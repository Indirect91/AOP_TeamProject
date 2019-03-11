#pragma once
#include "gameNode.h"
//���� ����ü
struct tagSensor
{
	RECT sensorRc;					//���� ��Ʈ
	float x, y;						//���� ��ǥ
	bool isJump;					//������ �ϰ��ִ��� �Ǵ�
	bool isTouch;					//������ ��ġ ������ �Ǵ�
};
class PlayerClass : public gameNode
{
private:
	enum playerState		//�÷��̾� ����(�̹���)
	{
		//���� 
		LEFTIDLE,
		LEFTRUN,
		LEFTATTACK,
		LEFTJUMPUP,
		LEFTJUMPDOWN,
		LEFTGRAB,
		LEFTDOWNATTACK,
		LEFTCHANGEFORM,
		//������
		RIGHTIDLE,
		RIGHTRUN,
		RIGHTATTACK,
		RIGHTJUMPUP,
		RIGHTJUMPDOWN,
		RIGHTGRAB,
		RIGHTDOWNATTACK,
		RIGHTCHANGEFORM,
	};
	enum changeFormEnum			//�÷��̾ ���� ����
	{
		//����
		JELLYIDLE,
		JELLYMOVE,
		JELLYJUMPUP,
		JELLYJUMPDOWN
	};
private:

	//�÷��̾�
	RECT playerRc;					//�÷��̾� ��Ʈ
	RECT changeEffectRc;			//���� ����Ʈ ���� ��Ʈ
	RECT attackRc;					//���� ���� ��Ʈ
	RECT fireWall;					//���̾�� ��Ʈ?
	RECT tileDestory;				//�μ����� Ÿ�� �νô� ��Ʈ
	float x, y;						//�÷��̾� ��ǥ
	float width;					//�÷��̾� ����
	float height;					//�÷��̾� ����
	float speed;					//�÷��̾� ���ǵ�
	float jellySpeed;				//���� ���ǵ�
	float gravity;					//�߷�
	float addtionalPower;			//�������� �Ŀ�
	float leftRepulsivePower;		//���ʿ��� ���� ��(�ݹ߷�)
	float rightRepulsivePower;		//�����ʿ��� ���� ��(�ݹ߷�)
	float changeCount;				//���� �ð�
	int imgCount;					//�̹��� ������ ���� ī��Ʈ
	int imgIndex;					//�̹��� ������ �ε��� ���� ī��Ʈ
	int BombCount;				//�����Ҷ� ������ ���� ������� �� ī��Ʈ
	bool isBombCount;
	//int frameCount;				
	bool isRepusiveCheck;			//�ݹ߷� ����
	bool isLeftRepulsive;			//�������� �ݹ߷��� �ٰ��ΰ�?
	bool changeForm;				//���� ���ΰ�? �ȼ� ���ΰ�?
	bool isLeft;					//�������� �Ǵ�
	bool isAttack;					//�������ΰ�?
	bool isDownAttack;				//�ٿ� ���� ���ΰ�?
	bool isChange;					//�������ΰ�?

	string CollisionStage;			//�������� �̸��� �������

	//���� 
	tagSensor sensorBottom;			//�Ʒ�
	tagSensor sensorTop;			//��
	tagSensor sensorLeft;			//����
	tagSensor sensorRight;			//������
	tagSensor sensorLeftTop;		//���� �밢��
	tagSensor sensorRightTop;		//������ �밢��

	// Enum //
	playerState playerStateEnum;
	changeFormEnum jellyState;

public:

	HRESULT init(float _x, float _y, string _collisionStage);
	void release(void);
	void update(void);
	void render(void);

	RECT getRect() { return playerRc; }
	RECT getSensorRcBottom() { return sensorBottom.sensorRc; }
	RECT getSensorRcTop() { return sensorTop.sensorRc; }
	RECT getSensorRcRight() { return sensorRight.sensorRc; }
	RECT getSensorRcLeft() { return sensorLeft.sensorRc; }
	RECT getAttackRc() { return attackRc; }
	int getBombCount() { return BombCount; }
	float getX() { return x; }
	float getY() { return y; }
	float getLeftRepulsiver() { return leftRepulsivePower; }
	float getRightRepulsive() { return rightRepulsivePower; }
	float getGravity() { return gravity; }
	float getChangeCount() { return changeCount; }
	bool getChangeForm() { return changeForm; }
	bool getIsAttack() { return isAttack; }
	void setX(float _x) { x -= _x; }
	void setChangeForm(bool _changeForm) { changeForm = _changeForm; }
	void setGravity(float _gravity) { gravity = _gravity; }

	void playerMove();					//�÷��̾�(�ȼ� ��) ������
	void playerAttack();				//�÷��̾� ����
	void sensorMove();					//���� ������
	void pixelCollision();				//�ȼ� �浹
	void repulsive();					//�ݹ߷�
	void transForm();					//�����ϱ�
	void jellyMove();					//�÷��̾�(���� ��) ������

	void sensorPixelCollisionCheck();						//������ �浹�� �ǰ��ִ��� üũ

	void playerStateFrameImageRender(float x, float y);		//������ �̹��� ������ ���� �Լ�

	PlayerClass() {};
	~PlayerClass() {};
};

