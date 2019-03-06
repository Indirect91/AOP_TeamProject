#pragma once
#include "gameNode.h"

enum PetsTypes
{
	bat = 1,
	seal,
	shark
};

class PetsClass : public gameNode
{
	image* petImage;		//���� �̹���
	RECT petRc;				//���� ��Ʈ

	float petX, petY;		//���� �߽���ǥ
	float petSpeed;			//���� �ӵ�
	bool isPetRight;		//���� �������� �����ִ°�? true->������
	bool isPetCatch;		//���� ��Ҵ°�? true->����

	int petImgCount;		//�� �̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ

	int whichPet;			//� ���� �����ߴ°�?

public:
	HRESULT init(int _whichPet, float _petX, float _petY);
	void release(void);
	void update(void);
	void render(void);

	float getPetX() { return petX; }
	void setPetX(float _petX) { petX = _petX; }

	float getPetY() { return petY; }
	void setPetY(float _petY) { petY = _petY; }

	bool getIsPetCatch() { return isPetCatch; }
	void setIsPetCatch(bool _isPetCatch) { isPetCatch = _isPetCatch; }


	PetsClass() {}
	~PetsClass() {}
};

