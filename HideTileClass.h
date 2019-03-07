#pragma once
#include "FieldManagerClass.h"
class HideTileClass : public FieldManagerClass
{
	struct Hide
	{
		RECT rc;
		bool isTouch;
	};
	image* light;
	image* Boom;

	bool isBoom;
	int BoomFrameX;
	int BoomFrameY;

	int Count;
	int frameImgX;
	int frameImgY;
	vector<Hide>HideList;
	Hide hide;
public:
	enum class HideTile
	{
		Stage1 = 0,
		BossStage
	};

	class PlayerClass* player;
	void setPlayer(PlayerClass* play) { player = play; }

	HRESULT init(HideTile Stage);
	void release(void);
	void update(PlayerClass * player);
	void render(void);

	HideTileClass() {}
	~HideTileClass() {}
};

