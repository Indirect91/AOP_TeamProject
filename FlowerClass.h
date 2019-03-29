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
	//�� ��Ʈ
	struct Flower
	{
		RECT rc;
	};
	//����
	bool isHit;
	//�ٴ� �� ī��Ʈ
	int Count;
	//���� �� ī��Ʈ
	int LeftCountone;
	int LeftCounttwo;
	int LeftCountthree;
	int LeftCountfour;
	//������ �� ī��Ʈ
	int RightCountone;
	int RightCounttwo;
	int RightCountthree;
	int RightCountfour;
	//���� �ι�° �� ī��Ʈ
	int LeftTwoCountone;
	int LeftTwoCounttwo;
	//������ �ι�° �� ī��Ʈ
	int RightTwoCountone;
	int RightTwoCounttwo;
	//�ٴڲ� 2��° ī��Ʈ
	int DownoneCount;
	int DowntwoCount;
	//���� �ܰ� �� ī��Ʈ
	int UponeCount;
	int UptwoCount;
	//���� �߽� �� ī��Ʈ
	int UpthreeCount;
	//�ٴ� ��
	Flower* flowerone;
	Flower* flowertwo;
	Flower* flowerthree;
	Flower* flowerfour;
	Flower* flowerfive;

	//������ ��
	Flower* flowerRightone;
	Flower* flowerRighttwo;

	//���� ��
	Flower* flwoerLeftone;
	Flower* flowerLefttwo;
	//�ٴ� �� 2����
	Flower* flowerDownone;
	Flower* flowerDowntwo;
	//���� �ܰ� ��
	Flower* flowerUpone;
	Flower* flowerUptwo;
	//���� �߽� ��
	Flower* flowerUpthree;
	//����
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
	//�Ѿ�
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

