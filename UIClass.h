#pragma once
#include "gameNode.h"

class UIClass : public gameNode
{
	image* jewelShapeImg;		//게임에서 보석의 숫자 옆에있는 보석문양

	image* HPImg;				//플레이어 체력
	int frameHP;				//0->체력x, 1=체력o

	struct tagPetCheck
	{
		image* CheckImg;		//체크용 이미지
		bool isCheck;			//스테이지1에서 찾았는가?
		int framePet;			//프레임 이미지
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

