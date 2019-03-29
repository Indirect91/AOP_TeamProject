#pragma once
#include "gameNode.h"

class PetsClass : public gameNode
{
public:
	enum class PetsTypes
	{
		seal = 1,
		bat,
		shark
	};
private:


	image* petImg;			//���� �̹���
	RECT petRc;				//���� ��Ʈ

	float petX, petY;		//���� �߽���ǥ
	float petSpeed;			//���� �ӵ�
	bool isPetRight;		//���� �������� �����ִ°�? true->������
	bool isPetFind;			//���� ã�Ҵ°�? true->ã��
	bool isPetCatch;		//���� ��Ҵ°�? true->����

	int petImgCount;		//�� �̹��� ī��Ʈ
	int frameX;				//�̹��� x������ ī��Ʈ
	int frameY;				//�̹��� y������ ī��Ʈ

	PetsTypes whichPet;			//� ���� �����ߴ°�?

	image* petHeartImg;		//���� �߽߰� �� ��Ʈ �̹���
	int petHImgCount;		//��Ʈ �̹��� ī��Ʈ
	int frameHX;			//��Ʈ �̹��� ������

public:

	HRESULT init(PetsTypes _whichPet, float _petX, float _petY, bool _isFind);
	void release(void);
	void update(void);
	void render(void);

	RECT getPetRc() { return petRc; }

	float getPetX() { return petX; }
	void setPetX(float _petX) { petX = _petX; }

	float getPetY() { return petY; }
	void setPetY(float _petY) { petY = _petY; }

	bool getIsPetFind() { return isPetFind; }
	void setIsPetFind(bool _isPetFind) { isPetFind = _isPetFind; }

	PetsTypes getWhichPet() { return whichPet; }

	PetsClass() {}
	~PetsClass() {}
};

