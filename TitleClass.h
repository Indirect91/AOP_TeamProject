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

	image * saveSlot1;
	image * saveSlot2;
	image * saveSlot3;
	POINTFLOAT saveSlot1Pos;
	POINTFLOAT saveSlot2Pos;
	POINTFLOAT saveSlot3Pos;


	UINT titleAlpha;
	UINT counter; //��� ���� Ȯ�ο�
	bool SettingPhase; //����â ���Կ���
	bool SecondPhase; //Ÿ��Ʋâ 2��° ȭ������
	bool LastPhase; //Ÿ��Ʋâ ������ ������

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	TitleClass() {};
	~TitleClass() {};
};
