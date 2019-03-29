#pragma once
#include "gameNode.h"

class VillageClass : public gameNode
{
	image* villageImg;				//���� �̹���
	image* villageBgImg;			//���� ��� �̹���
	int loopX;						//��� ���� ����X

	RECT merchantRc;				//���� ��Ʈ
	image* merchantImg;				//���� �̹���
	image* merchantHiImg;			//������ �λ� �̹���
	int imgVCount;
	int frameVX;

	bool isMeet;					//���ΰ� �����°�?
	RECT vEmpty;

	class PlayerClass* vPlayerPtr;	//���� ���������� �ִ� �÷��̾� ������

	class UIClass* vUIPtr;			//���� ���������� �ִ� UIŬ���� ������

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	VillageClass() {}
	~VillageClass() {}
};

