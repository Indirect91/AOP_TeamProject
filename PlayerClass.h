#pragma once
#include "gameNode.h"
class ItemClass;
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
	enum playerState		//�÷��̾� ����(�ΰ� ��)
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
		LEFTHIT,
		LEFTRESPAWN,
		//������
		RIGHTIDLE,
		RIGHTRUN,
		RIGHTATTACK,
		RIGHTJUMPUP,
		RIGHTJUMPDOWN,
		RIGHTGRAB,
		RIGHTDOWNATTACK,
		RIGHTCHANGEFORM,
		RIGHTHIT
	};
	enum changeFormEnum			//�÷��̾ ���� ����(���� ��)
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
	RECT fireWall;					//���̾�� ��Ʈ?(�����ϸ� �� ����)
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
	float BombCount;				//�����Ҷ� ������ ���� ������� �� ī��Ʈ
	int pipHp;						//�� ü��
	int imgCount;					//�̹��� ������ ���� ī��Ʈ
	int imgIndex;					//�̹��� ������ �ε��� ���� ī��Ʈ
	int changeEffectCount;			//���� ����Ʈ ������ ���ε��� ����
	int invincibleCount;			//���� �ð�
	int invincibleCountAlpha;		//������ ĳ���� ��¦��¦�ϰ� ǥ���� ī��Ʈ
	int testcount;
	bool isBomb;					//�����ϸ� ��Ʈ ������ ���� �ð� ������ ��������� ����
	bool isRepusiveCheck;			//�ݹ߷� ����
	bool isLeftRepulsive;			//�������� �ݹ߷��� �ٰ��ΰ�?
	bool changeForm;				//���� ��(true)�ΰ�? �ΰ� ��(false)�ΰ�?
	bool isLeft;					//�������� �Ǵ�
	bool isAttack;					//�������ΰ�?
	bool isDownAttack;				//�ٿ� ���� ���ΰ�?
	bool isChange;					//�������ΰ�?
	bool isInvincible;				//�÷��̾ �����ΰ�?
	bool isBombTileCrashDown;		//�������� Ÿ�� �ѽø� ��������~
	
	string CollisionStage;			//�������� �̸��� �������


	// ���� //
	tagSensor sensorBottom;			//�Ʒ�
	tagSensor sensorTop;			//��
	tagSensor sensorLeft;			//����
	tagSensor sensorRight;			//������
	tagSensor sensorLeftTop;		//���� �밢��
	tagSensor sensorRightTop;		//������ �밢��

	// Enum //
	playerState playerStateEnum;
	changeFormEnum jellyState;

	image * respawnImg;
	UINT	respawnFrame;
	bool isRespawn;					//��������������
	UINT counter;
	vector<ItemClass*> items;

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
	RECT getTileDestoryRc() { return tileDestory; }
	RECT getEnemyCrashRc() { return fireWall; }
	int getBombCount() { return BombCount; }
	int getInvincibleCount() { return invincibleCount; }
	int getPipHp() { return pipHp; }
	int getInvincibleCountAlpha() { return invincibleCountAlpha; }
	int getTestCount() { return testcount; }
	float getX() { return x; }
	float getY() { return y; }
	float getHeight() { return height; }
	float getLeftRepulsiver() { return leftRepulsivePower; }
	float getRightRepulsive() { return rightRepulsivePower; }
	float getGravity() { return gravity; }
	float getChangeCount() { return changeCount; }
	bool getSensorBottomIsJump() { return sensorBottom.isJump; }
	bool getIsLeft() { return isLeft; }
	bool getChangeForm() { return changeForm; }
	bool getIsAttack() { return isAttack; }
	bool getInvincible() { return isInvincible; }
	bool getIsBomb() { return isBomb; }
	bool &refResPawn() { return isRespawn; }
	UINT &refResPawnFrame() { return respawnFrame; }
	UINT &refCounter() { return counter; }
	
	tagSensor &getSensorBottom() { return sensorBottom; }
	


	vector<ItemClass*> &getItems() { return items; }
	//void setItems(vector<ItemClass*> _items) { items = _items; }

	void setX(float _x) { x -= _x; }
	void setRealX(float _x) { x = _x; }
	void setY(float _y) { y -= _y; }
	void setRealY(float _y) { y = _y; }
	void setPipHp(int _pipHp) { pipHp = _pipHp; }
	void setChangeForm(bool _changeForm) { changeForm = _changeForm; }
	void setGravity(float _gravity) { gravity = _gravity; }
	void setInvincible(bool _invincible) { isInvincible = _invincible; }
	void setInvincibleCount(int _invincibleCount) { invincibleCount = _invincibleCount; }
	void setInvincibleCountAlpha(int _invincibleCountAlpha) { invincibleCountAlpha = _invincibleCountAlpha; }
	void setBombTileCrashDown(bool _BombTileCrashDown) { isBombTileCrashDown = _BombTileCrashDown; }
	void setSensorBottomIsJump(bool _sensorBottomIsJump) { sensorBottom.isJump = _sensorBottomIsJump; }
	void setTestCount(int _testcount) { testcount = _testcount; }
	void setRightRepulsionPower(float _rightRepulsivePower) { rightRepulsivePower = _rightRepulsivePower; }
	void setLeftRepulsionPower(float _leftRepulsivePower) { leftRepulsivePower = _leftRepulsivePower; }


	void playerMove();					//�÷��̾�(�ȼ� ��) ������
	void playerAttack();				//�÷��̾� ����
	void sensorMove();					//���� ������
	void pixelCollision();				//�ȼ� �浹
	void repulsive();					//�ݹ߷�
	void transForm();					//�����ϱ�
	void jellyMove();					//�÷��̾�(���� ��) ������
	void respawn();

	void selectItem();

	void sensorPixelCollisionCheck();						//������ �浹�� �ǰ��ִ��� üũ

	void playerStateFrameImageRender(float x, float y);		//������ �̹��� ������ ���� �Լ�

	PlayerClass() {};
	~PlayerClass() {};
};

