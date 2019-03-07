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
	void setIsFire(bool _isFire) { isFire = _isFire; }

	savePoint() {}
	~savePoint() {}
};

//===================================
//	## �������� ##
//===================================
class treasureBox : public gameNode
{
public:
	//����
	struct tagJewel
	{
		image* jewelImg;			//�����̹���
		int jewelType;				//�ϴ� ��� ��� ���� ������
		RECT jewelRc;				//���� ��Ʈ
		float jewelX, jewelY;		//���� �߽���ǥ
		float jAngle;				//������ ���ư� �ޱ�
		float jGravity;				//���� ���ư��ٰ� ����Ʈ�� �߷�
		float jSpeed;				//������ ���ư� �ӵ�
		int jewelPrice;				//������ ���ΰ�?
	};
private:

	image* treasureBoxImg;			//�������� �̹���
	RECT treasureBoxRc;				//�������� ��Ʈ

	bool isOpen;					//���µǾ��°�?
	bool isRight;					//�������� ���ϰ� �ִ°�?

	float treasureX, treasureY;		//�������� �߽���ǥ

	int imgCount;
	int frameX, frameY;



	int jewelNum;					//������ ��� ���ð��ΰ�?
	tagJewel jewel;					//���� ����ü
	vector <tagJewel>jewelV;		//���� ����ü�� ��� ����

	string collisionStage;			//�ȼ� �浹�� ���������� ����� �Է��ϱ�����

public:
	HRESULT init(float _x, float _y, bool _isRight, string _collisionStage);
	void release(void);
	void update(void);
	void render(void);

	RECT getTreasureBoxRc() { return treasureBoxRc; }
	vector <tagJewel> & getJewels() { return jewelV; }
	void setIsOpen(bool _isOpen) { isOpen = _isOpen; }
	bool getIsOpen() { return isOpen; }

	treasureBox() {}
	~treasureBox() {}
};