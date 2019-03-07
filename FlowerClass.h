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

	//¹Ù´Ú ²É
	Flower* flowerone;
	Flower* flowertwo;
	Flower* flowerthree;
	Flower* flowerfour;
	Flower* flowerfive;

	//¿À¸¥ÂÊ ²É
	Flower* flowerRightone;
	Flower* flowerRighttwo;

	//¹éÅÍ
	vector<Flower*>FlowerList;
	vector<Flower*>FlowerListRight;

	//ÃÑ¾Ë
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

