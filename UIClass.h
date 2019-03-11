#pragma once
#include "gameNode.h"

class UIClass : public gameNode
{
	image* jewelShapeImg;		//���ӿ��� ������ ���� �����ִ� ��������

	image* HPImg;				//�÷��̾� ü��
	int frameHP;				//0->ü��x, 1=ü��o

	struct tagPetCheck
	{
		image* CheckImg;		//üũ�� �̹���
		bool isCheck;			//��������1���� ã�Ҵ°�?
		int framePet;			//������ �̹���
		POINT position;
	};

	tagPetCheck checkSealS1;
	tagPetCheck checkBatS1;
	tagPetCheck checkSharkS1;

	tagPetCheck checkSealB;
	tagPetCheck checkBatB;
	tagPetCheck checkSharkB;

	string petsWhere;

public:

	HRESULT init(string _petsWhere);
	void release();
	void update();
	void render();


	UIClass() {}
	~UIClass() {}
};

