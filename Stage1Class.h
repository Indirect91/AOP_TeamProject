#pragma once
#include "gameNode.h"

class Stage1Class : public gameNode
{
private:

	//스테이지 이미지
	image * stage1Img;
	image * stage1CollisionImg;

	//배경 이미지
	float loopX1, loopY1;		//배경 이미지 1의 루프좌표
	float loopX2, loopY2;		//배경 이미지 2의 루프좌표
	float loopX3, loopY3;		//배경 이미지 3의 루프좌표
	float loopX4, loopY4;		//배경 이미지 4의 루프좌표

	class PlayerClass* playerPtr;				//스테이지1에 있는 플레이어 클래스 포인터
	
	class EnemyManagerClass* s1EnemyMPtr;		//스테이지1에 있는 적 매니저 클래스 포인터
	vector < EnemyManagerClass*> s1EnemyMPtrV;	//스테이지1에 있는 적 매니저 클래스 포인터를 담는 벡터
	
	class PetsClass* s1PetPtr;					//스테이지1에 있는 펫 클래스 포인터
	vector <PetsClass*> s1PetPtrV;				//스테이지1에 있는 펫 클래스 포인터를 담는 벡터
	
	class FieldManagerClass* fieldPtr;

	class savePoint* s1SaveMPtr;				//스테이지1에 있는 세이브포인터 클래스 포인터
	vector <savePoint*> s1SaveMPtrV;			//스테이지1에 있는 세이브포인터 클래스 포인터를 담는 벡터

	class treasureBox* s1TreasurePtr;			//스테이지1에 있는 보물상자 클래스 포인터
	vector <treasureBox*> s1TreasurePtrV;		//스테이지1에 있는 보물상자 클래스 포인터를 담는 벡터

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Stage1Class() {};
	~Stage1Class() {};
};

