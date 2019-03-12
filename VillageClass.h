#pragma once
#include "gameNode.h"

class VillageClass : public gameNode
{
	image* villageImg;				//���� �̹���
	image* villageBgImg;			//���� ��� �̹���
	int loopX;						//��� ���� ����X

	RECT merchantRc;				//���� ��Ʈ
	image* merchantImg;				//���� �̹���
	int imgVCount;
	int frameVX;

	class PlayerClass* vPlayerPtr;	//���� ���������� �ִ� �÷��̾� ������

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	VillageClass() {}
	~VillageClass() {}
};

