#include "stdafx.h"
#include "PlayerClass.h"
/*====================================================
						init
======================================================*/
HRESULT PlayerClass::init(float _x, float _y, string _CollisionStage)
{
	//플레이어 변수 초기화
	x = _x;									//플레이어 x좌표
	y = _y;									//플레이어 y좌표
	width = 50;								//플레이어 가로 길이
	height = 50;							//플레이어 세로길이
	speed = 5.0f;							//플레이어 스피드
	gravity = 0.0f;							//중력
	addtionalPower = 0.0f;					//가변점프를 위한 추가적인 파워(가변점프)
	leftPower = 0.0f;						//왼쪽에서 끌어당기는 힘(반발력)
	rightPower = 0.0f;						//오른쪽에서 끌어당기는 힘(반발력)
	imgCount = 0;							//이미지를 돌릴 카운트
	imgIndex = 0;							//이미지 인덱스 접근을 위한 변수
	isAttack = false;						//공격을 했는지 판단
	isAttackOrMove = false;					//공격중에 이동불가
	isLeft = false;							//왼쪽인지? 오른쪽인지?
	isJumpCheck = false;					//점프를 했는지?
	isWallGrab = false;						//벽을 잡고있는지?
	CollisionStage = _CollisionStage;		//맵이름 넣기

	// 센서 변수 초기화 //
	//센서 왼쪽
	sensorLeft.x = x;
	sensorLeft.y = y + height / 2;
	sensorLeft.isJump = false;
	sensorLeft.isTouch = false;
	//센서 위
	sensorTop.x = x + width / 2;
	sensorTop.y = y;
	sensorTop.isJump = false;
	sensorTop.isTouch = false;

	//센서 오른쪽
	sensorRight.x = x + width;
	sensorRight.y = y + height / 2;
	sensorRight.isJump = false;
	sensorRight.isTouch = false;

	//센서 아래
	sensorBottom.x = x + width / 2;
	sensorBottom.y = y + height;
	sensorBottom.isJump = false;
	sensorBottom.isTouch = false;

	//센서 왼쪽 아래
	sensorLeftBottom.x = x;
	sensorLeftBottom.y = y + height;
	//센서 오른쪽 아래
	sensorRightBottom.x = x + width;
	sensorRightBottom.y = y + height;

	//왼똑 대각선
	sensorLeftDiagonal.x = x;
	sensorLeftDiagonal.y = y;
	sensorLeftDiagonal.isJump = false;
	sensorLeftDiagonal.isTouch = false;
	//오른쪽 대각선
	sensorRightDiagonal.x = x + width;
	sensorRightDiagonal.y = y;
	sensorRightDiagonal.isJump = false;
	sensorRightDiagonal.isTouch = false;
	return S_OK;
}
/*====================================================
						release
=====================================================*/
void PlayerClass::release(void)
{
}

/*====================================================
						update
======================================================*/
void PlayerClass::update(void)
{
	//상시 중력
	gravity += 0.2f;

	//반발력
	if (leftPower > 0)			//옆으로 미는 힘이 존재만 한다면
		leftPower -= 0.2f;		//업데이트마다 깎아준다
	else
	{
		leftPower = 0;			 //0보다 작아지면 0으로 셋
	}

	if (rightPower > 0)
		rightPower -= 0.2f;
	else
	{
		rightPower = 0;
	}


	this->playerMove();			//플레이어 윰직임
	this->sensorMove();			//센서 움직임
	this->pixelCollision();		//센서 픽셀 충돌
	this->playerAttack();		//플레이어 공격

	//플레이어에 중력 적용시킨다.
	y += gravity;

	//반발력 적용
	x += rightPower; //항시 작용하는 힘이 존재시 적용한다. 0이면 당근 변동 없겠지?
	x -= leftPower;
}
/*====================================================
						render
======================================================*/
void PlayerClass::render(void)
{
	//조건에 따라 프레임 이미지 렌더하는 함수
	this->playerStateFrameImageRender((x + 5), (y - 20));


	//토글키로 렉트 판정같은거 확인할 수 있읍
	if (KEYMANAGER->isToggleKey('Q'))
	{
		//플레이어 렌더
		Rectangle(getMemDC(), RelativeCameraRect(playerRc));

		// || sensorLeft.isTouch || sensorLeftDiagonal.isTouch || sensorRight.isTouch || sensorRightDiagonal.isTouch || sensorTop.isTouch
		if (sensorBottom.isTouch || sensorLeft.isTouch || sensorLeftDiagonal.isTouch || sensorRight.isTouch || sensorRightDiagonal.isTouch || sensorTop.isTouch)
		{

			HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
			RECT temp = RelativeCameraRect(sensorBottom.sensorRc);
			//Rectangle(getMemDC(), temp);
			FillRect(getMemDC(), &temp, brush);

			Rectangle(getMemDC(), RelativeCameraRect(sensorLeft.sensorRc));

			Rectangle(getMemDC(), RelativeCameraRect(sensorTop.sensorRc));

			Rectangle(getMemDC(), RelativeCameraRect(sensorRight.sensorRc));

			//Rectangle(getMemDC(), RelativeCameraRect(sensorLeftBottom.sensorRc));
			//Rectangle(getMemDC(), RelativeCameraRect(sensorRightBottom.sensorRc));

			Rectangle(getMemDC(), RelativeCameraRect(sensorLeftDiagonal.sensorRc));
			Rectangle(getMemDC(), RelativeCameraRect(sensorRightDiagonal.sensorRc));


			DeleteObject(brush);
		}

		//공격 판정 렉트 렌더
		Rectangle(getMemDC(), RelativeCameraRect(attackRc));

		TextOutfloat(getMemDC(), 400, 10, "센서 레프트의 레프트 좌표", sensorLeft.sensorRc.left);

	}
}

/*====================================================
			playerMove() - 플레이어 움직임 -
======================================================*/

void PlayerClass::playerMove()
{
	if (isJumpCheck)		//만약 플레이어가 점프를 한다면(false라면) 대기 이미지 출력 못하도록
	{
		if (gravity > 0)
		{
			playerState = PlayerClass::JUMP;
		}
	}//else if(isJumpCheck) END

	//오른쪽 움직임
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && isAttackOrMove == false)
	{
		x += speed;							//플레이어 속도만큼 x축 이동(오른쪽이니까 x축 증가)
		isLeft = false;						//false면 오른쪽 움직임 이미지
		isAttack = false;					//하면 공격 모션 캔슬
		//isWallGrab = false;


		if (!isJumpCheck && !isAttack)		//만약 플레이어가 점프를 한다면(false라면) 달리는 이미지 출력 못하도록
		{

			// 오른쪽 누르고있으니까 저는 오른쪽으로 뛰고있습니다.
			playerState = PlayerClass::RUN;

		}



	}
	//왼쪽 움직임
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT) && isAttackOrMove == false)
	{
		isLeft = true;			//true면 왼쪽 움직임 이미지
		//isWallGrab = true;		//벽을 잡은 상태로 반대키누르면?
		x -= speed;				//플레이어 속도만큼 x축 이동(왼쪽이니까 x축 감소)

		if (!isJumpCheck && !isAttack)		//만약 플레이어가 점프를 한다면(false라면) 달리는 이미지 출력 못하도록
		{
			//왼쪽을 누르고 있느니까 저는 왼쪽으로 뛰고있습니다.
			playerState = PlayerClass::RUN;
		}

	}
	// 달리고 있다가 멈췄네 ? 그러면 IDLE로 돌아감 ㅎ
	else
	{
		playerState = PlayerClass::IDLE;
	}

	//점프(가변 점프 : 점프키 누른 시간에 따라 점프력 상승 / 점프력 최대치 존재)
	if (sensorBottom.isJump == false)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			isJumpCheck = true;						//점프를 하게되면 프레임 이미지를 출력할 수 있게 true
			playerState = PlayerClass::JUMP;
			//반발력 점프
			if (sensorLeft.isJump == true)			//왼쪽 센서의 점프 불변수가 true면
			{
				//leftPower = 0.0f;
				rightPower = 7.5f;					//오른쪽으로 반발력 주기~
				isJumpCheck = true;					//점프를 하게되면 프레임 이미지를 출력할 수 있게 true
				sensorRight.isJump = false;			//
				isLeft = false;
			}
			if (sensorRight.isJump == true)			//오른쪽 센서의 점프 불변수가 true면
			{
				//rightPower = 0.0f;
				leftPower = 7.5f;					//왼쪽으로 반발력 주기~
				isJumpCheck = true;					//점프를 하게되면 프레임 이미지를 출력할 수 있게 true
				sensorLeft.isJump = false;
				isLeft = true;
			}
			y -= 20;								//점프 할때 살짝 띄워준다
			gravity = -1.8f;						//중력 역전시키기

		}
		if (KEYMANAGER->isStayKeyDown('C'))			//가변 점프
		{
			isJumpCheck = true;						//점프를 하게되면 프레임 이미지를 출력할 수 있게 true

			if (addtionalPower <= 1.6f)				//가변점프 파워가 1.6f이하면 
			{
				addtionalPower += 0.2f;				//파워를 추가시켜준다.
			}
			if (addtionalPower <= 1.6f)
			{
				gravity -= addtionalPower;
			}


			//if (isJumpCheck == true)
			//{
			//	playerState = PlayerClass::JUMP;
			//}
		}
		if (KEYMANAGER->isOnceKeyUp('C'))
		{
			isJumpCheck = true;						//점프를 하게되면 프레임 이미지를 출력할 수 있게 true
			playerState = PlayerClass::JUMP;

			//gravity = 0.0f;
			addtionalPower = 0.0f;					//점프 키를 떼면 가변 점프 파워 0.0f로 초기화
			sensorBottom.isJump = true;				//2단 점프 가능하지 못하게 변수 true로 변경
		}
	}
	else if (gravity > 0 || gravity < 0)
	{
		isJumpCheck = true;						//점프를 하게되면 프레임 이미지를 출력할 수 있게 true
		playerState = PlayerClass::JUMP;
	}

	//플레이어 상태 지속 업데이트
	playerRc = RectMake(x, y, width, height);
}

/*====================================================
			sensorMove() - 센서 움직임 -
======================================================*/
void PlayerClass::sensorMove()
{
	//센서 위치 조정(왼쪽)
	sensorLeft.x = x;
	sensorLeft.y = y + height / 2;
	//센서 위치 조정(위)
	sensorTop.x = x + width / 2;
	sensorTop.y = y;
	//센서 위치 조정(오른쪽)
	sensorRight.x = x + width;
	sensorRight.y = y + height / 2;

	//센서 위치 조정(아래)
	sensorBottom.x = x + width / 2;
	sensorBottom.y = y + height;
	//센서 위치 조정(왼쪽 아래)
	sensorLeftBottom.x = x + 10;
	sensorLeftBottom.y = y + height;
	//센서 위치 조정(오른쪽 아래)
	sensorRightBottom.x = x + (width - 10);
	sensorRightBottom.y = y + height;


	//왼똑 대각선
	sensorLeftDiagonal.x = x;
	sensorLeftDiagonal.y = y;
	//오른쪽 대각선
	sensorRightDiagonal.x = x + width;
	sensorRightDiagonal.y = y;


	//센서가 플레이어를 따라다니게 지속 업데이트
	sensorLeft.sensorRc = RectMakeCenter(sensorLeft.x, sensorLeft.y, 5, 40);
	sensorTop.sensorRc = RectMakeCenter(sensorTop.x, sensorTop.y, 40, 5);
	sensorRight.sensorRc = RectMakeCenter(sensorRight.x, sensorRight.y, 5, 40);

	sensorBottom.sensorRc = RectMakeCenter(sensorBottom.x, sensorBottom.y, 30, 5);
	//sensorLeftBottom.sensorRc = RectMakeCenter(sensorLeftBottom.x, sensorLeftBottom.y, 5, 5);
	//sensorRightBottom.sensorRc = RectMakeCenter(sensorRightBottom.x, sensorRightBottom.y, 5, 5);

	sensorLeftDiagonal.sensorRc = RectMakeCenter(sensorLeftDiagonal.x, sensorLeftDiagonal.y, 5, 5);
	sensorRightDiagonal.sensorRc = RectMakeCenter(sensorRightDiagonal.x, sensorRightDiagonal.y, 5, 5);
}

/*====================================================
			pixelCollision() - 픽셀 충돌 -
======================================================*/
void PlayerClass::pixelCollision()
//인자값이 센서렉트고 이게 들어가면 방금 들어온 센서가 픽셀충돌이 가능하게 
{

	//왼쪽 아래 픽셀 충돌(Bottom)//
	for (int i = sensorLeftBottom.y - 5; i < sensorLeftBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorLeftBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		//일반 타일 충돌
		if (r == 255 && g == 255 && b == 0)
		{
			y = i - height;							//픽셀 충돌시 플레이어 위치보정
			gravity = 0.0f;							//중력 0으로~
			sensorBottom.isJump = false;			//점프를 할 수 있도록 false
			isJumpCheck = false;					//점프 프레임 이미지 끄기
			break;
		}
		//무너지는 타일 충돌
		if (r == 91 && g == 63 && b == 34)
		{
			y = i - height;							//픽셀 충돌시 플레이어 위치보정
			gravity = 0.0f;							//중력 0으로~
			sensorBottom.isJump = false;			//점프를 할 수 있도록 false
			isJumpCheck = false;					//점프 프레임 이미지 끄기
			break;
		}
	}

	//오른쪽 아래 픽셀 충돌(Bottom)//
	for (int i = sensorRightBottom.y - 5; i < sensorRightBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorRightBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//일반 타일 충돌
		if ((r == 255 && g == 255 && b == 0))
		{
			y = i - height;							//픽셀 충돌시 플레이어 위치보정
			gravity = 0.0f;							//중력 0으로~
			sensorBottom.isJump = false;			//점프를 할 수 있도록 false
			isJumpCheck = false;					//점프 프레임 이미지 끄기
			break;
		}
		//무너지는 타일 충돌
		if ((r == 91 && g == 63 && b == 34))
		{
			y = i - height;							//픽셀 충돌시 플레이어 위치보정
			gravity = 0.0f;							//중력 0으로~
			sensorBottom.isJump = false;			//점프를 할 수 있도록 false
			isJumpCheck = false;					//점프 프레임 이미지 끄기
			break;
		}
	}

	//왼쪽 픽셀 충돌(Left)// = 왼쪽 충돌은 오른쪽 충돌과 반대로 줘야 한다.!!!!!!!!!!!!!!!!!!!
	for (int i = sensorLeft.x + 5; i > sensorLeft.x - 5; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), i, sensorLeft.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 255 && b == 0))					//RGB값이 0,255,0 이면
		{

			//플레이어 x축을 i만큼 보정(충돌이 일어난 곳으로 보정해준다. 안쪽으로 못들어가게)
			x = i;

			if (KEYMANAGER->isStayKeyDown(VK_LEFT) && isAttackOrMove == false)			//벽에 닿은채로 왼쪽키를 누르면
			{
				gravity = 0.0f;								//중력을 0으로 만들어 벽에 붙어있게 만듬
				sensorLeft.isJump = true;					//반발력 점프를 위한 변수 true면 반발력 점프 가능
				if (isLeft)									//벽잡하는 중에 왼쪽인지 판단
				{
					playerState = PlayerClass::GRAB;		//벽잡하는 중에 왼쪽이면 이미지 출력
				}
			}
			else if (isLeft && gravity > 0)					//벽잡이 아닌 그냥 왼쪽 벽에 충돌중에 중력이 0이상이고 왼쪽 판단하는 변수가 true면
			{
				playerState = PlayerClass::GRAB;			//벽잡고있는 이미지 출력
			}
			else if (gravity == 0)							//중력이 0일경우
			{
				playerState = PlayerClass::IDLE;			//대기모션 출력
			}

			leftPower = 0.0f;								//왼쪽 벽에 충돌을 하게 되면 leftpower 0으로 초기화
			sensorBottom.isJump = false;					//임시로 맵확인을 위한 점프
			sensorLeft.isTouch = true;						//센서가 픽셀과 충돌햇는지?
			break;

		}
	}

	//위 픽셀 충돌(Top)//
	for (int i = sensorTop.y - 5; i < sensorTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 0))
		{
			y += 5;				//떨어지기 위해 거리를 이격시킨다.
			gravity = 0.0f;		//그 후 중력을 0으로 만들어준후 중력값을 다시 받게
			sensorTop.isTouch = true;
			break;
		}
	}

	//오른쪽 픽셀 충돌(Right)//
	for (int i = sensorRight.x - 5; i < sensorRight.x + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), i, sensorRight.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 & b == 255))
		{
			x = i - width;
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && isAttackOrMove == false)
			{
				gravity = 0.0f;							//오른쪽 방향키를 누르고 있는 상태라면 중력을 0으로 해서 벽잡기
				sensorRight.isJump = true;				//반발력 점프를 위한 오른쪽 점프 센서가 true면 반발력 점프 가능
				if (!isLeft)							//벽잡하는 중에 오른쪽인지 판단 
				{
					playerState = PlayerClass::GRAB;	//벽잡하는 중에 오른쪽이면 이미지 출력
				}
			}
			else if (!isLeft && gravity > 0)			//벽잡이 아닌 그냥 오른쪽 벽에 충돌중에 중력이 0이상이고 오른쪽 판단하는 변수가 true면
			{
				playerState = PlayerClass::GRAB;		//오른쪽 벽잡 이미지 출력
			}
			else if (gravity == 0)						//중력이 0 이면 
			{
				playerState = PlayerClass::IDLE;		//대기 상태 이미지 출력
			}

			rightPower = 0.0f;						//오른쪽 충돌이 일어나면 오른쪽으로 당기는 반발력 0으로 초기화
			sensorBottom.isJump = false;			//임시로 맵확인을 위한 점프
			sensorRight.isTouch = true;

			break;
		}
	}

	//아래 픽셀 충돌(Bottom)// = 현재 안쓰는 충돌 =
	for (int i = sensorBottom.y - 5; i < sensorBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			y = i - height;
			gravity = 0.0f;
			sensorLeft.isJump = false;
			sensorRight.isJump = false;
			sensorBottom.isJump = false;
			isJumpCheck = false;					//점프 프레임 이미지 끄기
			sensorBottom.isTouch = true;
			break;
		}
		//무너지는 타일 충돌
		else if ((r == 91 && g == 63 && b == 34))
		{
			//y = i - height;							//픽셀 충돌시 플레이어 위치보정
			//gravity = 0.0f;							//중력 0으로~
			//sensorBottom.isJump = false;				//점프를 할 수 있도록 false
			//isJumpCheck = false;						//점프 프레임 이미지 끄기

			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{

			}
			break;
		}

	}

	// 중력이 0이상이때만 픽셀충돌함 //
	if (gravity > 0)
	{
		// 왼쪽 대각선 픽셀 충돌(LeftDiagonal) - 모서리 잡기위한 부분  //
		for (int i = sensorLeftDiagonal.y - 5; i < sensorLeftDiagonal.y + 5; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorLeftDiagonal.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 96 && g == 25 && b == 134))
			{
				gravity = 0.0f;								//모서리 잡으면 중력 0으로~
				sensorBottom.isJump = false;				//점프를 할 수 있도록 false

				if (KEYMANAGER->isStayKeyDown(VK_DOWN))		//모서리 잡은채로 DOWN키 누르면
				{
					y += 10;								//플레이어 떨어질수 있게
				}

				if (KEYMANAGER->isOnceKeyDown(VK_UP))		//모서리 잡은채로 UP키 누르면 부드럽게 올라가야하는데 실패...ㅜㅜ
				{
					y -= 60;
					x -= 50;
				}
				break;
			}
		}//완쪽 대각선 픽셀충돌 for문 END

		//오른쪽 대각선 픽셀 충돌(RightDiagonal) - 모서리 잡기위한 부분 //
		for (int i = sensorRightDiagonal.y - 5; i < sensorRightDiagonal.y + 5; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorRightDiagonal.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 96 && g == 25 && b == 134))
			{
				gravity = 0.0f;								//모서리 잡으면 중력 0으로~
				sensorBottom.isJump = false;				//점프를 할 수 있도록 false

				if (KEYMANAGER->isStayKeyDown(VK_DOWN))		//모서리 잡은채로 DOWN키 누르면
				{
					y += 10;								//플레이어 떨어질수 있게

				}
				if (KEYMANAGER->isStayKeyDown(VK_UP))		//모서리 잡은채로 UP키 누르면 부드럽게 올라가야하는데 실패...ㅜㅜ
				{
					y -= 60;
					x += 50;
				}
				break;
			}
		}//오른쪽 대각선 픽셀충돌 for문 END
	}
}

/*====================================================
			playerAttack() - 플레이어 공격 -
======================================================*/
void PlayerClass::playerAttack()
{

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		isAttack = true;
		isAttackOrMove = true;

		if (isLeft && isAttack)
		{
			attackRc = RectMakeCenter(x - 35, y + height / 2, 10, 10);
		}
		else if (!isLeft && isAttack)
		{
			attackRc = RectMakeCenter(x + 90, y + height / 2, 10, 10);
		}
	}

	if (isLeft && isAttack || !isLeft && isAttack)
	{
		playerState = PlayerClass::ATTACK;
	}

}

/*==============================================================
playerStateFrameImageRender(float x, float y) - 행동 상태 처리 -
================================================================*/
void PlayerClass::playerStateFrameImageRender(float x, float y)
{
	//Enum문을 사용해 플레이어 이미지 상태 변화
	switch (playerState)
	{
	case PlayerClass::IDLE:								// 대기
		if (isLeft)		//왼쪽이면?
		{
			//대기 모션 이미지 프레임 돌리기
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
			IMAGEMANAGER->findImage("pipIdle")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
		}
		else			//오른쪽이면?
		{
			//대기 모션 이미지 프레임 돌리기
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
		}
		break;

	case PlayerClass::RUN:								//뛰기
		if (isLeft)									//만약 플레이어가 점프를 한다면(false라면) 달리는 이미지 출력 못하도록
		{
			if (!isJumpCheck && !isAttack)
			{
				//왼쪽으로 뛰는 이미지 프레임 돌리기
				IMAGEMANAGER->findImage("pipRun")->setFrameY(1);
				imgCount++;															//키를 누르고 있을때 이미지카운트가 증가(++)
				if (imgCount % 3 == 0)												//이미지 카운트를 5로나눈 나머지가 0이면
				{
					imgIndex++;														//이미지 인덱스 증가(++)
					if (imgIndex > 11)												//이미지 인덱스가 마지막 인덱스 초과될경우
					{
						imgIndex = 0;												//이미지 인덱스 0으로 초기화
					}
					IMAGEMANAGER->findImage("pipRun")->setFrameX(imgIndex);			//x축 프레임 셋 돌리기~
				}
				IMAGEMANAGER->findImage("pipRun")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			}//if(!isJumpCheck && !isAttack) END
		}
		else
		{
			if (!isJumpCheck && !isAttack)
			{
				//오른쪽으로 뛰는 이미지 프레임 돌리기
				IMAGEMANAGER->findImage("pipRun")->setFrameY(0);
				imgCount++;															//키를 누르고 있을때 이미지카운트가 증가(++)
				if (imgCount % 3 == 0)												//이미지 카운트를 5로나눈 나머지가 0이면
				{
					imgIndex++;														//이미지 인덱스 증가(++)
					if (imgIndex > 11)												//이미지 인덱스가 마지막 인덱스 초과될경우
					{
						imgIndex = 0;												//이미지 인덱스 0으로 초기화
					}
					IMAGEMANAGER->findImage("pipRun")->setFrameX(imgIndex);			//x축 프레임 셋 돌리기~
				}
				IMAGEMANAGER->findImage("pipRun")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			}
		}
		break;

	case PlayerClass::ATTACK:							//공격
		if (isLeft && isAttack)		//왼쪽이면
		{
			IMAGEMANAGER->findImage("pipAttackLeft")->setFrameY(0);
			imgCount++;
			if (imgCount % 3 == 0)
			{
				imgIndex++;
				if (imgIndex > 11)
				{
					imgIndex = 0;
					if (imgIndex == 0)
					{
						isAttack = false;
						isAttackOrMove = false;
					}
				}
			}
			IMAGEMANAGER->findImage("pipAttackLeft")->setFrameX(imgIndex);
			IMAGEMANAGER->findImage("pipAttackLeft")->frameRender(getMemDC(), (x - 47) - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
		}
		else if (!isLeft && isAttack)						//오른쪽이면
		{
			IMAGEMANAGER->findImage("pipAttackRight")->setFrameY(0);
			imgCount++;
			if (imgCount % 3 == 0)
			{
				imgIndex++;
				if (imgIndex > 11)
				{
					imgIndex = 0;
					if (imgIndex == 0)
					{
						isAttack = false;
						isAttackOrMove = false;
					}
				}
			}
			IMAGEMANAGER->findImage("pipAttackRight")->setFrameX(imgIndex);
			IMAGEMANAGER->findImage("pipAttackRight")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
		}
		break;

	case PlayerClass::JUMP:								//점프
		if (isLeft)
		{
			if (gravity < 0 && isJumpCheck)		//중력이 0미만이면?
			{
				//왼쪽 방향
				//점프 뛰는 이미지 프레임
				IMAGEMANAGER->findImage("pipJumpUp")->setFrameY(0);
				imgCount++;
				if (imgCount % 3 == 0)
				{
					imgIndex++;
					if (imgIndex > 6)
					{
						imgIndex = 0;
					}
					IMAGEMANAGER->findImage("pipJumpUp")->setFrameX(imgIndex);
				}
				IMAGEMANAGER->findImage("pipJumpUp")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			}

			if (gravity > 0 && isJumpCheck)		//중력이 0 초과면?
			{
				//착지하는 이미지 프레임 돌리기
				IMAGEMANAGER->findImage("pipJumpDown")->setFrameY(0);
				imgCount++;
				if (imgCount % 3 == 0)
				{
					imgIndex++;
					if (imgIndex > 5)
					{
						imgIndex = 0;
					}
				}
				IMAGEMANAGER->findImage("pipJumpDown")->setFrameX(imgIndex);
				IMAGEMANAGER->findImage("pipJumpDown")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			}

		}
		else
		{
			if (gravity < 0 && isJumpCheck)
			{
				//오른쪽 방향
				//점프 뛰는 이미지 프레임
				IMAGEMANAGER->findImage("pipJumpUp")->setFrameY(1);
				imgCount++;
				if (imgCount % 3 == 0)
				{
					imgIndex++;
					if (imgIndex > 6)
					{
						imgIndex = 0;

					}
					IMAGEMANAGER->findImage("pipJumpUp")->setFrameX(imgIndex);
				}

				IMAGEMANAGER->findImage("pipJumpUp")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			}
			if (gravity > 0 && isJumpCheck)
			{
				IMAGEMANAGER->findImage("pipJumpDown")->setFrameY(1);
				imgCount++;
				if (imgCount % 3 == 0)
				{
					imgIndex++;
					if (imgIndex > 5)
					{
						imgIndex = 0;
					}
				}
				IMAGEMANAGER->findImage("pipJumpDown")->setFrameX(imgIndex);
				IMAGEMANAGER->findImage("pipJumpDown")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			}
		}
		//if(isLeft && isJumpCheck) END
		break;

	case PlayerClass::GRAB:								//벽잡기
		if (isLeft)
		{
			//왼쪽(true)
			IMAGEMANAGER->findImage("pipGrabLeft")->render(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
		}
		else
		{
			//오른쪽(false)
			IMAGEMANAGER->findImage("pipGrabRight")->render(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
		}
		break;

	case PlayerClass::DOWNATTACK:						//다운공격
		break;

	default:
		break;
	}



}
