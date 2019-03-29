#pragma once
#include "gameNode.h"

class UIClass : public gameNode
{
	image* jewelShapeImg;			//���ӿ��� ������ ���� �����ִ� ��������
	image* jewelCountImg[5];		//���ӿ��� ���� ������ �󸶳� �������ִ��� ������ �����̹���
	int jNum;

	image* HPImg;					//�÷��̾� ü��
	int maxHp;						//0->ü��x, 1=ü��o

	struct tagHeart
	{
		image* Hpimg;
		int frameHp;
		POINT position;
	};
	vector<tagHeart> totalHeartV;

	struct tagPetCheck
	{
		image* CheckImg;			//üũ�� �̹���
		bool isCheck;				//��������1���� ã�Ҵ°�?
		int framePet;				//������ �̹���
	};

	//��������1 ���� üũ
	tagPetCheck checkSealS1;
	tagPetCheck checkBatS1;
	tagPetCheck checkSharkS1;
	//������������ ���� üũ
	tagPetCheck checkSealB;
	tagPetCheck checkBatB;
	tagPetCheck checkSharkB;
	//���� ����ִ°�
	string petsWhere;

	//����
	image* storeImg;
	image* selectImg;
	float selectX, selectY;
	image* textImg;
	bool isShop;
	bool isPurchasable;
	bool isInvenFull;			//�κ��丮�� Ǯ(false)�̸� ?
	bool isNoMoney;				//���� ������?
	class PlayerClass* uiPlayerPtr;
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

	bool getIsShop() { return isShop; }
	void setIsShop(bool _isShop) { isShop = _isShop; }

	void setSelectX(float _selectX) { selectX = _selectX; }
	void setSelectY(float _selectY) { selectY = _selectY; }

	void setUiPlayerPtr(PlayerClass* _playerPtr) { uiPlayerPtr = _playerPtr; }

	UIClass() {}
	~UIClass() {}
};

