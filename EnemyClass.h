#pragma once
#include "gameNode.h"

//===================================
//	## 떠다니는 문어 enemy ##
//===================================
class flyOctopus : public gameNode
{
	image* enemyImage;		//적 이미지
	RECT enemyRc;			//적 렉트

	float enemyX, enemyY;	//적 좌표
	bool isDie;				//적이 죽었는가? true->죽음

	float dieCount;			//죽었을때 이미지가 작아지며 사라지게 만들 카운트
	float dieCountX;		//죽었을때 이미지가 작아지며 사라지게 만들 카운트

	bool firstStep;			//죽었을때 줄어들었다 늘어나며 사라지는 모양을 만들기위해 준 불변수

	int reviveCount;		//다시 살아날 시간

	int imgCount;			//이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트


public:
	HRESULT init(float _enemyX, float _enemyY);
	void release(void);
	void update(void);
	void render(void);

	RECT getEnemyRc() { return enemyRc; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	flyOctopus() {}
	~flyOctopus() {}
};

//===================================
//	## 기어다니는 벌레 enemy ##
//===================================
class crawlBug : public gameNode
{
	image* enemyImage;		//적 이미지
	RECT enemyRc;			//적 렉트

	float enemyX, enemyY;	//적 좌표
	float saveX, saveY;		//받아온 적의 좌표를 저장해둘 
	float enemySpeed;		//적 속도
	bool isRight;			//적이 오른쪽을 보고 있는가? true->오른쪽

	bool isDie;				//적이 죽었는가? true->죽음

	float dieCount;			//죽었을때 이미지가 작아지며 사라지게 만들 카운트
	float dieCountX;			//죽었을때 이미지가 작아지며 사라지게 만들 카운트

	bool firstStep;			//죽었을때 줄어들었다 늘어나며 사라지는 모양을 만들기위해 준 불변수

	int reviveCount;		//다시 살아날 시간
	bool isRevive;			//죽고 다시 살아나는 모습을 보여줄 불변수

	int imgCount;			//이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트

	//움직이는 적이라면 움직일 범위값을 넣어줄 변수
	int scaleLeftX;			//움직일 범위의 왼쪽 끝
	int scaleRightX;		//움직일 범위의 오른쪽 끝

public:
	HRESULT init(float _x, float _y, float _scaleLeftX, float _scaleRightX);
	void release(void);
	void update(void);
	void render(void);

	RECT getEnemyRc() { return enemyRc; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	crawlBug() {}
	~crawlBug() {}
};

//===================================
//	## 날아다니는 크리스탈 enemy ##
//===================================
class flyCrystal : public gameNode
{
	image* enemyImage;		//적 이미지
	RECT enemyRc;			//적 렉트

	float enemyX, enemyY;	//적 좌표
	float saveX, saveY;		//받아온 적의 좌표를 저장해둘 
	float enemySpeed;		//적 속도
	bool isRight;			//적이 오른쪽을 보고 있는가? true->오른쪽

	bool isDie;				//적이 죽었는가? true->죽음
	int dieCount;			//죽었을때 이미지가 깜빡이며 사라지게 만들 카운트

	int reviveCount;		//다시 살아날 시간
	bool isRevive;			//죽고 다시 살아나는 모습을 보여줄 불변수

	int imgCount;			//이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트

	//움직이는 적이라면 움직일 범위값을 넣어줄 변수
	int scaleLeftX;			//움직일 범위의 왼쪽 끝
	int scaleRightX;		//움직일 범위의 오른쪽 끝

public:
	HRESULT init(float _x, float _y, float _scaleLeftX, float _scaleRightX, bool _isRight);
	void release(void);
	void update(void);
	void render(void);

	RECT getEnemyRc() { return enemyRc; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	flyCrystal() {}
	~flyCrystal() {}
};

//===================================
//	## 둥둥이 유령 enemy ##
//===================================
class flyGhost : public gameNode
{
	image* enemyImage;		//적 이미지
	RECT enemyRc;			//적 렉트

	float enemyX, enemyY;	//적 좌표
	float enemySpeed;		//적 속도
	bool isDie;				//적이 죽었는가? true->죽음
	int reviveCount;		//다시 살아날 시간

	int imgCount;			//이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트

public:
	HRESULT init(float _x, float _y);
	void release(void);
	void update(void);

	void render(void);

	RECT getEnemyRc() { return enemyRc; }

	float getEnemyX() { return enemyX; }
	void setEnemyX(float _enemyX) { enemyX = _enemyX; }

	float getEnemyY() { return enemyY; }
	void setEnemyY(float _enemyY) { enemyY = _enemyY; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	flyGhost() {}
	~flyGhost() {}
};