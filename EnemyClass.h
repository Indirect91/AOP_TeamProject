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
	float enemySpeed;		//�� �ӵ�
	bool isDie;				//���� �׾��°�? true->����

	int imgCount;			//�̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getEnemyX() { return enemyX; }
	void setEnemyX(float _enemyX) { enemyX = _enemyX; }

	float getEnemyY() { return enemyY; }
	void setEnemyY(float _enemyY) { enemyY = _enemyY; }

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
	float enemySpeed;		//�� �ӵ�
	bool isRight;			//���� �������� ���� �ִ°�? true->������
	bool isDie;				//���� �׾��°�? true->����

	int imgCount;			//�̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ

	//�����̴� ���̶�� ������ �������� �־��� ����
	int scaleLeftX;			//������ ������ ���� ��
	int scaleRightX;		//������ ������ ������ ��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getEnemyX() { return enemyX; }
	void setEnemyX(float _enemyX) { enemyX = _enemyX; }

	float getEnemyY() { return enemyY; }
	void setEnemyY(float _enemyY) { enemyY = _enemyY; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	int getScaleLeftX() { return scaleLeftX; }
	void setScaleLeftX(int _scaleLeftX) { scaleLeftX = _scaleLeftX; }

	int getScaleRightX() { return scaleRightX; }
	void setScaleRightX(int _scaleRightX) { scaleRightX = _scaleRightX; }

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
	float enemySpeed;		//�� �ӵ�
	bool isRight;			//���� �������� ���� �ִ°�? true->������
	bool isDie;				//���� �׾��°�? true->����

	int imgCount;			//�̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ
	int stayCount;			//�̹����� ��� �ӹ����� �ϴ� �ð�

	//�����̴� ���̶�� ������ �������� �־��� ����
	int scaleLeftX;			//������ ������ ���� ��
	int scaleRightX;		//������ ������ ������ ��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getEnemyX() { return enemyX; }
	void setEnemyX(float _enemyX) { enemyX = _enemyX; }

	float getEnemyY() { return enemyY; }
	void setEnemyY(float _enemyY) { enemyY = _enemyY; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	int getScaleLeftX() { return scaleLeftX; }
	void setScaleLeftX(int _scaleLeftX) { scaleLeftX = _scaleLeftX; }

	int getScaleRightX() { return scaleRightX; }
	void setScaleRightX(int _scaleRightX) { scaleRightX = _scaleRightX; }

	flyCrystal() {}
	~flyCrystal() {}
};