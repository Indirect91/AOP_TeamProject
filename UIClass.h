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

	bool getCheckSealS1_IsCheck() { return checkSealS1.isCheck; }
	void setCheckSealS1_IsCheck(bool _isCheck) { checkSealS1.isCheck = _isCheck; }

	bool getCheckBatS1_IsCheck() { return checkBatS1.isCheck; }
	void setCheckBatS1_IsCheck(bool _isCheck) { checkBatS1.isCheck = _isCheck; }

	bool getCheckSharkS1_IsCheck() { return checkSharkS1.isCheck; }
	void setCheckSharkS1_IsCheck(bool _isCheck) { checkSharkS1.isCheck = _isCheck; }

	bool getCheckSealB_IsCheck() { return checkSealB.isCheck; }
	void setCheckSealB_IsCheck(bool _isCheck) { checkSealB.isCheck = _isCheck; }

	bool getCheckBatB_IsCheck() { return checkBatB.isCheck; }
	void setCheckBatB_IsCheck(bool _isCheck) { checkBatB.isCheck = _isCheck; }

	bool getCheckSharkB_IsCheck() { return checkSharkB.isCheck; }
	void setCheckSharkB_IsCheck(bool _isCheck) { checkSharkB.isCheck = _isCheck; }


	UIClass() {}
	~UIClass() {}
};

