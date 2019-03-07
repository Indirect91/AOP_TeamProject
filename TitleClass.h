#pragma once
#include "gameNode.h"
class TitleClass : public gameNode
{
private:
	image * titlebg;   //타이틀 백그라운드
	image * titlelogo; //타이틀 로고
	image * pip1;      //형태별 핍
	image * pip2;	   //형태별 핍
	image * pip3;	   //형태별 핍
	image * esc;	//ESC누르라는 창
	image * enter; //Enter 누르라는 창

	bool isMotion; //모션진행중인지


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	TitleClass() {};
	~TitleClass() {};
};
