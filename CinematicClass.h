#pragma once
#include "gameNode.h"
class CinematicClass : public gameNode
{
	image* prologueImg[9];	//���ѷα�
	image* epilogueImg[2];	//���ʷα�
	image* curtainImg;		//��ȯ

	image * firstBuffer;	//ù° ȭ��
	image * secondBuffer;	//��° ȭ��

	float firstAlpha;		//ù° ȭ��
	float secondAlpha;		//��° ȭ�� ����

	BOOL firstRising;		//ù° ���İ� �����
	BOOL secondRising;		//��° ���İ� �����

	bool ending;
	bool cineEnd;
	int curtainY;

	int cinemaCount;		//�ó׸� �ѱ� ī��Ʈ
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

