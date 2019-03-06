#pragma once
#include "gameNode.h"

//===================================
//	## ���̺� ����Ʈ ##
//===================================
class savePoint : public gameNode
{
	image* savePointImg;		//���̺� ����Ʈ �̹���
	RECT savePointRc;			//���̺� ����Ʈ ����

	image* savePointFireImg;	//���̺� ����Ʈ �Ҳ� �̹���
	RECT savePointFireRc;		//���̺� ����Ʈ �Ҳ� ����

	bool isSave;				//���̺� ����Ʈ�� ��Ҵ°�?
	bool isFire;				//�ѹ� �Ҳ��� �Ͼ�°�?

	float savePX, savePY;		//������ �߽���ǥ

	int imgCount;				//�̹��� ī���� ����
	int frameX1;				//�� �̹��� ������ ����
	int frameX2;				//�Ҳ� �̹��� ������ ����

public:
	HRESULT init(float _x, float _y);
	void release(void);
	void update(void);
	void render(void);

	RECT getSavePointRc() { return savePointRc; }

	void setIsSave(bool _isSave) { isSave = _isSave; }

	savePoint() {}
	~savePoint() {}
};

//===================================
//	## �������� ##
//===================================
class treasureBox : public gameNode
{
	image* treasureBoxImg;			//�������� �̹���
	RECT treasureBoxRc;				//�������� ��Ʈ

	bool isOpen;					//���µǾ��°�?
	bool isRight;					//�������� ���ϰ� �ִ°�?

	float treasureX, treasureY;		//�������� �߽���ǥ

	int imgCount;
	int frameX, frameY;

public:
	HRESULT init(float _x, float _y, bool _isRight);
	void release(void);
	void update(void);
	void render(void);

	treasureBox() {}
	~treasureBox() {}
};