#pragma once
#include "gameNode.h"
class CinematicClass : public gameNode
{
	image* prologueImg[9];	//프롤로그
	image* epilogueImg[2];	//에필로그
	image* curtainImg;		//전환

	image * firstBuffer;	//첫째 화면
	image * secondBuffer;	//둘째 화면

	float firstAlpha;		//첫째 화면
	float secondAlpha;		//둘째 화면 알파

	BOOL firstRising;		//첫째 알파값 상승중
	BOOL secondRising;		//둘째 알파값 상승중

	bool ending;
	bool cineEnd;
	int curtainY;

	int cinemaCount;		//시네마 넘길 카운트
	int alpha[9];

	bool cinemaStart;

	bool isWatch;

	bool isP1;
	bool isP2;
	bool isP3;
	bool isP4;
	bool isP5;
	bool isP6;
	bool isP7;
	bool isP8;
	bool isP9;

	bool isE1;
	bool isE2;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	CinematicClass() {}
	~CinematicClass() {}
};

