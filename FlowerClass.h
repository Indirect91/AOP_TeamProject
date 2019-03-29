#pragma once
#include "FieldManagerClass.h"
class FlowerClass : public FieldManagerClass
{
public:
	enum class FlowerTile
	{
		Stage1 = 0,
		BossStage
	};
private:
	//²É ·ºÆ®
	struct Flower
	{
		RECT rc;
	};
	//º¯¼ö
	bool isHit;
	//¹Ù´Ú ²É Ä«¿îÆ®
	int Count;
	//¿ÞÂÊ ²É Ä«¿îÆ®
	int LeftCountone;
	int LeftCounttwo;
	int LeftCountthree;
	int LeftCountfour;
	//¿À¸¥ÂÊ ²É Ä«¿îÆ®
	int RightCountone;
	int RightCounttwo;
	int RightCountthree;
	int RightCountfour;
	//¿ÞÂÊ µÎ¹øÂ° ²É Ä«¿îÆ®
	int LeftTwoCountone;
	int LeftTwoCounttwo;
	//¿À¸¥ÂÊ µÎ¹øÂ° ²É Ä«¿îÆ®
	int RightTwoCountone;
	int RightTwoCounttwo;
	//¹Ù´Ú²É 2¹øÂ° Ä«¿îÆ®
	int DownoneCount;
	int DowntwoCount;
	//À§¿¡ ¿Ü°¢ ²É Ä«¿îÆ®
	int UponeCount;
	int UptwoCount;
	//À§¿¡ Áß½É ²É Ä«¿îÆ®
	int UpthreeCount;
	//¹Ù´Ú ²É
	Flower* flowerone;
	Flower* flowertwo;
	Flower* flowerthree;
	Flower* flowerfour;
	Flower* flowerfive;

	//¿À¸¥ÂÊ ²É
	Flower* flowerRightone;
	Flower* flowerRighttwo;

	//¿ÞÂÊ ²É
	Flower* flwoerLeftone;
	Flower* flowerLefttwo;
	//¹Ù´Ú ²É 2¹ø¤Š
	Flower* flowerDownone;
	Flower* flowerDowntwo;
	//À§¿¡ ¿Ü°¢ ²É
	Flower* flowerUpone;
	Flower* flowerUptwo;
	//À§¿¡ Áß½É ²É
	Flower* flowerUpthree;
	//¹éÅÍ
	vector<Flower*>FlowerList;
	vector<Flower*>FlowerListLeft;
	vector<Flower*>FlowerListRight;
	vector<Flower*>FlowerListLefttwo;
	vector<Flower*>FlowerListRighttwo;
	vector<Flower*>FlowerListDownoen;
	vector<Flower*>FlowerListDowntwo;
	vector<Flower*>FlowerListUpone;
	vector<Flower*>FlowerListUptwo;
	vector<Flower*>FlowerListUpthree;
	//ÃÑ¾Ë
	class bullet* fireBollPtr;
	class bullet* fireBollLeftPtr;
	class bullet* fireBollRightPtr;
	class bullet* fireBollLefttwoPtr;
	class bullet* fireBollRighttwoPtr;
	class bullet* fireBollUpOnePtr;
	class bullet* fireBollUpTwoPtr;
	class bullet* fireBollUpthreePtr;
	class bullet* fireBollDownOnePtr;
	class bullet* fireBollDownTwoPtr;


	FlowerTile StageNumber;
public:


	class PlayerClass* player;
	void setPlayer(PlayerClass* play) { player = play; }

	class bullet* getFireBollPtr() { return fireBollPtr; }
	class bullet* getFireBollLeftPtr() { return fireBollLeftPtr; }
	class bullet* getFireBollRightPtr() { return fireBollRightPtr; }
	class bullet* getFireBollLeftTwoPtr() { return fireBollLefttwoPtr; }
	class bullet* getFireBollRightTwoPtr() { return fireBollRighttwoPtr; }
	class bullet* getFireBollUpOnePtr() { return fireBollUpOnePtr; }
	class bullet* getFireBollUpTwoPtr() { return fireBollUpTwoPtr; }
	class bullet* getFireBollUpThreePtr() { return fireBollUpthreePtr; }
	class bullet* getFireBollDownOnePtr() { return fireBollDownOnePtr; }
	class bullet* getFireBollDownTwoPtr() { return fireBollDownTwoPtr; }

	HRESULT init(FlowerTile Stage);
	void release(void);
	void update(void);
	void render(void);

	void flowerOne();

	FlowerClass() {}
	~FlowerClass() {}
};

