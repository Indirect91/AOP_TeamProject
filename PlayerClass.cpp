#include "stdafx.h"
#include "PlayerClass.h"

/*====================================================
						init()
======================================================*/
HRESULT PlayerClass::init(float _x, float _y, string _collisionStage)
{
	//플레이어 초기화
	x = _x;										//플레이어 죄표x
	y = _y;										//플레이어 좌표y
	width = 50;									//플레이어 가로
	height = 50;								//플레이어 세로
	speed = 5.0f;								//플레이어 스피드
	jellySpeed = 4.0f;							//젤리 스피드
	gravity = 0.0f;								//중력
	addtionalPower = 0.0f;						//가변점프 파워
	leftRepulsivePower = 0.0f;					//왼쪽에서 당기는 반발력
	rightRepulsivePower = 0.0f;					//오른쪽에서 당기는 반발력
	imgCount = 0;								//이미지 프레임 돌리기
	imgIndex = 0;								//프레임 이미지 인덱스 접근
	changeCount = 0.0f;							//변신 시간
	isRepusiveCheck = false;					//반발력 체크
	isLeftRepulsive = false;					//반발략을 어느 부분으로 줄것인가?
	changeForm = false;							//젤리 핍인가? 픽셀 핍인가?
	isLeft = false;								//왼쪽? 오른쪽? 방향 판단
	isAttack = false;							//공격중인가?
	isDownAttack = false;
	//isChange = false;							//이동중 공격 못하게
	CollisionStage = _collisionStage;			//인자 값으로 받아온 이미지 담기~

#pragma region 센서 초기화
	//센서 초기화
	sensorBottom.x = x + width / 2;				//센서 x위치 초기화
	sensorBottom.y = y + height;				//센서 y위치 초기화
	sensorBottom.isJump = false;				//센서 점프 bool변수 초기화
	sensorBottom.isTouch = false;				//센서 터치 bool변수 초기화

	sensorLeft.x = x;							//센서 x위치 초기화
	sensorLeft.y = y + height / 2;				//센서 y위치 초기화
	sensorLeft.isJump = false;					//센서 점프 bool변수 초기화
	sensorLeft.isTouch = false;					//센서 터치 bool변수 초기화

	sensorRight.x = x + width;					//센서 x위치 초기화
	sensorRight.y = y + height / 2;				//센서 y위치 초기화
	sensorRight.isJump = false;					//센서 점프 bool변수 초기화
	sensorRight.isTouch = false;				//센서 터치 bool변수 초기화

	sensorTop.x = x + width / 2;				//센서 x위치 초기화
	sensorTop.y = y;							//센서 y위치 초기화
	sensorTop.isJump = false;					//센서 점프 bool변수 초기화
	sensorTop.isTouch = false;					//센서 터치 bool변수 초기화

	sensorLeftTop.x = x;						//센서 x위치 초기화
	sensorLeftTop.y = y;						//센서 y위치 초기화
	sensorLeftTop.isJump = false;				//센서 점프 bool변수 초기화
	sensorLeftTop.isTouch = false;				//센서 터치 bool변수 초기화

	sensorRightTop.x = x + width;				//센서 x위치 초기화
	sensorRightTop.y = y;						//센서 y위치 초기화
	sensorRightTop.isJump = false;				//센서 점프 bool변수 초기화
	sensorRightTop.isTouch = false;				//센서 터치 bool변수 초기화
#pragma endregion
	frme = 0;
	counter = 0;
	suckHan = 50;
	return S_OK;
}

/*====================================================
						release()
=====================================================*/
void PlayerClass::release(void)
{
}

/*====================================================
						update()
======================================================*/
void PlayerClass::update(void)
{
	//상시 중력
	gravity += 0.4f;

	if (!changeForm)
	{
		this->playerMove();							//플레이어 움직임
		this->playerAttack();
	}

	this->sensorMove();								//센서 움직임
	this->pixelCollision();							//픽셀 충돌
	this->repulsive();								//반발력

	//변신
	if (KEYMANAGER->isStayKeyDown('L'))
	{
		changeCount += 0.05f;

		if (!isLeft) playerStateEnum = playerState::LEFTCHANGEFORM;
		else playerStateEnum = playerState::RIGHTCHANGEFORM;
	}
	if (KEYMANAGER->isOnceKeyUp('L'))
	{
		if (changeCount <= 2.0f)
		{
			changeCount = 0.0f;
		}
	}

	if (changeCount >= 2.0f)
	{
		changeCount = 2.0f;
		changeForm = true;
	}

	if (changeForm)
	{
		this->jellyMove();
	}

	//중력을 제일 마지막에 더해줘야한다.
	y += gravity;

	//반발력이 존재하면 당겨당겨~
	x -= leftRepulsivePower;
	x += rightRepulsivePower;

}

/*============================================================
						render()
==============================================================*/
void PlayerClass::render(void)
{
	counter++;
	if (KEYMANAGER->isToggleKey('Q'))
	{
		//플레이어
		Rectangle(getMemDC(), RelativeCameraRect(playerRc));

		//픽셀 충돌시 체크
		this->sensorPixelCollisionCheck();
	}

	
	if (counter>15&&counter<115)
	{
		frme++;
		if (frme % 15 == 0)
		{
			
			if (frme > 16)
			{
				frme = 16;
			}
		}
	}
	else
	{
		frme--;
		if (frme % 10 == 0)
		{
			if (frme < 0)
			{
				frme = 0;
			}
		}
	}
	IMAGEMANAGER->addFrameImage("portl", "2312,308_ 복사본.bmp", 2312, 308, 17, 1, true, RGB(255, 0, 255))->stretchFrameRenderCenterXDownY(getMemDC(), 60, 80, frme, 0, 1, 2);


	this->playerStateFrameImageRender((x + 5), (y - 20));
}

/*=============================================================
			playerMove() - 플레이어 움직임 -
===============================================================*/
void PlayerClass::playerMove()
{
	//!isLeft ? playerStateEnum = RIGHTIDLE : playerStateEnum = LEFTIDLE;

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//공격중이지 않으면 이동가능 // 점프(true) 공격(true) 이동 가능
		if (!isAttack)
		{
			x += speed;
			isLeft = true;
			if (isLeft) playerStateEnum = playerState::RIGHTRUN;
		}

		if (!sensorBottom.isTouch)
		{
			if (isAttack)
			{
				x += speed;
				isLeft = true;
			}
		}
	}
	else
	{
		playerStateEnum = playerState::RIGHTIDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!isAttack)
		{
			x -= speed;
			isLeft = false;
			playerStateEnum = playerState::LEFTRUN;
		}

		if (!sensorBottom.isTouch)
		{
			if (isAttack)
			{
				x -= speed;
				isLeft = false;
			}
		}
	}
	else
	{
		if (!isLeft) playerStateEnum = playerState::LEFTIDLE;
	}

	if (!sensorBottom.isJump)												//바텀의 센서 점프 bool변수가 false면 아래의 기능을 사용 할 수 있다.
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			y -= 10;														//점프하기 전에 y축을 살짝 이격시킨다.
			gravity = -6.0f;												//중력을 역전 시켜서 점프

			//반발력
			if (isRepusiveCheck && !sensorBottom.isTouch)					//반발력을 줄것인지?
			{
				if (isLeftRepulsive && !sensorLeftTop.isTouch)				//왼쪽으로 반발력을 준다면
				{
					x += 10;												//x축을 살짝 이격 시킨후
					rightRepulsivePower = 5.5f;								//반발력을 준다.
					isLeft = true;
				}
				else if (!isLeftRepulsive && !sensorRightTop.isTouch)		//오른쪽으로 반발력을 준다면
				{
					x -= 10;												//x축을 살짝 이격 시킨후
					leftRepulsivePower = 5.5f;								//반발력을 준다.
					isLeft = false;
				}
			}
		}
		if (KEYMANAGER->isStayKeyDown('K'))
		{
			//가변 점프(C키를 꾹 누르고 있으면 가변 점프 파워가 증가를 하게 된다.(최대치 존재))
			if (addtionalPower <= 1.6f)										//가변점프 파워가 1.6f 이하라면
			{
				addtionalPower += 0.2f;										//가변점프 파워 증가
			}
			if (addtionalPower <= 1.6f)										//가변점프 파워가 1.6f 이하라면
			{
				gravity -= addtionalPower;									//증가한 가변점프 파워를 점프 중력에 추가해 점프를 높게 뛸수 있도록 해준다
			}

		}
		if (KEYMANAGER->isOnceKeyUp('K'))
		{
			sensorBottom.isJump = true;										//이중 점프를 막기위해 bool변수 true
			addtionalPower = 0.0f;											//가변점프 파워 다시 초기화
		}
	}
	if (!sensorBottom.isTouch)
	{
		if (!isLeft)
		{
			if (gravity < 0) playerStateEnum = playerState::LEFTJUMPUP;
			else playerStateEnum = playerState::LEFTJUMPDOWN;
		}
		else
		{
			if (gravity < 0) playerStateEnum = playerState::RIGHTJUMPUP;
			else playerStateEnum = playerState::RIGHTJUMPDOWN;
		}
	}

	//플레이어 지속 업데이트
	playerRc = RectMake(x, y, width, height);
}

/*=============================================================
			playerAttack() - 플레이어 공격 -
===============================================================*/
void PlayerClass::playerAttack()
{
	//플레이어 일반 공격
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		imgIndex = 12;
		isAttack = true;
	}

	if (isAttack && !isLeft)
	{
		playerStateEnum = playerState::LEFTATTACK;
	}
	else if (isAttack && isLeft)
	{
		playerStateEnum = playerState::RIGHTATTACK;
	}

	//플레이어 다운공격
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		isDownAttack = true;
	}

	if (isDownAttack && !isLeft)
	{
		playerStateEnum = PlayerClass::LEFTDOWNATTACK;
	}
	else if (isDownAttack && isLeft)
	{
		playerStateEnum = PlayerClass::LEFTDOWNATTACK;
	}

}

/*==============================================================
			sensorMove() - 센서 움직임 -
================================================================*/
void PlayerClass::sensorMove()
{
#pragma region 센서 위치 지속 업데이트
	sensorBottom.x = x + width / 2;
	sensorBottom.y = y + height;
	sensorBottom.isTouch = false;

	sensorLeft.x = x;
	sensorLeft.y = y + height / 2;
	sensorLeft.isTouch = false;

	sensorRight.x = x + width;
	sensorRight.y = y + height / 2;
	sensorRight.isTouch = false;

	sensorTop.x = x + width / 2;
	sensorTop.y = y;
	sensorTop.isTouch = false;

	sensorLeftTop.x = x;
	sensorLeftTop.y = y;
	sensorLeftTop.isTouch = false;

	sensorRightTop.x = x + width;
	sensorRightTop.y = y;
	sensorRightTop.isTouch = false;
#pragma endregion

	//센서 지속 업데이트
	sensorBottom.sensorRc = RectMakeCenter(sensorBottom.x, sensorBottom.y, 40, 5);
	sensorLeft.sensorRc = RectMakeCenter(sensorLeft.x, sensorLeft.y, 5, 40);
	sensorRight.sensorRc = RectMakeCenter(sensorRight.x, sensorRight.y, 5, 40);
	sensorTop.sensorRc = RectMakeCenter(sensorTop.x, sensorTop.y, 40, 5);
	sensorLeftTop.sensorRc = RectMakeCenter(sensorLeftTop.x, sensorLeftTop.y, 5, 5);
	sensorRightTop.sensorRc = RectMakeCenter(sensorRightTop.x, sensorRightTop.y, 5, 5);
}

/*==============================================================
			pixelCollision() - 픽셀 충돌 -
================================================================*/
void PlayerClass::pixelCollision()
{
	//바텀 픽셀 충돌(Bottom)
	for (int i = sensorBottom.y - 5; i < sensorBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//바텀센서 X 픽셀(노란색)
		if (r == 255 && g == 255 && b == 0)
		{
			y = i - height;						//y축 위치보정
			gravity = 0.0f;						//중력 0으로~
			sensorBottom.isTouch = true;		//현재 픽셀 충돌중인지 체크
			sensorBottom.isJump = false;		//픽셀 충돌중이면 언제든지 점프
			isRepusiveCheck = false;			//벽점프가 아닌 점프 할 때 반발력을 안주게 하기 위해
			//if(isAttack) isAttack = false;
			break;
		}

		//바텀 센서 X 무너지는 타일
		if (r == 91 && g == 63 && b == 34)
		{
			y = i - height;
			gravity = 0.0f;						//중력 0으로~
			sensorBottom.isTouch = true;		//현재 픽셀 충돌중인지 체크
			sensorBottom.isJump = false;		//픽셀 충돌중이면 언제든지 점프
			isRepusiveCheck = false;			//벽점프가 아닌 점프 할 때 반발력을 안주게 하기 위해
			break;
		}

		//바텀 센서 X 나무타일
		if (r == 255 && g == 94 && b == 0)
		{
			y = i - height;
			gravity = 0.0f;						//중력 0으로~
			sensorBottom.isTouch = true;		//현재 픽셀 충돌중인지 체크
			sensorBottom.isJump = false;		//픽셀 충돌중이면 언제든지 점프
			isRepusiveCheck = false;			//벽점프가 아닌 점프 할 때 반발력을 안주게 하기 위해
			break;
		}

		//바텀센서 X 변신으로 부서지는 타일
		if (r == 126 && g == 206 && b == 244)
		{
			y = i - height;
			gravity = 0.0f;						//중력 0으로~
			sensorBottom.isTouch = true;		//현재 픽셀 충돌중인지 체크
			sensorBottom.isJump = false;		//픽셀 충돌중이면 언제든지 점프
			isRepusiveCheck = false;			//벽점프가 아닌 점프 할 때 반발력을 안주게 하기 위해
			break;
		}

		//바텀센서 X 끊어지는 타일
		if (r == 149 && g == 149 && b == 149)
		{
			y = i - height;
			gravity = 0.0f;						//중력 0으로~
			sensorBottom.isTouch = true;		//현재 픽셀 충돌중인지 체크
			sensorBottom.isJump = false;		//픽셀 충돌중이면 언제든지 점프
			isRepusiveCheck = false;			//벽점프가 아닌 점프 할 때 반발력을 안주게 하기 위해
			break;
		}
	}

	//오른쪽 픽셀 충돌(Right)
	for (int i = sensorRight.x - 5; i < sensorRight.x + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), i, sensorRight.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//오른쪽 센서 X 픽셀(파란색)
		if (r == 0 && g == 0 && b == 255)
		{
			x = i - width;						//x축 위치 보정
			isLeftRepulsive = false;			//반발력을 어느방향으로 줄 것인가?(왼쪽으로 줄거임)
			rightRepulsivePower = 0.0f;			//반발력 파워가 항시 존재하면 안되니까 0으로 초기화
			isRepusiveCheck = true;				//벽점프를 할 수 있도록 
			sensorBottom.isJump = false;		//벽에 닿으면 점프를 할 수 있어야 하니까
			sensorRight.isTouch = true;			//오른쪽 센서가 충돌이 되고있는지?

			if (!sensorBottom.isTouch && sensorRight.isTouch && gravity > 0)
			{
				playerStateEnum = playerState::RIGHTGRAB;
			}

			if (gravity > 15.0f)
			{
				gravity = 15.0f;
			}
			if (!changeForm)
			{
				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					gravity = 0.0f;					//벽잡을 하는 중이니 중력 0
				}
			}
			break;
		}

		//노란색과 충돌시
		if (r == 255 && g == 255 && b == 0)
		{
			x = i - width;						//위치 보정
			break;
		}
		//검정색과 충돌시
		if (r == 0 && g == 0 && b == 0)
		{
			x = i - width;						//위치 보정
			break;
		}

	}

	//왼쪽 픽셀 충돌(Left)
	for (int i = sensorLeft.x + 5; i > sensorLeft.x - 5; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), i, sensorLeft.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//왼쪽 센서 X 픽셀(연두)
		if (r == 0 && g == 255 && b == 0)
		{

			x = i;								//x축 위치 보정
			isLeftRepulsive = true;				//반발력을 어느방향으로 줄 것인가?(오른쪽으로 줄거임)
			leftRepulsivePower = 0.0f;			//반발력 파워가 항시 존재하면 안되니까 0으로 초기화
			isRepusiveCheck = true; 			//벽점프를 할 수 있도록 
			sensorBottom.isJump = false;		//벽에 닿으면 점프를 할 수 있어야 하니까
			sensorLeft.isTouch = true;			//왼쪽 센서가 충돌이 되고있는지?

			if (!sensorBottom.isTouch && sensorLeft.isTouch && gravity > 0)
			{
				playerStateEnum = playerState::LEFTGRAB;
			}

			if (gravity > 15.0f)
			{
				gravity = 15.0f;
			}
			if (!changeForm)
			{
				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					gravity = 0.0f;					//벽잡을 하는 중이니 중력을 0
				}
			}
			break;
		}
		//노란색과 충돌시 
		if (r == 255 && g == 255 && b == 0)
		{
			x = i;								//위치 보정
			break;
		}
		//검정색과 충돌시
		if (r == 0 && g == 0 && b == 0)
		{
			x = i;								//위치 보정
			break;
		}
	}

	//탑 픽셀 충돌(Top)
	for (int i = sensorTop.y - 5; i < sensorTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//탑 센서 X 픽셀(검정)
		if (r == 0 && g == 0 && b == 0)
		{
			y += 5;								//y축을 이격시켜준다.
			gravity = 0.0f;						//중력을 0으로 만들어 자연스럽게 떨어지게
			sensorTop.isTouch = true;			//탑 센서가 충돌 중인지?
			break;
		}
	}

	//오른쪽 대각선 픽셀 충돌(RightTop)
	for (int i = sensorRightTop.y - 5; i < sensorRightTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorRightTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (!changeForm)
		{
			//오른쪽 대각 센서 X 픽셀(보라)
			if (r == 96 && g == 25 && b == 134)
			{
				gravity = 0.0f;								//모서리에 매달리고 있으니 중력 0
				sensorRightTop.isTouch = true;				//오른쪽 모서리 센서가 충돌중인지?
				sensorBottom.isJump = false;				//모서리 잡은후 점프 가능하게

				if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
				{
					y += 20;								//Down버튼 누를시 내려올수 있게
				}
			}
		}
	}

	//왼쪽 대각선 픽셀 충돌(LeftTop)
	for (int i = sensorLeftTop.y - 5; i < sensorLeftTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorLeftTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!changeForm)
		{
			//왼쪽 대각 센서 X 픽셀(보라)
			if (r == 96 && g == 25 && b == 134)
			{
				gravity = 0.0f;								//모서리에 매달리고 있으니 중력 0
				sensorLeftTop.isTouch = true;				//왼쪽 모서리 센서가 충돌중인지?
				sensorBottom.isJump = false;				//모서리 잡은후 점프 가능하게

				if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
				{
					y += 20;								//Down버튼 누를시 내려올수 있게
				}
			}
		}
	}
}

/*==============================================================
			repulsive() - 반발력 -
================================================================*/
void PlayerClass::repulsive()
{
	//반발력 힘(왼쪽)
	if (leftRepulsivePower > 0)							//왼쪽 반발력 힘이 0 이상이면
	{
		leftRepulsivePower -= 0.1f;						//힘을 계속 깎아 준다.
	}
	else
	{
		leftRepulsivePower = 0.0f;						//반발력 힘이 음수(-)이면 0으로 유지
	}
	//반발력 힘(오른쪽)
	if (rightRepulsivePower > 0)						//오른쪽 반발력 힘이 0 이상이면
	{
		rightRepulsivePower -= 0.1f;					//힘을 계속 깎아 준다.
	}
	else
	{
		rightRepulsivePower = 0.0f;						//반발력 힘이 음수(-)이면 0으로 유지
	}
}

/*==============================================================
			jellyMove() - 젤리 움직임 -
================================================================*/
void PlayerClass::jellyMove()
{
	jellyState = changeFormEnum::JELLYIDLE;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		x += jellySpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		x -= jellySpeed;
	}

	if (!sensorBottom.isJump)												//바텀의 센서 점프 bool변수가 false면 아래의 기능을 사용 할 수 있다.
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			y -= 10;														//점프하기 전에 y축을 살짝 이격시킨다.
			gravity = -6.0f;												//중력을 역전 시켜서 점프
		}
		if (KEYMANAGER->isStayKeyDown('K'))
		{
			//가변 점프(C키를 꾹 누르고 있으면 가변 점프 파워가 증가를 하게 된다.(최대치 존재))
			if (addtionalPower <= 1.6f)										//가변점프 파워가 1.6f 이하라면
			{
				addtionalPower += 0.2f;										//가변점프 파워 증가
			}
			if (addtionalPower <= 1.6f)										//가변점프 파워가 1.6f 이하라면
			{
				gravity -= addtionalPower;									//증가한 가변점프 파워를 점프 중력에 추가해 점프를 높게 뛸수 있도록 해준다
			}
			//젤리 점프~
			if (gravity > 0)												//젤리 점프 천천히 떨어지기
			{
				gravity -= 0.3f;											//현재 작용되고있는 중력에서 빼준다.
			}
		}
		if (KEYMANAGER->isOnceKeyUp('K'))
		{
			sensorBottom.isJump = true;										//이중 점프를 막기위해 bool변수 true
			addtionalPower = 0.0f;											//가변점프 파워 다시 초기화
		}
	}
	if (!sensorBottom.isTouch)
	{
		if (gravity < 0) jellyState = changeFormEnum::JELLYJUMPUP;
		else jellyState = changeFormEnum::JELLYJUMPDOWN;
	}

	//플레이어 지속 업데이트
	playerRc = RectMake(x, y, width, height);
}

/*==============================================================
	sensorPixelCollisionCheck() - 센서 충돌 체크 -
================================================================*/
void PlayerClass::sensorPixelCollisionCheck()
{
	//센서 렌더(픽셀 충돌 중이면 빨간색 | 충돌중이 아니면 하늘색)
	if (sensorBottom.isTouch)
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		RECT temp = RelativeCameraRect(sensorBottom.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	else
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
		RECT temp = RelativeCameraRect(sensorBottom.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	//
	if (sensorLeft.isTouch)
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		RECT temp = RelativeCameraRect(sensorLeft.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	else
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
		RECT temp = RelativeCameraRect(sensorLeft.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	//
	if (sensorRight.isTouch)
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		RECT temp = RelativeCameraRect(sensorRight.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	else
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
		RECT temp = RelativeCameraRect(sensorRight.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	//
	if (sensorTop.isTouch)
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		RECT temp = RelativeCameraRect(sensorTop.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	else
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
		RECT temp = RelativeCameraRect(sensorTop.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	//
	if (sensorLeftTop.isTouch)
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		RECT temp = RelativeCameraRect(sensorLeftTop.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	else
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
		RECT temp = RelativeCameraRect(sensorLeftTop.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	//
	if (sensorRightTop.isTouch)
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		RECT temp = RelativeCameraRect(sensorRightTop.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	else
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
		RECT temp = RelativeCameraRect(sensorRightTop.sensorRc);
		FillRect(getMemDC(), &temp, brush);
		DeleteObject(brush);
	}
	//
}

/*==============================================================
playerStateFrameImageRender(float x, float y) - 행동 상태 처리 -
================================================================*/
void PlayerClass::playerStateFrameImageRender(float x, float y)
{
	if (!changeForm)
	{
		switch (playerStateEnum)
		{
		case PlayerClass::LEFTIDLE:
			IMAGEMANAGER->findImage("pipIdle")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 14)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipIdle")->setFrameX(imgIndex);
			}
			//IMAGEMANAGER->findImage("pipIdle")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			if (suckHan <= 1)
				suckHan = 1;
			else
				suckHan -= 1;
			IMAGEMANAGER->findImage("pipIdle")->stretchFrameRenderCenterXDownY(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top, IMAGEMANAGER->findImage("pipIdle")->getFrameX(), IMAGEMANAGER->findImage("pipIdle")->getFrameY(), 1.0f, suckHan);
			
			break;

		case PlayerClass::LEFTRUN:
			IMAGEMANAGER->findImage("pipRun")->setFrameY(1);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 11)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipRun")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipRun")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::LEFTATTACK:
			IMAGEMANAGER->findImage("pipAttackLeft")->setFrameY(0);
			imgCount++;
			if (imgCount % 4 == 0)
			{
				imgIndex--;
				if (imgIndex < 0)
				{
					imgIndex = 11;
					isAttack = false;
				}
				if (isAttack) IMAGEMANAGER->findImage("pipAttackLeft")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipAttackLeft")->frameRender(getMemDC(), (x - 47) - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::LEFTJUMPUP:
			IMAGEMANAGER->findImage("pipJumpUp")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 6)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipJumpUp")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipJumpUp")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::LEFTJUMPDOWN:
			IMAGEMANAGER->findImage("pipJumpDown")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 5)

				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipJumpDown")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipJumpDown")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::LEFTGRAB:
			IMAGEMANAGER->findImage("pipGrabLeft")->render(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::LEFTDOWNATTACK:
			IMAGEMANAGER->findImage("pipDownAttack")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 10)
				{
					imgIndex = 0;
					isDownAttack = false;
				}
				if (!isDownAttack) IMAGEMANAGER->findImage("pipDownAttack")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipDownAttack")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::LEFTCHANGEFORM:
			IMAGEMANAGER->findImage("pipChangeForm")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 9)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipChangeForm")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipChangeForm")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

			//오른쪽
		case PlayerClass::RIGHTIDLE:
			IMAGEMANAGER->findImage("pipIdle")->setFrameY(1);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 14)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipIdle")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipIdle")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::RIGHTRUN:
			IMAGEMANAGER->findImage("pipRun")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 11)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipRun")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipRun")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::RIGHTATTACK:
			IMAGEMANAGER->findImage("pipAttackRight")->setFrameY(0);
			imgCount++;
			if (imgCount % 3 == 0)
			{
				imgIndex--;
				if (imgIndex < 0)
				{
					imgIndex = 11;
					isAttack = false;
				}
				if (isAttack) IMAGEMANAGER->findImage("pipAttackRight")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipAttackRight")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::RIGHTJUMPUP:
			IMAGEMANAGER->findImage("pipJumpUp")->setFrameY(1);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 6)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipJumpUp")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipJumpUp")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::RIGHTJUMPDOWN:
			IMAGEMANAGER->findImage("pipJumpDown")->setFrameY(1);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 5)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipJumpDown")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipJumpDown")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::RIGHTGRAB:
			IMAGEMANAGER->findImage("pipGrabRight")->render(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::RIGHTDOWNATTACK:
			IMAGEMANAGER->findImage("pipDownAttack")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 10)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("pipDownAttack")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipDownAttack")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;

		case PlayerClass::RIGHTCHANGEFORM:
			IMAGEMANAGER->findImage("pipChangeForm")->setFrameY(1);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex--;
				if (imgIndex < 0)
				{
					imgIndex = 9;
				}
				IMAGEMANAGER->findImage("pipChangeForm")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("pipChangeForm")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (jellyState)
		{
		case PlayerClass::JELLYIDLE:
			IMAGEMANAGER->findImage("jellyStay")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 7)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("jellyStay")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("jellyStay")->frameRender(getMemDC(), x - CAMERA.getCRc().left, (y + 30) - CAMERA.getCRc().top);
			break;
		case PlayerClass::JELLYJUMPUP:
			IMAGEMANAGER->findImage("jellyJumpUp")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 7)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("jellyJumpUp")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("jellyJumpUp")->frameRender(getMemDC(), x - CAMERA.getCRc().left, (y + 30) - CAMERA.getCRc().top);
			break;
		case PlayerClass::JELLYJUMPDOWN:
			IMAGEMANAGER->findImage("jellyJumpDown")->setFrameY(0);
			imgCount++;
			if (imgCount % 5 == 0)
			{
				imgIndex++;
				if (imgIndex > 10)
				{
					imgIndex = 0;
				}
				IMAGEMANAGER->findImage("jellyJumpDown")->setFrameX(imgIndex);
			}
			IMAGEMANAGER->findImage("jellyJumpDown")->frameRender(getMemDC(), x - CAMERA.getCRc().left, (y + 30) - CAMERA.getCRc().top);
			break;
		default:
			break;
		}
	}

	

}
