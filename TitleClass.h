#pragma once
#include "gameNode.h"
class TitleClass : public gameNode
{
private:
	image * titlebg;   //Ÿ��Ʋ ��׶���
	image * titlelogo; //Ÿ��Ʋ �ΰ�
	image * pip1;      //���º� ��
	image * pip2;	   //���º� ��
	image * pip3;	   //���º� ��
	image * esc;		//ESC������� â
	image * enter;		//Enter ������� â
	image * newYes;
	image * newNo;		
	image * fileSelect;
	image * loadFile;
	image * ESC_YSetting;
	image * newEmpty;
	image * selection;
	image * moneyNum[5];
	image * rescueAnimal;
	image * maxHeart;
	image * continueimg;
	image * saveSlot1;
	image * saveSlot2;
	image * saveSlot3;
	POINTFLOAT saveSlot1Pos;
	POINTFLOAT saveSlot2Pos;
	POINTFLOAT saveSlot3Pos;

	UINT heratNum;
	UINT titleAlpha;
	UINT counter; //��� ���� Ȯ�ο�
	bool SettingPhase; //����â ���Կ���
	bool SecondPhase; //Ÿ��Ʋâ 2��° ȭ������
	bool LastPhase; //Ÿ��Ʋâ ������ ������
	int jNum;

	//���Կ� ������ ���ڵ�
	image * slot1Money;
	image * slot2Money;
	image * slot3Money;

	image * slot1Pets;
	image * slot2Pets;
	image * slot3Pets;
	int Pip1Pets;
	int Pip2Pets;
	int Pip3Pets;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TitleClass() {};
	~TitleClass() {};
};
