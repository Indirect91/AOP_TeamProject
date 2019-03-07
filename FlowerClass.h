#pragma once
#include "FieldManagerClass.h"
class FlowerClass :	public FieldManagerClass
{
	struct Flower
	{
		RECT rc;
	};
	bool isHit;
	int Count;
	int RightCountone;
	int RightCounttwo;
	int RightCountthree;
	int RightCountfour;

	//�ٴ� ��
	Flower* flowerone;
	Flower* flowertwo;
	Flower* flowerthree;
	Flower* flowerfour;
	Flower* flowerfive;

	//������ ��
	Flower* flowerRightone;
	Flower* flowerRighttwo;

	//����
	vector<Flower*>FlowerList;
	vector<Flower*>FlowerListRight;

	//�Ѿ�
	class bullet* fireBollPtr;
	class bullet* fireBollRightPtr;
public:
	enum class FlowerTile
	{
		Stage1 = 0,
		BossStage
	};

	class PlayerClass* player;
	void setPlayer(PlayerClass* play) { player = play; }

	HRESULT init(FlowerTile Stage);
	void release(void);
	void update(PlayerClass * player);
	void render(void);

	void flowerOne();

	FlowerClass() {}
	~FlowerClass() {}
};

