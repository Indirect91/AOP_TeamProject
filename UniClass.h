#pragma once
#include "FieldManagerClass.h"

//유니 클래스 
class UniClass : public FieldManagerClass
{
public:

	enum class Jumpstate
	{
		Stage1,
		BossStage = 1
	};
private:
	//점프대 렉트
	RECT JumpRCone;
	RECT JumpRCtwo;
	//점프대 이미지
	image* JumpOne;
	image* JumpTwo;
	//이미지 카운트
	//1번
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
		image* block;
		RECT rc;
		POINT point;
		bool isTouch;
		bool isMode;
		int TouchCount;
		int Count;
		int FrameCount;
		int FrameX;
		int FrameY;
	};
	//스테이지 1번
	vector<Tile*>TileListone;
	vector<Tile*>TileListtwo;
	vector<Tile*>TileListthree;
	vector<Tile*>TileListfour;
	vector<Tile*>TileListfive;
	//보스 스테이지
	vector<Tile*>TileListBossone;
	vector<Tile*>TileListBosstwo;

	//불변수 스테이지 1번
	bool TileListoneB;
	bool TileListtwoB;
	bool TileListthreeB;
	bool TileListfourB;
	bool TileListfiveB;
	//불변수 2번째 보스스테이지
	bool TileBossoneB;
	bool TileBosstwoB;

	//enum클래스 생성
	BreakTile StageNumber;
public:
	Tile* tile;

	class PlayerClass* playerPtr;
	class FieldManagerClass* FieldPtr;
	void setPlayer(PlayerClass* play) { playerPtr = play; }
	//스테이지 1번
	vector<Tile*> getTileListone() { return TileListone; }
	vector<Tile*> getTileListtwo() { return TileListtwo; }
	vector<Tile*> getTileListthree() { return TileListthree; }
	vector<Tile*> getTileListfour() { return TileListfour; }
	vector<Tile*> getTileListfive() { return TileListfive; }
	//보스 스테이지
	vector<Tile*> getTileListBossone() { return TileListBossone; }
	vector<Tile*> getTileListBosstwo() { return TileListBosstwo; }
	//스테이지 1 불변수 겟함수
	bool getBoolTileone() { return TileListoneB; }
	bool getBoolTiletwo() { return TileListtwoB; }
	bool getBoolTilethree() { return TileListthreeB; }
	bool getBoolTilefour() { return TileListfourB; }
	bool getBoolTilefive() { return TileListfiveB; }
	//스테이지 1 불변수 셋함수
	void setBoolTileone(bool tileone) { TileListoneB = tileone; }
	void setBoolTiletwo(bool tiletwo) { TileListtwoB = tiletwo; }
	void setBoolTilethree(bool tilethree) { TileListthreeB = tilethree; }
	void setBoolTilefour(bool tilefour) { TileListfourB = tilefour; }
	void setBoolTilefive(bool tilefive) { TileListfiveB = tilefive; }
	//보스 스테이지 불변수 겟함수
	bool getBoolTileBossone() { return TileBossoneB; }
	bool getBoolTileBosstwo() { return TileBosstwoB; }
	//보스 스테이지 불변수 셋함수
	void setBoolTileBossone(bool bossone) { TileBossoneB = bossone; }
	void setBoolTileBosstwo(bool bosstwo) { TileBosstwoB = bosstwo; }




	void Stage1FrameCount();
	void BossStageFrameCount();

	HRESULT init(BreakTile Stage);
	void release(void);
	void update(void);
	void render(void);

	BreakTileClass() {}
	~BreakTileClass() {}
	void breakTileList(vector<Tile*> Tile);
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
	//알파값타일 렉트
	int imageCount;
	bool ishide;
	RECT HideRc;
	RECT HideRcTwo;
	RECT GrassRC;
	RECT BossTileRCone;
	RECT BossTileRCtwo;
	//그물 타일
	image* Vine;
	RECT VineRC;
	bool isVine;
	//알파값 타일 이미지
	image* HideBlockTwo;
	image* light;
	image* Boom;
	image* HideBlock;
	image* Grass;
	image* BossTile1;
	image* BossTile2;
	//폭탄터지는 이미지 프레임
	bool isBoom;
	int BoomFrameX;
	int BoomFrameY;
	//변신타일 이미지 프레임
	int Count;
	int frameImgX;
	int frameImgY;


	vector<Hide>HideList;
	Hide hide;
	HideTile StageNumber;
public:


	class PlayerClass* player;
	void setPlayer(PlayerClass* play) { player = play; }

	vector<Hide> &getHideTile() { return HideList; }
	void setHideTile(vector<Hide> _HideList) { HideList = _HideList; }

	int getCount() { return Count; }
	int getBoomFrameX() { return BoomFrameX; }
	bool getBoom() { return isBoom; }
	bool getIsVine() { return isVine; }
	RECT getVineRC() { return VineRC; }
	RECT getHideBlockTwo() { return HideRcTwo; }
	RECT getHideBlock() { return HideRc; }
	RECT getGrass() { return GrassRC; }
	RECT getBossTile1() { return BossTileRCone; }
	RECT getBossTile2() { return BossTileRCtwo; }
	int &refImageCount() { return imageCount; }

	image* getVineImage() { return Vine; }
	void setIsVine(bool vine) { isVine = vine; }
	void setImageCount(int imagecount) { imageCount = imagecount; }
	void setBoom(bool boom) { isBoom = boom; }
	void setBoomFrameX(int frameX) { BoomFrameX = frameX; }
	void setCount(int count) { Count = count; }

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
	//스테이지 1번
	RECT ThornOne;
	RECT ThornTwo;
	RECT ThornThree;
	RECT ThornFour;
	RECT ThornFive;
	RECT ThornSix;
	RECT ThornSeven;
	vector<RECT>ThornList;
	//보스 스테이지
	RECT ThornBossone;
	RECT ThornBosstwo;
	RECT ThornBossthree;
	RECT ThornBossfour;
	RECT ThornBossfive;
	RECT ThornBosssix;
	vector<RECT>ThornBossList;
	//이넘클래스 생성자
	stageNumber StageNumber;
public:

	class PlayerClass* player;
	void setPlayer(PlayerClass* play) { player = play; }

	vector<RECT> getThornStage1() { return ThornList; }
	vector<RECT> getThornBossStage() { return ThornBossList; }

	HRESULT init(stageNumber Stage);
	void release(void);
	void update(void);
	void render(void);


	ThorntrapClass() {}
	~ThorntrapClass() {}
};
