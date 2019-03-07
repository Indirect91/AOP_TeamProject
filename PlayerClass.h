#pragma once
#include "gameNode.h"
//센서 구조체(픽셀충돌을 위한 센서)
struct tagSensor
{
	RECT sensorRc;			//센서 렉트
	float x, y;				//센서 중심좌표
	bool isJump;			//점프를 위한 불변수
	bool isTouch;			//센서가 충돌중인가?

};
class PlayerClass : public gameNode
{
private:
	//플레이어 행동 상태처리를 위한 이넘문~
	enum tagEnum
	{
		IDLE,					//플레이어 대기
		RUN,					//플레이어 뛰기
		ATTACK,					//플레이어 공격
		JUMP,					//플레이어 점프
		GRAB,					//플레이어 벽잡기
		DOWNATTACK				//플레이어 아래공격
	};
private:
	//플레이어 변수
	RECT playerRc;				//플레이어 렉트
	RECT attackRc;				//공격시 판정 렉트
	float x, y;					//플레이어 좌표
	float width;				//플레이어 가로
	float height;				//플레이어 세로
	float speed;				//플레이어 스피드
	float gravity;				//중력
	float addtionalPower;		//가변점프를 위한 추가적인 파워
	float leftPower;			//반발력 점프를 위한 왼쪽에서 끌어당기는 힘
	float rightPower;			//반발력 점프를 위한 오른쪽에서 끌어당기는 힘
	int imgCount;				//이미지 프레임 시간
	int imgIndex;				//이미지 인덱스 접근
	bool isAttack;				//공격을 했는지 판단
	bool isAttackOrMove;		//공격중엔 이동불가
	bool isLeft;				//좌우 프레임 이미지 구분을 위한 변수
	bool isJumpCheck;			//점프 프레임 이미지를 위한 변수
	bool isWallGrab;			//벽을 잡고있는지?
	string CollisionStage;		//어느 스테이지와 충돌중인지

	tagEnum playerState;		//플레이어 상태 (프레임 이미지 돌릴꺼임)

	//젤리 변수
	//RECT jellyRc;				//젤리 캐릭터 렉트
	//float x, y;					//젤리 좌표
	//float width;				//플레이어 가로
	//float height;				//플레이어 세로
	//float speed;				//플레이어 스피드
	//float gravity;				//중력
	//float addtionalPower;		//가변점프를 위한 추가적인 파워

	//센서 생성(상 하 좌 우)
	tagSensor sensorLeft;
	tagSensor sensorTop;
	tagSensor sensorRight;

	tagSensor sensorBottom;			//지금 안씀
	tagSensor sensorRightBottom;	//
	tagSensor sensorLeftBottom;
	//센서 대각선
	tagSensor sensorLeftDiagonal;
	tagSensor sensorRightDiagonal;

public:

	HRESULT init(float x, float y, string stage);
	void release(void);
	void update(void);
	void render(void);

	//겟,셋 함수//
	RECT getRect() { return playerRc; }
	RECT getAttackRect() { return attackRc; }
	float getX() { return x; }
	float getY() { return y; }
	float getLeftPower() { return leftPower; }
	float getRightPower() { return rightPower; }
	float getGravity() { return gravity; }
	void setGravity(float _gravity) { gravity = _gravity; }


	// 함수 //
	void playerMove();			//플레이어 움직임에 대한 함수(이동,점프)
	void playerAttack();		//플레이어 공격~
	void sensorMove();			//플레이어를 따라다니는 센서의 움직임에 대한 함수
	void pixelCollision();		//센서가 픽셀충돌 감지

	void playerStateFrameImageRender(float x, float y);		//프레임 이미지 렌더를 위한 함수

	RECT getSensorRcBottom() { return sensorBottom.sensorRc; }

	PlayerClass() {};
	~PlayerClass() {};
};

