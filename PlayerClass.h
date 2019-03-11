#pragma once
#include "gameNode.h"
//센서 구조체
struct tagSensor
{
	RECT sensorRc;					//센서 렉트
	float x, y;						//중점 좌표
	bool isJump;					//점프를 하고있는지 판단
	bool isTouch;					//센서가 터치 중인지 판단
};
class PlayerClass : public gameNode
{
private:
	enum playerState		//플레이어 상태(이미지)
	{
		//왼쪽 
		LEFTIDLE,
		LEFTRUN,
		LEFTATTACK,
		LEFTJUMPUP,
		LEFTJUMPDOWN,
		LEFTGRAB,
		LEFTDOWNATTACK,
		LEFTCHANGEFORM,
		//오른쪽
		RIGHTIDLE,
		RIGHTRUN,
		RIGHTATTACK,
		RIGHTJUMPUP,
		RIGHTJUMPDOWN,
		RIGHTGRAB,
		RIGHTDOWNATTACK,
		RIGHTCHANGEFORM,
	};
	enum changeFormEnum			//플레이어가 변신 상태
	{
		//젤리
		JELLYIDLE,
		JELLYMOVE,
		JELLYJUMPUP,
		JELLYJUMPDOWN
	};
private:

	//플레이어
	RECT playerRc;					//플레이어 렉트
	RECT changeEffectRc;			//변신 이펙트 씌울 렉트
	RECT attackRc;					//공격 판정 렉트
	RECT fireWall;					//파이어월 렉트?
	RECT tileDestory;				//부서지는 타일 부시는 렉트
	float x, y;						//플레이어 좌표
	float width;					//플레이어 가로
	float height;					//플레이어 세로
	float speed;					//플레이어 스피드
	float jellySpeed;				//젤리 스피드
	float gravity;					//중력
	float addtionalPower;			//가변점프 파워
	float leftRepulsivePower;		//왼쪽에서 당기는 힘(반발력)
	float rightRepulsivePower;		//오른쪽에서 당기는 힘(반발력)
	float changeCount;				//변신 시간
	int imgCount;					//이미지 프레임 돌릴 카운트
	int imgIndex;					//이미지 프레임 인덱스 돌릴 카운트
	int BombCount;				//변신할때 터지는 공격 사라지게 할 카운트
	bool isBombCount;
	//int frameCount;				
	bool isRepusiveCheck;			//반발력 점프
	bool isLeftRepulsive;			//왼쪽으로 반발력을 줄것인가?
	bool changeForm;				//젤리 핍인가? 픽셀 핍인가?
	bool isLeft;					//왼쪽인지 판단
	bool isAttack;					//공격중인가?
	bool isDownAttack;				//다운 공격 중인가?
	bool isChange;					//변신중인가?

	string CollisionStage;			//스테이지 이름을 담기위해

	//센서 
	tagSensor sensorBottom;			//아래
	tagSensor sensorTop;			//위
	tagSensor sensorLeft;			//왼쪽
	tagSensor sensorRight;			//오른쪽
	tagSensor sensorLeftTop;		//왼쪽 대각선
	tagSensor sensorRightTop;		//오른쪽 대각선

	// Enum //
	playerState playerStateEnum;
	changeFormEnum jellyState;

public:

	HRESULT init(float _x, float _y, string _collisionStage);
	void release(void);
	void update(void);
	void render(void);

	RECT getRect() { return playerRc; }
	RECT getSensorRcBottom() { return sensorBottom.sensorRc; }
	RECT getSensorRcTop() { return sensorTop.sensorRc; }
	RECT getSensorRcRight() { return sensorRight.sensorRc; }
	RECT getSensorRcLeft() { return sensorLeft.sensorRc; }
	RECT getAttackRc() { return attackRc; }
	int getBombCount() { return BombCount; }
	float getX() { return x; }
	float getY() { return y; }
	float getLeftRepulsiver() { return leftRepulsivePower; }
	float getRightRepulsive() { return rightRepulsivePower; }
	float getGravity() { return gravity; }
	float getChangeCount() { return changeCount; }
	bool getChangeForm() { return changeForm; }
	bool getIsAttack() { return isAttack; }
	void setX(float _x) { x -= _x; }
	void setChangeForm(bool _changeForm) { changeForm = _changeForm; }
	void setGravity(float _gravity) { gravity = _gravity; }

	void playerMove();					//플레이어(픽셀 핍) 움직임
	void playerAttack();				//플레이어 공격
	void sensorMove();					//센서 움직임
	void pixelCollision();				//픽셀 충돌
	void repulsive();					//반발력
	void transForm();					//변신하기
	void jellyMove();					//플레이어(젤리 핍) 움직임

	void sensorPixelCollisionCheck();						//센서가 충돌이 되고있는지 체크

	void playerStateFrameImageRender(float x, float y);		//프레임 이미지 렌더를 위한 함수

	PlayerClass() {};
	~PlayerClass() {};
};

