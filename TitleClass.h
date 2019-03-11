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
	image * esc;		//ESC누르라는 창
	image * enter;		//Enter 누르라는 창
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
	UINT counter; //모션 진행 확인용
	bool SettingPhase; //세팅창 진입여부
	bool SecondPhase; //타이틀창 2번째 화면인지
	bool LastPhase; //타이틀창 마지막 페이즈

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	TitleClass() {};
	~TitleClass() {};
};
