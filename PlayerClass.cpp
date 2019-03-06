#include "stdafx.h"
#include "PlayerClass.h"

HRESULT PlayerClass::init(void)
{
	//플레이어 변수 초기화
	x = 100;					//플레이어 x좌표
	y = WINSIZEY / 2;			//플레이어 y좌표
	width = 50;					//플레이어 가로 길이
	height = 50;				//플레이어 세로길이
	speed = 5.0f;				//플레이어 스피드
	gravity = 0.0f;				//중력
	addtionalPower = 0.0f;		//가변점프를 위한 추가적인 파워(가변점프)
	leftPower = 0.0f;			//왼쪽에서 끌어당기는 힘(반발력)
	rightPower = 0.0f;			//오른쪽에서 끌어당기는 힘(반발력)
	isAttack = false;			//공격을 했는지 판단
	imgCount = 0;				//이미지를 돌릴 카운트
	imgIndex = 0;				//이미지 인덱스 접근을 위한 변수
	isLeft = false;
	isjumpCheck = false;


	// 센서 변수 초기화 //
	//센서 왼쪽
	sensorLeft.x = x;
	sensorLeft.y = y + height / 2;
	sensorLeft.isJump = false;
	//센서 위
	sensorTop.x = x + width / 2;
	sensorTop.y = y;
	sensorTop.isJump = false;
	//센서 오른쪽
	sensorRight.x = x + width;
	sensorRight.y = y + height / 2;
	sensorRight.isJump = false;

	//센서 아래
	sensorBottom.x = x + width / 2;
	sensorRight.y = y + height;
	sensorBottom.isJump = false;
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
	//오른쪽 대각선
	sensorRightDiagonal.x = x + width;
	sensorRightDiagonal.y = y;
	sensorRightDiagonal.isJump = false;
	return S_OK;
}

void PlayerClass::release(void)
{
}

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
	this->pipAttack();			//플레이어 공격

	//플레이어에 중력 적용시킨다.
	y += gravity;

	//반발력 적용
	x += rightPower; //항시 작용하는 힘이 존재시 적용한다. 0이면 당근 변동 없겠지?
	x -= leftPower;
}

void PlayerClass::render(void)
{
	//Enum문을 사용해 플레이어 이미지 상태 변화
	switch (playerState)
	{
	case PlayerClass::IDLE:
		if (isLeft)		//isLeft가   
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
			IMAGEMANAGER->findImage("pipIdle")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
		}
		//isLeft가 false면
		else
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
			IMAGEMANAGER->findImage("pipIdle")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
		}
		break;

	case PlayerClass::RUN:
		IMAGEMANAGER->findImage("pipRun")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
		break;

	case PlayerClass::ATTACK:
		IMAGEMANAGER->findImage("pipAttack")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
		break;

	case PlayerClass::JUMP:
		if (isLeft && isjumpCheck)
		{	//왼쪽 방향
			//IMAGEMANAGER->findImage("pipJumpUp")->setFrameY(0);
			IMAGEMANAGER->findImage("pipJumpUp")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
			if (gravity > 0)
			{
				//IMAGEMANAGER->findImage("pipJumpDown")->setFrameY(0);
				IMAGEMANAGER->findImage("pipJumpDown")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
			}
		}
		else
		{	//오른쪽 방향
			//IMAGEMANAGER->findImage("pipJumpUp")->setFrameY(1);
			IMAGEMANAGER->findImage("pipJumpUp")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
			if (gravity > 0)
			{
				//IMAGEMANAGER->findImage("pipJumpDown")->setFrameY(1);
				IMAGEMANAGER->findImage("pipJumpDown")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
			}
		}

		break;

	case PlayerClass::GRAB:
		if (isLeft)
		{
			IMAGEMANAGER->findImage("pipGrabLeft")->render(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
		}
		else
		{
			IMAGEMANAGER->findImage("pipGrabRight")->render(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
		}
		break;

	case PlayerClass::DOWNATTACK:
		break;

	default:
		break;
	}

	//토글키로 렉트 판정같은거 확인할 수 있읍
	if (KEYMANAGER->isToggleKey('Q'))
	{
		//플레이어 렌더
		Rectangle(getMemDC(), RelativeCameraRect(playerRc));

		//센서 렌더
		Rectangle(getMemDC(), RelativeCameraRect(sensorLeft.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorTop.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorRight.sensorRc));

		Rectangle(getMemDC(), RelativeCameraRect(sensorBottom.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorLeftBottom.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorRightBottom.sensorRc));

		Rectangle(getMemDC(), RelativeCameraRect(sensorLeftDiagonal.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorRightDiagonal.sensorRc));

		//공격 판정 렉트 렌더
		Rectangle(getMemDC(), RelativeCameraRect(attackRc));
	}
}

//플레이어 움직임
void PlayerClass::playerMove()
{

	//오른쪽 움직임
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		isLeft = false;			//false면 오른쪽 움직임 이미지
		x += speed;				//플레이어 속도만큼 x축 이동(오른쪽이니까 x축 증가)

		// 오른쪽 누르고있으니까 저는 오른쪽으로 뛰고있습니다.
		playerState = PlayerClass::RUN;
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

	}
	//왼쪽 움직임
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		isLeft = true;			//true면 왼쪽 움직임 이미지
		x -= speed;				//플레이어 속도만큼 x축 이동(왼쪽이니까 x축 감소)

		//왼쪽을 누르고 있느니까 저는 왼쪽으로 뛰고있습니다.
		playerState = PlayerClass::RUN;
		//왼쪽으로 뛰는 이미지 프레임 돌리기
		IMAGEMANAGER->findImage("pipRun")->setFrameY(1);
		imgCount++;
		if (imgCount % 3 == 0)
		{
			imgIndex++;
			if (imgIndex > 11)
			{
				imgIndex = 0;
			}
			IMAGEMANAGER->findImage("pipRun")->setFrameX(imgIndex);
		}
	}
	else
	{
		// 달리고 있다가 멈췄네 ? 그러면 IDLE로 돌아감 ㅎ
		playerState = PlayerClass::IDLE;
	}

	//점프(가변 점프 : 점프키 누른 시간에 따라 점프력 상승 / 점프력 최대치 존재)
	if (sensorBottom.isJump == false)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{

			//반발력 점프
			if (sensorLeft.isJump == true)		//왼쪽 센서의 점프 불변수가 true면
			{
				sensorRight.isJump = false;
				rightPower = 7.5f;				//오른쪽으로 반발력 주기~
			}
			if (sensorRight.isJump == true)		//오른쪽 센서의 점프 불변수가 true면
			{
				sensorLeft.isJump = false;
				sensorRight.isJump = false;
				leftPower = 7.5f;				//왼쪽으로 반발력 주기~
			}

			y -= 20;							//점프 할때 살짝 띄워준다
			gravity = -1.8f;					//중력 역전시키기


//------------------------------------------
			playerState = PlayerClass::JUMP;
			//임시로 해본 점프 이미지
			if (isLeft)
			{	//왼쪽
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
				//점프 착지하는 이미지 프레임!!
				if (gravity > 0)
				{
					IMAGEMANAGER->findImage("pipJumpDown")->setFrameY(0);
					imgCount++;
					if (imgCount % 3 == 0)
					{
						imgIndex++;
						if (imgIndex > 5)
						{
							imgIndex = 0;
						}
						IMAGEMANAGER->findImage("pipJumpDown")->setFrameX(imgIndex);
					}
				}
			}
			else
			{	//오른쪽
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
				//점프 착지하는 이미지 프레임!!
				if (gravity > 0)
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
						IMAGEMANAGER->findImage("pipJumpDown")->setFrameX(imgIndex);
					}
				}
			}
		}

		//-----------------------------------------

		if (KEYMANAGER->isStayKeyDown('C'))		//가변 점프
		{
			if (addtionalPower <= 1.6f)			//가변점프 파워가 1.6f이하면 
			{
				addtionalPower += 0.2f;			//파워를 추가시켜준다.
			}
			if (addtionalPower <= 1.6f)
			{
				gravity -= addtionalPower;
			}
		}
		if (KEYMANAGER->isOnceKeyUp('C'))
		{
			//gravity = 0.0f;
			addtionalPower = 0.0f;				//점프 키를 떼면 가변 점프 파워 0.0f로 초기화
			sensorBottom.isJump = true;			//2단 점프 가능하지 못하게 변수 true로 변경
		}
	}

	//플레이어 상태 지속 업데이트
	playerRc = RectMake(x, y, width, height);
}

//센서 움직임
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

	//sensorBottom.sensorRc = RectMakeCenter(sensorBottom.x, sensorBottom.y, 30, 5);
	sensorLeftBottom.sensorRc = RectMakeCenter(sensorLeftBottom.x, sensorLeftBottom.y, 5, 5);
	sensorRightBottom.sensorRc = RectMakeCenter(sensorRightBottom.x, sensorRightBottom.y, 5, 5);

	sensorLeftDiagonal.sensorRc = RectMakeCenter(sensorLeftDiagonal.x, sensorLeftDiagonal.y, 5, 5);
	sensorRightDiagonal.sensorRc = RectMakeCenter(sensorRightDiagonal.x, sensorRightDiagonal.y, 5, 5);
}

//픽셀 충돌
void PlayerClass::pixelCollision()
//인자값이 센서렉트고 이게 들어가면 방금 들어온 센서가 픽셀충돌이 가능하게 
{
	//왼쪽 픽셀 충돌(Left)//
	for (int i = sensorLeft.x; i < sensorLeft.x + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), i, sensorLeft.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 255 && b == 0))					//RGB값이 0,255,0 이면
		{
			x = i + width / 5 - 5;							//플레이어 x축을 계산범위에 플레이어 가로를 5로 나눠 더해준다.
															//왼쪽으로 파고들지 않게 하기 위해
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))			//벽에 닿은채로 왼쪽키를 누르면
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
			break;

		}
	}

	//위 픽셀 충돌(Top)//
	for (int i = sensorTop.y - 5; i < sensorTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 0))
		{
			y += 5;				//떨어지기 위해 거리를 이격시킨다.
			gravity = 0.0f;		//그 후 중력을 0으로 만들어준후 중력값을 다시 받게
			break;
		}
	}

	//오른쪽 픽셀 충돌(Right)//
	for (int i = sensorRight.x - 5; i < sensorRight.x + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), i, sensorRight.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 & b == 255))
		{
			x = i - width;
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
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
			break;
		}
	}

	//아래 픽셀 충돌(Bottom)//
	for (int i = sensorBottom.y - 5; i < sensorBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorBottom.x, i);
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
			break;
		}

	}

	//왼쪽 아래 픽셀 충돌(Bottom)//
	for (int i = sensorLeftBottom.y - 5; i < sensorLeftBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorLeftBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		//일반 타일 충돌
		if ((r == 255 && g == 255 && b == 0))
		{
			y = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
		//무너지는 타일 충돌
		if ((r == 91 && g == 63 && b == 34))
		{
			y = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
	}

	//오른쪽 아래 픽셀 충돌(Bottom)//
	for (int i = sensorRightBottom.y - 5; i < sensorRightBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorRightBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//일반 타일 충돌
		if ((r == 255 && g == 255 && b == 0))
		{
			y = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
		//무너지는 타일 충돌
		if ((r == 91 && g == 63 && b == 34))
		{
			y = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
	}

	//중력이 0이상이때만 픽셀충돌함//
	if (gravity > 0)
	{
		//왼쪽 대각선 픽셀 충돌(LeftDiagonal)//
		for (int i = sensorLeftDiagonal.y - 5; i < sensorLeftDiagonal.y + 5; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorLeftDiagonal.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 96 && g == 25 && b == 134))
			{
				gravity = 0.0f;
				sensorBottom.isJump = false;

				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					y += 10;
				}

				if (KEYMANAGER->isOnceKeyDown(VK_UP))
				{
					y -= 60;
					x -= 50;
				}
				break;
			}
		}

		//오른쪽 대각선 픽셀 충돌(RightDiagonal)//
		for (int i = sensorRightDiagonal.y - 5; i < sensorRightDiagonal.y + 5; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorRightDiagonal.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 96 && g == 25 && b == 134))
			{
				gravity = 0.0f;
				sensorBottom.isJump = false;

				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					y += 10;

				}
				if (KEYMANAGER->isStayKeyDown(VK_UP))
				{
					y -= 60;
					x += 50;
				}
				break;
			}

		}
	}

}

void PlayerClass::pipAttack()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		//playerState = PlayerClass::ATTACK;
		//IMAGEMANAGER->findImage("pipAttack")->setFrameY(0);
		//imgCount++;
		//if (imgCount % 7 == 0)
		//{
		//	imgIndex++;
		//	if (imgIndex > 11)
		//	{
		//		imgIndex = 0;
		//	}
		//}
		//IMAGEMANAGER->findImage("pipAttack")->setFrameX(imgIndex);
		//isAttack = true;
		//if (isAttack == true)
		//{
		//	attackRc = RectMakeCenter(x - 20, y + height / 2, 10, 10);
		//}

	}

}
