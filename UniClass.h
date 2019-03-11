#pragma once
#include "FieldManagerClass.h"

//���� Ŭ���� 
class UniClass : public FieldManagerClass
{
public:

	enum class Jumpstate
	{
		Stage1,
		BossStage = 1
	};
private:
	//������ ��Ʈ
	RECT JumpRCone;
	RECT JumpRCtwo;
	//������ �̹���
	image* JumpOne;
	image* JumpTwo;
	//�̹��� ī��Ʈ
	//1��
	int JumpOneX;
	int JumpOneY;
	int JumpTwoX;
	int JumpTwoY;


	Jumpstate StageNumber;
public:

	RECT getJumpRCone() { return JumpRCone; }
	RECT getJumpRCtwo() { return JumpRCtwo; }

	int getJumponeY() { return JumpOneY; }
	int getJumptwoY() { return JumpTwoY; }
	void setJumponeY(int one) { JumpOneY = one; }
	void setJumptwoY(int two) { JumpTwoY = two; }


	HRESULT init(Jumpstate Stage);
	void release(void);
	void update(void);
	void render(void);

	UniClass() {}
	~UniClass() {}
};

/*********************************************************************************************
## breakTile Class
**********************************************************************************************/
class BreakTileClass : public FieldManagerClass
{
public:
	enum class BreakTile
	{
		Stage1 = 0,
		BossStage
	};

private:
	struct Tile
	{
		RECT rc;
		POINT point;
		bool isTouch;
		bool isMode;
		int TouchCount;
		int Count;
	};
	vector<Tile>TileList;

	BreakTile StageNumber;
public:
	Tile tile;

	class PlayerClass* player;
	void setPlayer(PlayerClass* play) { player = play; }


	HRESULT init(BreakTile Stage);
	void release(void);
	void update(void);
	void render(void);


	BreakTileClass() {}
	~BreakTileClass() {}
};


/**************************************************************************************************
## HideTileClass ##
***************************************************************************************************/
class HideTileClass : public FieldManagerClass
{
public:
	enum class HideTile
	{
		Stage1 = 0,
		BossStage
	};
private:
	struct Hide
	{
		RECT rc;
		bool isTouch;
	};
	//���İ�Ÿ�� ��Ʈ
	bool ishide;
	RECT HideRc;
	RECT HideRcTwo;
	RECT GrassRC;
	RECT BossTileRCone;
	RECT BossTileRCtwo;
	//���İ� Ÿ�� �̹���
	image* HideBlockTwo;
	image* light;
	image* Boom;
	image* HideBlock;
	image* Grass;
	image* BossTile1;
	image* BossTile2;

	//��ź������ �̹��� ������
	bool isBoom;
	int BoomFrameX;
	int BoomFrameY;
	//����Ÿ�� �̹��� ������
	int Count;
	int frameImgX;
	int frameImgY;
	vector<Hide>HideList;
	Hide hide;
	HideTile StageNumber;
public:


	class PlayerClass* player;
	void setPlayer(PlayerClass* play) { player = play; }

	HRESULT init(HideTile Stage);
	void release(void);
	void update(void);
	void render(void);

	HideTileClass() {}
	~HideTileClass() {}
};

/*******************************************************************************************************************
## ThornTrapClass
********************************************************************************************************************/

class ThorntrapClass : public FieldManagerClass
{

public:
	enum class stageNumber
	{
		Stage1 = 0,
		BossStage
	};

private:
	//�������� 1��
	RECT ThornOne;
	RECT ThornTwo;
	RECT ThornThree;
	RECT ThornFour;
	RECT ThornFive;
	RECT ThornSix;
	RECT ThornSeven;
	vector<RECT>ThornList;
	//���� ��������

	stageNumber StageNumber;
public:

	HRESULT init(stageNumber Stage);
	void release(void);
	void update(void);
	void render(void);


	ThorntrapClass() {}
	~ThorntrapClass() {}
};