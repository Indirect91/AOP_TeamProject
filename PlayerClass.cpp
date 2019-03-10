#include "stdafx.h"
#include "PlayerClass.h"

/*====================================================
						init()
======================================================*/
HRESULT PlayerClass::init(float _x, float _y, string _collisionStage)
{
	//�÷��̾� �ʱ�ȭ
	x = _x;										//�÷��̾� ��ǥx
	y = _y;										//�÷��̾� ��ǥy
	width = 50;									//�÷��̾� ����
	height = 50;								//�÷��̾� ����
	speed = 5.0f;								//�÷��̾� ���ǵ�
	jellySpeed = 4.0f;							//���� ���ǵ�
	gravity = 0.0f;								//�߷�
	addtionalPower = 0.0f;						//�������� �Ŀ�
	leftRepulsivePower = 0.0f;					//���ʿ��� ���� �ݹ߷�
	rightRepulsivePower = 0.0f;					//�����ʿ��� ���� �ݹ߷�
	imgCount = 0;								//�̹��� ������ ������
	imgIndex = 0;								//������ �̹��� �ε��� ����
	changeCount = 0.0f;							//���� �ð�
	isRepusiveCheck = false;					//�ݹ߷� üũ
	isLeftRepulsive = false;					//�ݹ߷��� ��� �κ����� �ٰ��ΰ�?
	changeForm = false;							//���� ���ΰ�? �ȼ� ���ΰ�?
	isLeft = false;								//����? ������? ���� �Ǵ�
	isAttack = false;							//�������ΰ�?
	isDownAttack = false;
	//isChange = false;							//�̵��� ���� ���ϰ�
	CollisionStage = _collisionStage;			//���� ������ �޾ƿ� �̹��� ���~

#pragma region ���� �ʱ�ȭ
	//���� �ʱ�ȭ
	sensorBottom.x = x + width / 2;				//���� x��ġ �ʱ�ȭ
	sensorBottom.y = y + height;				//���� y��ġ �ʱ�ȭ
	sensorBottom.isJump = false;				//���� ���� bool���� �ʱ�ȭ
	sensorBottom.isTouch = false;				//���� ��ġ bool���� �ʱ�ȭ

	sensorLeft.x = x;							//���� x��ġ �ʱ�ȭ
	sensorLeft.y = y + height / 2;				//���� y��ġ �ʱ�ȭ
	sensorLeft.isJump = false;					//���� ���� bool���� �ʱ�ȭ
	sensorLeft.isTouch = false;					//���� ��ġ bool���� �ʱ�ȭ

	sensorRight.x = x + width;					//���� x��ġ �ʱ�ȭ
	sensorRight.y = y + height / 2;				//���� y��ġ �ʱ�ȭ
	sensorRight.isJump = false;					//���� ���� bool���� �ʱ�ȭ
	sensorRight.isTouch = false;				//���� ��ġ bool���� �ʱ�ȭ

	sensorTop.x = x + width / 2;				//���� x��ġ �ʱ�ȭ
	sensorTop.y = y;							//���� y��ġ �ʱ�ȭ
	sensorTop.isJump = false;					//���� ���� bool���� �ʱ�ȭ
	sensorTop.isTouch = false;					//���� ��ġ bool���� �ʱ�ȭ

	sensorLeftTop.x = x;						//���� x��ġ �ʱ�ȭ
	sensorLeftTop.y = y;						//���� y��ġ �ʱ�ȭ
	sensorLeftTop.isJump = false;				//���� ���� bool���� �ʱ�ȭ
	sensorLeftTop.isTouch = false;				//���� ��ġ bool���� �ʱ�ȭ

	sensorRightTop.x = x + width;				//���� x��ġ �ʱ�ȭ
	sensorRightTop.y = y;						//���� y��ġ �ʱ�ȭ
	sensorRightTop.isJump = false;				//���� ���� bool���� �ʱ�ȭ
	sensorRightTop.isTouch = false;				//���� ��ġ bool���� �ʱ�ȭ
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
	//��� �߷�
	gravity += 0.4f;

	if (!changeForm)
	{
		this->playerMove();							//�÷��̾� ������
		this->playerAttack();
	}

	this->sensorMove();								//���� ������
	this->pixelCollision();							//�ȼ� �浹
	this->repulsive();								//�ݹ߷�

	//����
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

	//�߷��� ���� �������� ��������Ѵ�.
	y += gravity;

	//�ݹ߷��� �����ϸ� ��ܴ��~
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
		//�÷��̾�
		Rectangle(getMemDC(), RelativeCameraRect(playerRc));

		//�ȼ� �浹�� üũ
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
	IMAGEMANAGER->addFrameImage("portl", "2312,308_ ���纻.bmp", 2312, 308, 17, 1, true, RGB(255, 0, 255))->stretchFrameRenderCenterXDownY(getMemDC(), 60, 80, frme, 0, 1, 2);


	this->playerStateFrameImageRender((x + 5), (y - 20));
}

/*=============================================================
			playerMove() - �÷��̾� ������ -
===============================================================*/
void PlayerClass::playerMove()
{
	//!isLeft ? playerStateEnum = RIGHTIDLE : playerStateEnum = LEFTIDLE;

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//���������� ������ �̵����� // ����(true) ����(true) �̵� ����
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

	if (!sensorBottom.isJump)												//������ ���� ���� bool������ false�� �Ʒ��� ����� ��� �� �� �ִ�.
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			y -= 10;														//�����ϱ� ���� y���� ��¦ �̰ݽ�Ų��.
			gravity = -6.0f;												//�߷��� ���� ���Ѽ� ����

			//�ݹ߷�
			if (isRepusiveCheck && !sensorBottom.isTouch)					//�ݹ߷��� �ٰ�����?
			{
				if (isLeftRepulsive && !sensorLeftTop.isTouch)				//�������� �ݹ߷��� �شٸ�
				{
					x += 10;												//x���� ��¦ �̰� ��Ų��
					rightRepulsivePower = 5.5f;								//�ݹ߷��� �ش�.
					isLeft = true;
				}
				else if (!isLeftRepulsive && !sensorRightTop.isTouch)		//���������� �ݹ߷��� �شٸ�
				{
					x -= 10;												//x���� ��¦ �̰� ��Ų��
					leftRepulsivePower = 5.5f;								//�ݹ߷��� �ش�.
					isLeft = false;
				}
			}
		}
		if (KEYMANAGER->isStayKeyDown('K'))
		{
			//���� ����(CŰ�� �� ������ ������ ���� ���� �Ŀ��� ������ �ϰ� �ȴ�.(�ִ�ġ ����))
			if (addtionalPower <= 1.6f)										//�������� �Ŀ��� 1.6f ���϶��
			{
				addtionalPower += 0.2f;										//�������� �Ŀ� ����
			}
			if (addtionalPower <= 1.6f)										//�������� �Ŀ��� 1.6f ���϶��
			{
				gravity -= addtionalPower;									//������ �������� �Ŀ��� ���� �߷¿� �߰��� ������ ���� �ۼ� �ֵ��� ���ش�
			}

		}
		if (KEYMANAGER->isOnceKeyUp('K'))
		{
			sensorBottom.isJump = true;										//���� ������ �������� bool���� true
			addtionalPower = 0.0f;											//�������� �Ŀ� �ٽ� �ʱ�ȭ
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

	//�÷��̾� ���� ������Ʈ
	playerRc = RectMake(x, y, width, height);
}

/*=============================================================
			playerAttack() - �÷��̾� ���� -
===============================================================*/
void PlayerClass::playerAttack()
{
	//�÷��̾� �Ϲ� ����
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

	//�÷��̾� �ٿ����
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
			sensorMove() - ���� ������ -
================================================================*/
void PlayerClass::sensorMove()
{
#pragma region ���� ��ġ ���� ������Ʈ
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

	//���� ���� ������Ʈ
	sensorBottom.sensorRc = RectMakeCenter(sensorBottom.x, sensorBottom.y, 40, 5);
	sensorLeft.sensorRc = RectMakeCenter(sensorLeft.x, sensorLeft.y, 5, 40);
	sensorRight.sensorRc = RectMakeCenter(sensorRight.x, sensorRight.y, 5, 40);
	sensorTop.sensorRc = RectMakeCenter(sensorTop.x, sensorTop.y, 40, 5);
	sensorLeftTop.sensorRc = RectMakeCenter(sensorLeftTop.x, sensorLeftTop.y, 5, 5);
	sensorRightTop.sensorRc = RectMakeCenter(sensorRightTop.x, sensorRightTop.y, 5, 5);
}

/*==============================================================
			pixelCollision() - �ȼ� �浹 -
================================================================*/
void PlayerClass::pixelCollision()
{
	//���� �ȼ� �浹(Bottom)
	for (int i = sensorBottom.y - 5; i < sensorBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//���Ҽ��� X �ȼ�(�����)
		if (r == 255 && g == 255 && b == 0)
		{
			y = i - height;						//y�� ��ġ����
			gravity = 0.0f;						//�߷� 0����~
			sensorBottom.isTouch = true;		//���� �ȼ� �浹������ üũ
			sensorBottom.isJump = false;		//�ȼ� �浹���̸� �������� ����
			isRepusiveCheck = false;			//�������� �ƴ� ���� �� �� �ݹ߷��� ���ְ� �ϱ� ����
			//if(isAttack) isAttack = false;
			break;
		}

		//���� ���� X �������� Ÿ��
		if (r == 91 && g == 63 && b == 34)
		{
			y = i - height;
			gravity = 0.0f;						//�߷� 0����~
			sensorBottom.isTouch = true;		//���� �ȼ� �浹������ üũ
			sensorBottom.isJump = false;		//�ȼ� �浹���̸� �������� ����
			isRepusiveCheck = false;			//�������� �ƴ� ���� �� �� �ݹ߷��� ���ְ� �ϱ� ����
			break;
		}

		//���� ���� X ����Ÿ��
		if (r == 255 && g == 94 && b == 0)
		{
			y = i - height;
			gravity = 0.0f;						//�߷� 0����~
			sensorBottom.isTouch = true;		//���� �ȼ� �浹������ üũ
			sensorBottom.isJump = false;		//�ȼ� �浹���̸� �������� ����
			isRepusiveCheck = false;			//�������� �ƴ� ���� �� �� �ݹ߷��� ���ְ� �ϱ� ����
			break;
		}

		//���Ҽ��� X �������� �μ����� Ÿ��
		if (r == 126 && g == 206 && b == 244)
		{
			y = i - height;
			gravity = 0.0f;						//�߷� 0����~
			sensorBottom.isTouch = true;		//���� �ȼ� �浹������ üũ
			sensorBottom.isJump = false;		//�ȼ� �浹���̸� �������� ����
			isRepusiveCheck = false;			//�������� �ƴ� ���� �� �� �ݹ߷��� ���ְ� �ϱ� ����
			break;
		}

		//���Ҽ��� X �������� Ÿ��
		if (r == 149 && g == 149 && b == 149)
		{
			y = i - height;
			gravity = 0.0f;						//�߷� 0����~
			sensorBottom.isTouch = true;		//���� �ȼ� �浹������ üũ
			sensorBottom.isJump = false;		//�ȼ� �浹���̸� �������� ����
			isRepusiveCheck = false;			//�������� �ƴ� ���� �� �� �ݹ߷��� ���ְ� �ϱ� ����
			break;
		}
	}

	//������ �ȼ� �浹(Right)
	for (int i = sensorRight.x - 5; i < sensorRight.x + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), i, sensorRight.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//������ ���� X �ȼ�(�Ķ���)
		if (r == 0 && g == 0 && b == 255)
		{
			x = i - width;						//x�� ��ġ ����
			isLeftRepulsive = false;			//�ݹ߷��� ����������� �� ���ΰ�?(�������� �ٰ���)
			rightRepulsivePower = 0.0f;			//�ݹ߷� �Ŀ��� �׽� �����ϸ� �ȵǴϱ� 0���� �ʱ�ȭ
			isRepusiveCheck = true;				//�������� �� �� �ֵ��� 
			sensorBottom.isJump = false;		//���� ������ ������ �� �� �־�� �ϴϱ�
			sensorRight.isTouch = true;			//������ ������ �浹�� �ǰ��ִ���?

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
					gravity = 0.0f;					//������ �ϴ� ���̴� �߷� 0
				}
			}
			break;
		}

		//������� �浹��
		if (r == 255 && g == 255 && b == 0)
		{
			x = i - width;						//��ġ ����
			break;
		}
		//�������� �浹��
		if (r == 0 && g == 0 && b == 0)
		{
			x = i - width;						//��ġ ����
			break;
		}

	}

	//���� �ȼ� �浹(Left)
	for (int i = sensorLeft.x + 5; i > sensorLeft.x - 5; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), i, sensorLeft.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//���� ���� X �ȼ�(����)
		if (r == 0 && g == 255 && b == 0)
		{

			x = i;								//x�� ��ġ ����
			isLeftRepulsive = true;				//�ݹ߷��� ����������� �� ���ΰ�?(���������� �ٰ���)
			leftRepulsivePower = 0.0f;			//�ݹ߷� �Ŀ��� �׽� �����ϸ� �ȵǴϱ� 0���� �ʱ�ȭ
			isRepusiveCheck = true; 			//�������� �� �� �ֵ��� 
			sensorBottom.isJump = false;		//���� ������ ������ �� �� �־�� �ϴϱ�
			sensorLeft.isTouch = true;			//���� ������ �浹�� �ǰ��ִ���?

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
					gravity = 0.0f;					//������ �ϴ� ���̴� �߷��� 0
				}
			}
			break;
		}
		//������� �浹�� 
		if (r == 255 && g == 255 && b == 0)
		{
			x = i;								//��ġ ����
			break;
		}
		//�������� �浹��
		if (r == 0 && g == 0 && b == 0)
		{
			x = i;								//��ġ ����
			break;
		}
	}

	//ž �ȼ� �浹(Top)
	for (int i = sensorTop.y - 5; i < sensorTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//ž ���� X �ȼ�(����)
		if (r == 0 && g == 0 && b == 0)
		{
			y += 5;								//y���� �̰ݽ����ش�.
			gravity = 0.0f;						//�߷��� 0���� ����� �ڿ������� ��������
			sensorTop.isTouch = true;			//ž ������ �浹 ������?
			break;
		}
	}

	//������ �밢�� �ȼ� �浹(RightTop)
	for (int i = sensorRightTop.y - 5; i < sensorRightTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorRightTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (!changeForm)
		{
			//������ �밢 ���� X �ȼ�(����)
			if (r == 96 && g == 25 && b == 134)
			{
				gravity = 0.0f;								//�𼭸��� �Ŵ޸��� ������ �߷� 0
				sensorRightTop.isTouch = true;				//������ �𼭸� ������ �浹������?
				sensorBottom.isJump = false;				//�𼭸� ������ ���� �����ϰ�

				if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
				{
					y += 20;								//Down��ư ������ �����ü� �ְ�
				}
			}
		}
	}

	//���� �밢�� �ȼ� �浹(LeftTop)
	for (int i = sensorLeftTop.y - 5; i < sensorLeftTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorLeftTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!changeForm)
		{
			//���� �밢 ���� X �ȼ�(����)
			if (r == 96 && g == 25 && b == 134)
			{
				gravity = 0.0f;								//�𼭸��� �Ŵ޸��� ������ �߷� 0
				sensorLeftTop.isTouch = true;				//���� �𼭸� ������ �浹������?
				sensorBottom.isJump = false;				//�𼭸� ������ ���� �����ϰ�

				if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
				{
					y += 20;								//Down��ư ������ �����ü� �ְ�
				}
			}
		}
	}
}

/*==============================================================
			repulsive() - �ݹ߷� -
================================================================*/
void PlayerClass::repulsive()
{
	//�ݹ߷� ��(����)
	if (leftRepulsivePower > 0)							//���� �ݹ߷� ���� 0 �̻��̸�
	{
		leftRepulsivePower -= 0.1f;						//���� ��� ��� �ش�.
	}
	else
	{
		leftRepulsivePower = 0.0f;						//�ݹ߷� ���� ����(-)�̸� 0���� ����
	}
	//�ݹ߷� ��(������)
	if (rightRepulsivePower > 0)						//������ �ݹ߷� ���� 0 �̻��̸�
	{
		rightRepulsivePower -= 0.1f;					//���� ��� ��� �ش�.
	}
	else
	{
		rightRepulsivePower = 0.0f;						//�ݹ߷� ���� ����(-)�̸� 0���� ����
	}
}

/*==============================================================
			jellyMove() - ���� ������ -
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

	if (!sensorBottom.isJump)												//������ ���� ���� bool������ false�� �Ʒ��� ����� ��� �� �� �ִ�.
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			y -= 10;														//�����ϱ� ���� y���� ��¦ �̰ݽ�Ų��.
			gravity = -6.0f;												//�߷��� ���� ���Ѽ� ����
		}
		if (KEYMANAGER->isStayKeyDown('K'))
		{
			//���� ����(CŰ�� �� ������ ������ ���� ���� �Ŀ��� ������ �ϰ� �ȴ�.(�ִ�ġ ����))
			if (addtionalPower <= 1.6f)										//�������� �Ŀ��� 1.6f ���϶��
			{
				addtionalPower += 0.2f;										//�������� �Ŀ� ����
			}
			if (addtionalPower <= 1.6f)										//�������� �Ŀ��� 1.6f ���϶��
			{
				gravity -= addtionalPower;									//������ �������� �Ŀ��� ���� �߷¿� �߰��� ������ ���� �ۼ� �ֵ��� ���ش�
			}
			//���� ����~
			if (gravity > 0)												//���� ���� õõ�� ��������
			{
				gravity -= 0.3f;											//���� �ۿ�ǰ��ִ� �߷¿��� ���ش�.
			}
		}
		if (KEYMANAGER->isOnceKeyUp('K'))
		{
			sensorBottom.isJump = true;										//���� ������ �������� bool���� true
			addtionalPower = 0.0f;											//�������� �Ŀ� �ٽ� �ʱ�ȭ
		}
	}
	if (!sensorBottom.isTouch)
	{
		if (gravity < 0) jellyState = changeFormEnum::JELLYJUMPUP;
		else jellyState = changeFormEnum::JELLYJUMPDOWN;
	}

	//�÷��̾� ���� ������Ʈ
	playerRc = RectMake(x, y, width, height);
}

/*==============================================================
	sensorPixelCollisionCheck() - ���� �浹 üũ -
================================================================*/
void PlayerClass::sensorPixelCollisionCheck()
{
	//���� ����(�ȼ� �浹 ���̸� ������ | �浹���� �ƴϸ� �ϴû�)
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
playerStateFrameImageRender(float x, float y) - �ൿ ���� ó�� -
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

			//������
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
