#pragma once
#include "gameNode.h"

//===================================
//	## ���ٴϴ� ���� enemy ##
//===================================
class flyOctopus : public gameNode
{
	image* enemyImage;		//�� �̹���
	RECT enemyRc;			//�� ��Ʈ

	float enemyX, enemyY;	//�� ��ǥ
	bool isDie;				//���� �׾��°�? true->����

	float dieCount;			//�׾����� �̹����� �۾����� ������� ���� ī��Ʈ
	float dieCountX;		//�׾����� �̹����� �۾����� ������� ���� ī��Ʈ

	bool firstStep;			//�׾����� �پ����� �þ�� ������� ����� ��������� �� �Һ���

	int reviveCount;		//�ٽ� ��Ƴ� �ð�

	int imgCount;			//�̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ


public:
	HRESULT init(float _enemyX, float _enemyY);
	void release(void);
	void update(void);
	void render(void);

	RECT getEnemyRc() { return enemyRc; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	flyOctopus() {}
	~flyOctopus() {}
};

//===================================
//	## ���ٴϴ� ���� enemy ##
//===================================
class crawlBug : public gameNode
{
	image* enemyImage;		//�� �̹���
	RECT enemyRc;			//�� ��Ʈ

	float enemyX, enemyY;	//�� ��ǥ
	float saveX, saveY;		//�޾ƿ� ���� ��ǥ�� �����ص� 
	float enemySpeed;		//�� �ӵ�
	bool isRight;			//���� �������� ���� �ִ°�? true->������

	bool isDie;				//���� �׾��°�? true->����

	float dieCount;			//�׾����� �̹����� �۾����� ������� ���� ī��Ʈ
	float dieCountX;			//�׾����� �̹����� �۾����� ������� ���� ī��Ʈ

	bool firstStep;			//�׾����� �پ����� �þ�� ������� ����� ��������� �� �Һ���

	int reviveCount;		//�ٽ� ��Ƴ� �ð�
	bool isRevive;			//�װ� �ٽ� ��Ƴ��� ����� ������ �Һ���

	int imgCount;			//�̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ

	//�����̴� ���̶�� ������ �������� �־��� ����
	int scaleLeftX;			//������ ������ ���� ��
	int scaleRightX;		//������ ������ ������ ��

public:
	HRESULT init(float _x, float _y, float _scaleLeftX, float _scaleRightX);
	void release(void);
	void update(void);
	void render(void);

	RECT getEnemyRc() { return enemyRc; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	crawlBug() {}
	~crawlBug() {}
};

//===================================
//	## ���ƴٴϴ� ũ����Ż enemy ##
//===================================
class flyCrystal : public gameNode
{
	image* enemyImage;		//�� �̹���
	RECT enemyRc;			//�� ��Ʈ

	float enemyX, enemyY;	//�� ��ǥ
	float saveX, saveY;		//�޾ƿ� ���� ��ǥ�� �����ص� 
	float enemySpeed;		//�� �ӵ�
	bool isRight;			//���� �������� ���� �ִ°�? true->������

	bool isDie;				//���� �׾��°�? true->����
	int dieCount;			//�׾����� �̹����� �����̸� ������� ���� ī��Ʈ

	int reviveCount;		//�ٽ� ��Ƴ� �ð�
	bool isRevive;			//�װ� �ٽ� ��Ƴ��� ����� ������ �Һ���

	int imgCount;			//�̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ

	//�����̴� ���̶�� ������ �������� �־��� ����
	int scaleLeftX;			//������ ������ ���� ��
	int scaleRightX;		//������ ������ ������ ��

public:
	HRESULT init(float _x, float _y, float _scaleLeftX, float _scaleRightX);
	void release(void);
	void update(void);
	void render(void);

	RECT getEnemyRc() { return enemyRc; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	flyCrystal() {}
	~flyCrystal() {}
};

//===================================
//	## �յ��� ���� enemy ##
//===================================
class flyGhost : public gameNode
{
	image* enemyImage;		//�� �̹���
	RECT enemyRc;			//�� ��Ʈ

	float enemyX, enemyY;	//�� ��ǥ
	float enemySpeed;		//�� �ӵ�
	bool isDie;				//���� �׾��°�? true->����
	int reviveCount;		//�ٽ� ��Ƴ� �ð�

	int imgCount;			//�̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ

public:
	HRESULT init(float _x, float _y);
	void release(void);
	void update(void);

	void render(void);

	RECT getEnemyRc() { return enemyRc; }

	float getEnemyX() { return enemyX; }
	void setEnemyX(float _enemyX) { enemyX = _enemyX; }

	float getEnemyY() { return enemyY; }
	void setEnemyY(float _enemyY) { enemyY = _enemyY; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	flyGhost() {}
	~flyGhost() {}
};