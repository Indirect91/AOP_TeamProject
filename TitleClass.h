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
	image * esc;	//ESC������� â
	image * enter; //Enter ������� â

	bool isMotion; //�������������


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	TitleClass() {};
	~TitleClass() {};
};
