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
	float enemySpeed;		//적 속도
	bool isDie;				//적이 죽었는가? true->죽음

	int imgCount;			//이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getEnemyX() { return enemyX; }
	void setEnemyX(float _enemyX) { enemyX = _enemyX; }

	float getEnemyY() { return enemyY; }
	void setEnemyY(float _enemyY) { enemyY = _enemyY; }

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
	float enemySpeed;		//적 속도
	bool isRight;			//적이 오른쪽을 보고 있는가? true->오른쪽
	bool isDie;				//적이 죽었는가? true->죽음

	int imgCount;			//이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트

	//움직이는 적이라면 움직일 범위값을 넣어줄 변수
	int scaleLeftX;			//움직일 범위의 왼쪽 끝
	int scaleRightX;		//움직일 범위의 오른쪽 끝

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getEnemyX() { return enemyX; }
	void setEnemyX(float _enemyX) { enemyX = _enemyX; }

	float getEnemyY() { return enemyY; }
	void setEnemyY(float _enemyY) { enemyY = _enemyY; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	int getScaleLeftX() { return scaleLeftX; }
	void setScaleLeftX(int _scaleLeftX) { scaleLeftX = _scaleLeftX; }

	int getScaleRightX() { return scaleRightX; }
	void setScaleRightX(int _scaleRightX) { scaleRightX = _scaleRightX; }

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
	float enemySpeed;		//적 속도
	bool isRight;			//적이 오른쪽을 보고 있는가? true->오른쪽
	bool isDie;				//적이 죽었는가? true->죽음

	int imgCount;			//이미지 카운트
	int frameX;				//이미지 x프레임 카운트
	int frameY;				//이미지 y프레임 카운트
	int stayCount;			//이미지가 잠시 머무르게 하는 시간

	//움직이는 적이라면 움직일 범위값을 넣어줄 변수
	int scaleLeftX;			//움직일 범위의 왼쪽 끝
	int scaleRightX;		//움직일 범위의 오른쪽 끝

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getEnemyX() { return enemyX; }
	void setEnemyX(float _enemyX) { enemyX = _enemyX; }

	float getEnemyY() { return enemyY; }
	void setEnemyY(float _enemyY) { enemyY = _enemyY; }

	bool getIsDie() { return isDie; }
	void setIsDie(bool _isDie) { isDie = _isDie; }

	int getScaleLeftX() { return scaleLeftX; }
	void setScaleLeftX(int _scaleLeftX) { scaleLeftX = _scaleLeftX; }

	int getScaleRightX() { return scaleRightX; }
	void setScaleRightX(int _scaleRightX) { scaleRightX = _scaleRightX; }

	flyCrystal() {}
	~flyCrystal() {}
};