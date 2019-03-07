#include "stdafx.h"
#include "PlayerClass.h"
/*====================================================
						init
======================================================*/
HRESULT PlayerClass::init(float _x, float _y, string _CollisionStage)
{
	//�÷��̾� ���� �ʱ�ȭ
	x = _x;									//�÷��̾� x��ǥ
	y = _y;									//�÷��̾� y��ǥ
	width = 50;								//�÷��̾� ���� ����
	height = 50;							//�÷��̾� ���α���
	speed = 5.0f;							//�÷��̾� ���ǵ�
	gravity = 0.0f;							//�߷�
	addtionalPower = 0.0f;					//���������� ���� �߰����� �Ŀ�(��������)
	leftPower = 0.0f;						//���ʿ��� ������� ��(�ݹ߷�)
	rightPower = 0.0f;						//�����ʿ��� ������� ��(�ݹ߷�)
	imgCount = 0;							//�̹����� ���� ī��Ʈ
	imgIndex = 0;							//�̹��� �ε��� ������ ���� ����
	isAttack = false;						//������ �ߴ��� �Ǵ�
	isAttackOrMove = false;					//�����߿� �̵��Ұ�
	isLeft = false;							//��������? ����������?
	isJumpCheck = false;					//������ �ߴ���?
	isWallGrab = false;						//���� ����ִ���?
	CollisionStage = _CollisionStage;		//���̸� �ֱ�

	// ���� ���� �ʱ�ȭ //
	//���� ����
	sensorLeft.x = x;
	sensorLeft.y = y + height / 2;
	sensorLeft.isJump = false;
	sensorLeft.isTouch = false;
	//���� ��
	sensorTop.x = x + width / 2;
	sensorTop.y = y;
	sensorTop.isJump = false;
	sensorTop.isTouch = false;

	//���� ������
	sensorRight.x = x + width;
	sensorRight.y = y + height / 2;
	sensorRight.isJump = false;
	sensorRight.isTouch = false;

	//���� �Ʒ�
	sensorBottom.x = x + width / 2;
	sensorBottom.y = y + height;
	sensorBottom.isJump = false;
	sensorBottom.isTouch = false;

	//���� ���� �Ʒ�
	sensorLeftBottom.x = x;
	sensorLeftBottom.y = y + height;
	//���� ������ �Ʒ�
	sensorRightBottom.x = x + width;
	sensorRightBottom.y = y + height;

	//�޶� �밢��
	sensorLeftDiagonal.x = x;
	sensorLeftDiagonal.y = y;
	sensorLeftDiagonal.isJump = false;
	sensorLeftDiagonal.isTouch = false;
	//������ �밢��
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
	//��� �߷�
	gravity += 0.2f;

	//�ݹ߷�
	if (leftPower > 0)			//������ �̴� ���� ���縸 �Ѵٸ�
		leftPower -= 0.2f;		//������Ʈ���� ����ش�
	else
	{
		leftPower = 0;			 //0���� �۾����� 0���� ��
	}

	if (rightPower > 0)
		rightPower -= 0.2f;
	else
	{
		rightPower = 0;
	}


	this->playerMove();			//�÷��̾� ������
	this->sensorMove();			//���� ������
	this->pixelCollision();		//���� �ȼ� �浹
	this->playerAttack();		//�÷��̾� ����

	//�÷��̾ �߷� �����Ų��.
	y += gravity;

	//�ݹ߷� ����
	x += rightPower; //�׽� �ۿ��ϴ� ���� ����� �����Ѵ�. 0�̸� ��� ���� ������?
	x -= leftPower;
}
/*====================================================
						render
======================================================*/
void PlayerClass::render(void)
{
	//���ǿ� ���� ������ �̹��� �����ϴ� �Լ�
	this->playerStateFrameImageRender((x + 5), (y - 20));


	//���Ű�� ��Ʈ ���������� Ȯ���� �� ����
	if (KEYMANAGER->isToggleKey('Q'))
	{
		//�÷��̾� ����
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

		//���� ���� ��Ʈ ����
		Rectangle(getMemDC(), RelativeCameraRect(attackRc));

		TextOutfloat(getMemDC(), 400, 10, "���� ����Ʈ�� ����Ʈ ��ǥ", sensorLeft.sensorRc.left);

	}
}

/*====================================================
			playerMove() - �÷��̾� ������ -
======================================================*/

void PlayerClass::playerMove()
{
	if (isJumpCheck)		//���� �÷��̾ ������ �Ѵٸ�(false���) ��� �̹��� ��� ���ϵ���
	{
		if (gravity > 0)
		{
			playerState = PlayerClass::JUMP;
		}
	}//else if(isJumpCheck) END

	//������ ������
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && isAttackOrMove == false)
	{
		x += speed;							//�÷��̾� �ӵ���ŭ x�� �̵�(�������̴ϱ� x�� ����)
		isLeft = false;						//false�� ������ ������ �̹���
		isAttack = false;					//�ϸ� ���� ��� ĵ��
		//isWallGrab = false;


		if (!isJumpCheck && !isAttack)		//���� �÷��̾ ������ �Ѵٸ�(false���) �޸��� �̹��� ��� ���ϵ���
		{

			// ������ �����������ϱ� ���� ���������� �ٰ��ֽ��ϴ�.
			playerState = PlayerClass::RUN;

		}



	}
	//���� ������
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT) && isAttackOrMove == false)
	{
		isLeft = true;			//true�� ���� ������ �̹���
		//isWallGrab = true;		//���� ���� ���·� �ݴ�Ű������?
		x -= speed;				//�÷��̾� �ӵ���ŭ x�� �̵�(�����̴ϱ� x�� ����)

		if (!isJumpCheck && !isAttack)		//���� �÷��̾ ������ �Ѵٸ�(false���) �޸��� �̹��� ��� ���ϵ���
		{
			//������ ������ �ִ��ϱ� ���� �������� �ٰ��ֽ��ϴ�.
			playerState = PlayerClass::RUN;
		}

	}
	// �޸��� �ִٰ� ����� ? �׷��� IDLE�� ���ư� ��
	else
	{
		playerState = PlayerClass::IDLE;
	}

	//����(���� ���� : ����Ű ���� �ð��� ���� ������ ��� / ������ �ִ�ġ ����)
	if (sensorBottom.isJump == false)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			isJumpCheck = true;						//������ �ϰԵǸ� ������ �̹����� ����� �� �ְ� true
			playerState = PlayerClass::JUMP;
			//�ݹ߷� ����
			if (sensorLeft.isJump == true)			//���� ������ ���� �Һ����� true��
			{
				//leftPower = 0.0f;
				rightPower = 7.5f;					//���������� �ݹ߷� �ֱ�~
				isJumpCheck = true;					//������ �ϰԵǸ� ������ �̹����� ����� �� �ְ� true
				sensorRight.isJump = false;			//
				isLeft = false;
			}
			if (sensorRight.isJump == true)			//������ ������ ���� �Һ����� true��
			{
				//rightPower = 0.0f;
				leftPower = 7.5f;					//�������� �ݹ߷� �ֱ�~
				isJumpCheck = true;					//������ �ϰԵǸ� ������ �̹����� ����� �� �ְ� true
				sensorLeft.isJump = false;
				isLeft = true;
			}
			y -= 20;								//���� �Ҷ� ��¦ ����ش�
			gravity = -1.8f;						//�߷� ������Ű��

		}
		if (KEYMANAGER->isStayKeyDown('C'))			//���� ����
		{
			isJumpCheck = true;						//������ �ϰԵǸ� ������ �̹����� ����� �� �ְ� true

			if (addtionalPower <= 1.6f)				//�������� �Ŀ��� 1.6f���ϸ� 
			{
				addtionalPower += 0.2f;				//�Ŀ��� �߰������ش�.
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
			isJumpCheck = true;						//������ �ϰԵǸ� ������ �̹����� ����� �� �ְ� true
			playerState = PlayerClass::JUMP;

			//gravity = 0.0f;
			addtionalPower = 0.0f;					//���� Ű�� ���� ���� ���� �Ŀ� 0.0f�� �ʱ�ȭ
			sensorBottom.isJump = true;				//2�� ���� �������� ���ϰ� ���� true�� ����
		}
	}
	else if (gravity > 0 || gravity < 0)
	{
		isJumpCheck = true;						//������ �ϰԵǸ� ������ �̹����� ����� �� �ְ� true
		playerState = PlayerClass::JUMP;
	}

	//�÷��̾� ���� ���� ������Ʈ
	playerRc = RectMake(x, y, width, height);
}

/*====================================================
			sensorMove() - ���� ������ -
======================================================*/
void PlayerClass::sensorMove()
{
	//���� ��ġ ����(����)
	sensorLeft.x = x;
	sensorLeft.y = y + height / 2;
	//���� ��ġ ����(��)
	sensorTop.x = x + width / 2;
	sensorTop.y = y;
	//���� ��ġ ����(������)
	sensorRight.x = x + width;
	sensorRight.y = y + height / 2;

	//���� ��ġ ����(�Ʒ�)
	sensorBottom.x = x + width / 2;
	sensorBottom.y = y + height;
	//���� ��ġ ����(���� �Ʒ�)
	sensorLeftBottom.x = x + 10;
	sensorLeftBottom.y = y + height;
	//���� ��ġ ����(������ �Ʒ�)
	sensorRightBottom.x = x + (width - 10);
	sensorRightBottom.y = y + height;


	//�޶� �밢��
	sensorLeftDiagonal.x = x;
	sensorLeftDiagonal.y = y;
	//������ �밢��
	sensorRightDiagonal.x = x + width;
	sensorRightDiagonal.y = y;


	//������ �÷��̾ ����ٴϰ� ���� ������Ʈ
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
			pixelCollision() - �ȼ� �浹 -
======================================================*/
void PlayerClass::pixelCollision()
//���ڰ��� ������Ʈ�� �̰� ���� ��� ���� ������ �ȼ��浹�� �����ϰ� 
{

	//���� �Ʒ� �ȼ� �浹(Bottom)//
	for (int i = sensorLeftBottom.y - 5; i < sensorLeftBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorLeftBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		//�Ϲ� Ÿ�� �浹
		if (r == 255 && g == 255 && b == 0)
		{
			y = i - height;							//�ȼ� �浹�� �÷��̾� ��ġ����
			gravity = 0.0f;							//�߷� 0����~
			sensorBottom.isJump = false;			//������ �� �� �ֵ��� false
			isJumpCheck = false;					//���� ������ �̹��� ����
			break;
		}
		//�������� Ÿ�� �浹
		if (r == 91 && g == 63 && b == 34)
		{
			y = i - height;							//�ȼ� �浹�� �÷��̾� ��ġ����
			gravity = 0.0f;							//�߷� 0����~
			sensorBottom.isJump = false;			//������ �� �� �ֵ��� false
			isJumpCheck = false;					//���� ������ �̹��� ����
			break;
		}
	}

	//������ �Ʒ� �ȼ� �浹(Bottom)//
	for (int i = sensorRightBottom.y - 5; i < sensorRightBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorRightBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//�Ϲ� Ÿ�� �浹
		if ((r == 255 && g == 255 && b == 0))
		{
			y = i - height;							//�ȼ� �浹�� �÷��̾� ��ġ����
			gravity = 0.0f;							//�߷� 0����~
			sensorBottom.isJump = false;			//������ �� �� �ֵ��� false
			isJumpCheck = false;					//���� ������ �̹��� ����
			break;
		}
		//�������� Ÿ�� �浹
		if ((r == 91 && g == 63 && b == 34))
		{
			y = i - height;							//�ȼ� �浹�� �÷��̾� ��ġ����
			gravity = 0.0f;							//�߷� 0����~
			sensorBottom.isJump = false;			//������ �� �� �ֵ��� false
			isJumpCheck = false;					//���� ������ �̹��� ����
			break;
		}
	}

	//���� �ȼ� �浹(Left)// = ���� �浹�� ������ �浹�� �ݴ�� ��� �Ѵ�.!!!!!!!!!!!!!!!!!!!
	for (int i = sensorLeft.x + 5; i > sensorLeft.x - 5; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), i, sensorLeft.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 255 && b == 0))					//RGB���� 0,255,0 �̸�
		{

			//�÷��̾� x���� i��ŭ ����(�浹�� �Ͼ ������ �������ش�. �������� ������)
			x = i;

			if (KEYMANAGER->isStayKeyDown(VK_LEFT) && isAttackOrMove == false)			//���� ����ä�� ����Ű�� ������
			{
				gravity = 0.0f;								//�߷��� 0���� ����� ���� �پ��ְ� ����
				sensorLeft.isJump = true;					//�ݹ߷� ������ ���� ���� true�� �ݹ߷� ���� ����
				if (isLeft)									//�����ϴ� �߿� �������� �Ǵ�
				{
					playerState = PlayerClass::GRAB;		//�����ϴ� �߿� �����̸� �̹��� ���
				}
			}
			else if (isLeft && gravity > 0)					//������ �ƴ� �׳� ���� ���� �浹�߿� �߷��� 0�̻��̰� ���� �Ǵ��ϴ� ������ true��
			{
				playerState = PlayerClass::GRAB;			//������ִ� �̹��� ���
			}
			else if (gravity == 0)							//�߷��� 0�ϰ��
			{
				playerState = PlayerClass::IDLE;			//����� ���
			}

			leftPower = 0.0f;								//���� ���� �浹�� �ϰ� �Ǹ� leftpower 0���� �ʱ�ȭ
			sensorBottom.isJump = false;					//�ӽ÷� ��Ȯ���� ���� ����
			sensorLeft.isTouch = true;						//������ �ȼ��� �浹�޴���?
			break;

		}
	}

	//�� �ȼ� �浹(Top)//
	for (int i = sensorTop.y - 5; i < sensorTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 0))
		{
			y += 5;				//�������� ���� �Ÿ��� �̰ݽ�Ų��.
			gravity = 0.0f;		//�� �� �߷��� 0���� ��������� �߷°��� �ٽ� �ް�
			sensorTop.isTouch = true;
			break;
		}
	}

	//������ �ȼ� �浹(Right)//
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
				gravity = 0.0f;							//������ ����Ű�� ������ �ִ� ���¶�� �߷��� 0���� �ؼ� �����
				sensorRight.isJump = true;				//�ݹ߷� ������ ���� ������ ���� ������ true�� �ݹ߷� ���� ����
				if (!isLeft)							//�����ϴ� �߿� ���������� �Ǵ� 
				{
					playerState = PlayerClass::GRAB;	//�����ϴ� �߿� �������̸� �̹��� ���
				}
			}
			else if (!isLeft && gravity > 0)			//������ �ƴ� �׳� ������ ���� �浹�߿� �߷��� 0�̻��̰� ������ �Ǵ��ϴ� ������ true��
			{
				playerState = PlayerClass::GRAB;		//������ ���� �̹��� ���
			}
			else if (gravity == 0)						//�߷��� 0 �̸� 
			{
				playerState = PlayerClass::IDLE;		//��� ���� �̹��� ���
			}

			rightPower = 0.0f;						//������ �浹�� �Ͼ�� ���������� ���� �ݹ߷� 0���� �ʱ�ȭ
			sensorBottom.isJump = false;			//�ӽ÷� ��Ȯ���� ���� ����
			sensorRight.isTouch = true;

			break;
		}
	}

	//�Ʒ� �ȼ� �浹(Bottom)// = ���� �Ⱦ��� �浹 =
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
			isJumpCheck = false;					//���� ������ �̹��� ����
			sensorBottom.isTouch = true;
			break;
		}
		//�������� Ÿ�� �浹
		else if ((r == 91 && g == 63 && b == 34))
		{
			//y = i - height;							//�ȼ� �浹�� �÷��̾� ��ġ����
			//gravity = 0.0f;							//�߷� 0����~
			//sensorBottom.isJump = false;				//������ �� �� �ֵ��� false
			//isJumpCheck = false;						//���� ������ �̹��� ����

			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{

			}
			break;
		}

	}

	// �߷��� 0�̻��̶��� �ȼ��浹�� //
	if (gravity > 0)
	{
		// ���� �밢�� �ȼ� �浹(LeftDiagonal) - �𼭸� ������� �κ�  //
		for (int i = sensorLeftDiagonal.y - 5; i < sensorLeftDiagonal.y + 5; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorLeftDiagonal.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 96 && g == 25 && b == 134))
			{
				gravity = 0.0f;								//�𼭸� ������ �߷� 0����~
				sensorBottom.isJump = false;				//������ �� �� �ֵ��� false

				if (KEYMANAGER->isStayKeyDown(VK_DOWN))		//�𼭸� ����ä�� DOWNŰ ������
				{
					y += 10;								//�÷��̾� �������� �ְ�
				}

				if (KEYMANAGER->isOnceKeyDown(VK_UP))		//�𼭸� ����ä�� UPŰ ������ �ε巴�� �ö󰡾��ϴµ� ����...�̤�
				{
					y -= 60;
					x -= 50;
				}
				break;
			}
		}//���� �밢�� �ȼ��浹 for�� END

		//������ �밢�� �ȼ� �浹(RightDiagonal) - �𼭸� ������� �κ� //
		for (int i = sensorRightDiagonal.y - 5; i < sensorRightDiagonal.y + 5; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(CollisionStage)->getMemDC(), sensorRightDiagonal.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 96 && g == 25 && b == 134))
			{
				gravity = 0.0f;								//�𼭸� ������ �߷� 0����~
				sensorBottom.isJump = false;				//������ �� �� �ֵ��� false

				if (KEYMANAGER->isStayKeyDown(VK_DOWN))		//�𼭸� ����ä�� DOWNŰ ������
				{
					y += 10;								//�÷��̾� �������� �ְ�

				}
				if (KEYMANAGER->isStayKeyDown(VK_UP))		//�𼭸� ����ä�� UPŰ ������ �ε巴�� �ö󰡾��ϴµ� ����...�̤�
				{
					y -= 60;
					x += 50;
				}
				break;
			}
		}//������ �밢�� �ȼ��浹 for�� END
	}
}

/*====================================================
			playerAttack() - �÷��̾� ���� -
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
playerStateFrameImageRender(float x, float y) - �ൿ ���� ó�� -
================================================================*/
void PlayerClass::playerStateFrameImageRender(float x, float y)
{
	//Enum���� ����� �÷��̾� �̹��� ���� ��ȭ
	switch (playerState)
	{
	case PlayerClass::IDLE:								// ���
		if (isLeft)		//�����̸�?
		{
			//��� ��� �̹��� ������ ������
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
		else			//�������̸�?
		{
			//��� ��� �̹��� ������ ������
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

	case PlayerClass::RUN:								//�ٱ�
		if (isLeft)									//���� �÷��̾ ������ �Ѵٸ�(false���) �޸��� �̹��� ��� ���ϵ���
		{
			if (!isJumpCheck && !isAttack)
			{
				//�������� �ٴ� �̹��� ������ ������
				IMAGEMANAGER->findImage("pipRun")->setFrameY(1);
				imgCount++;															//Ű�� ������ ������ �̹���ī��Ʈ�� ����(++)
				if (imgCount % 3 == 0)												//�̹��� ī��Ʈ�� 5�γ��� �������� 0�̸�
				{
					imgIndex++;														//�̹��� �ε��� ����(++)
					if (imgIndex > 11)												//�̹��� �ε����� ������ �ε��� �ʰ��ɰ��
					{
						imgIndex = 0;												//�̹��� �ε��� 0���� �ʱ�ȭ
					}
					IMAGEMANAGER->findImage("pipRun")->setFrameX(imgIndex);			//x�� ������ �� ������~
				}
				IMAGEMANAGER->findImage("pipRun")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			}//if(!isJumpCheck && !isAttack) END
		}
		else
		{
			if (!isJumpCheck && !isAttack)
			{
				//���������� �ٴ� �̹��� ������ ������
				IMAGEMANAGER->findImage("pipRun")->setFrameY(0);
				imgCount++;															//Ű�� ������ ������ �̹���ī��Ʈ�� ����(++)
				if (imgCount % 3 == 0)												//�̹��� ī��Ʈ�� 5�γ��� �������� 0�̸�
				{
					imgIndex++;														//�̹��� �ε��� ����(++)
					if (imgIndex > 11)												//�̹��� �ε����� ������ �ε��� �ʰ��ɰ��
					{
						imgIndex = 0;												//�̹��� �ε��� 0���� �ʱ�ȭ
					}
					IMAGEMANAGER->findImage("pipRun")->setFrameX(imgIndex);			//x�� ������ �� ������~
				}
				IMAGEMANAGER->findImage("pipRun")->frameRender(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
			}
		}
		break;

	case PlayerClass::ATTACK:							//����
		if (isLeft && isAttack)		//�����̸�
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
		else if (!isLeft && isAttack)						//�������̸�
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

	case PlayerClass::JUMP:								//����
		if (isLeft)
		{
			if (gravity < 0 && isJumpCheck)		//�߷��� 0�̸��̸�?
			{
				//���� ����
				//���� �ٴ� �̹��� ������
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

			if (gravity > 0 && isJumpCheck)		//�߷��� 0 �ʰ���?
			{
				//�����ϴ� �̹��� ������ ������
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
				//������ ����
				//���� �ٴ� �̹��� ������
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

	case PlayerClass::GRAB:								//�����
		if (isLeft)
		{
			//����(true)
			IMAGEMANAGER->findImage("pipGrabLeft")->render(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
		}
		else
		{
			//������(false)
			IMAGEMANAGER->findImage("pipGrabRight")->render(getMemDC(), x - CAMERA.getCRc().left, y - CAMERA.getCRc().top);
		}
		break;

	case PlayerClass::DOWNATTACK:						//�ٿ����
		break;

	default:
		break;
	}



}
