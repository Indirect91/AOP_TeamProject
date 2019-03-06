#include "stdafx.h"
#include "PlayerClass.h"

HRESULT PlayerClass::init(void)
{
	//�÷��̾� ���� �ʱ�ȭ
	x = 100;					//�÷��̾� x��ǥ
	y = WINSIZEY / 2;			//�÷��̾� y��ǥ
	width = 50;					//�÷��̾� ���� ����
	height = 50;				//�÷��̾� ���α���
	speed = 5.0f;				//�÷��̾� ���ǵ�
	gravity = 0.0f;				//�߷�
	addtionalPower = 0.0f;		//���������� ���� �߰����� �Ŀ�(��������)
	leftPower = 0.0f;			//���ʿ��� ������� ��(�ݹ߷�)
	rightPower = 0.0f;			//�����ʿ��� ������� ��(�ݹ߷�)
	isAttack = false;			//������ �ߴ��� �Ǵ�
	imgCount = 0;				//�̹����� ���� ī��Ʈ
	imgIndex = 0;				//�̹��� �ε��� ������ ���� ����
	isLeft = false;
	isjumpCheck = false;


	// ���� ���� �ʱ�ȭ //
	//���� ����
	sensorLeft.x = x;
	sensorLeft.y = y + height / 2;
	sensorLeft.isJump = false;
	//���� ��
	sensorTop.x = x + width / 2;
	sensorTop.y = y;
	sensorTop.isJump = false;
	//���� ������
	sensorRight.x = x + width;
	sensorRight.y = y + height / 2;
	sensorRight.isJump = false;

	//���� �Ʒ�
	sensorBottom.x = x + width / 2;
	sensorRight.y = y + height;
	sensorBottom.isJump = false;
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
	//������ �밢��
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
	this->pipAttack();			//�÷��̾� ����

	//�÷��̾ �߷� �����Ų��.
	y += gravity;

	//�ݹ߷� ����
	x += rightPower; //�׽� �ۿ��ϴ� ���� ����� �����Ѵ�. 0�̸� ��� ���� ������?
	x -= leftPower;
}

void PlayerClass::render(void)
{
	//Enum���� ����� �÷��̾� �̹��� ���� ��ȭ
	switch (playerState)
	{
	case PlayerClass::IDLE:
		if (isLeft)		//isLeft��   
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
			IMAGEMANAGER->findImage("pipIdle")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
		}
		//isLeft�� false��
		else
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
		{	//���� ����
			//IMAGEMANAGER->findImage("pipJumpUp")->setFrameY(0);
			IMAGEMANAGER->findImage("pipJumpUp")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
			if (gravity > 0)
			{
				//IMAGEMANAGER->findImage("pipJumpDown")->setFrameY(0);
				IMAGEMANAGER->findImage("pipJumpDown")->frameRender(getMemDC(), x + 5 - CAMERA.getCRc().left, y + 10 - CAMERA.getCRc().top);
			}
		}
		else
		{	//������ ����
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

	//���Ű�� ��Ʈ ���������� Ȯ���� �� ����
	if (KEYMANAGER->isToggleKey('Q'))
	{
		//�÷��̾� ����
		Rectangle(getMemDC(), RelativeCameraRect(playerRc));

		//���� ����
		Rectangle(getMemDC(), RelativeCameraRect(sensorLeft.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorTop.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorRight.sensorRc));

		Rectangle(getMemDC(), RelativeCameraRect(sensorBottom.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorLeftBottom.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorRightBottom.sensorRc));

		Rectangle(getMemDC(), RelativeCameraRect(sensorLeftDiagonal.sensorRc));
		Rectangle(getMemDC(), RelativeCameraRect(sensorRightDiagonal.sensorRc));

		//���� ���� ��Ʈ ����
		Rectangle(getMemDC(), RelativeCameraRect(attackRc));
	}
}

//�÷��̾� ������
void PlayerClass::playerMove()
{

	//������ ������
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		isLeft = false;			//false�� ������ ������ �̹���
		x += speed;				//�÷��̾� �ӵ���ŭ x�� �̵�(�������̴ϱ� x�� ����)

		// ������ �����������ϱ� ���� ���������� �ٰ��ֽ��ϴ�.
		playerState = PlayerClass::RUN;
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

	}
	//���� ������
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		isLeft = true;			//true�� ���� ������ �̹���
		x -= speed;				//�÷��̾� �ӵ���ŭ x�� �̵�(�����̴ϱ� x�� ����)

		//������ ������ �ִ��ϱ� ���� �������� �ٰ��ֽ��ϴ�.
		playerState = PlayerClass::RUN;
		//�������� �ٴ� �̹��� ������ ������
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
		// �޸��� �ִٰ� ����� ? �׷��� IDLE�� ���ư� ��
		playerState = PlayerClass::IDLE;
	}

	//����(���� ���� : ����Ű ���� �ð��� ���� ������ ��� / ������ �ִ�ġ ����)
	if (sensorBottom.isJump == false)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{

			//�ݹ߷� ����
			if (sensorLeft.isJump == true)		//���� ������ ���� �Һ����� true��
			{
				sensorRight.isJump = false;
				rightPower = 7.5f;				//���������� �ݹ߷� �ֱ�~
			}
			if (sensorRight.isJump == true)		//������ ������ ���� �Һ����� true��
			{
				sensorLeft.isJump = false;
				sensorRight.isJump = false;
				leftPower = 7.5f;				//�������� �ݹ߷� �ֱ�~
			}

			y -= 20;							//���� �Ҷ� ��¦ ����ش�
			gravity = -1.8f;					//�߷� ������Ű��


//------------------------------------------
			playerState = PlayerClass::JUMP;
			//�ӽ÷� �غ� ���� �̹���
			if (isLeft)
			{	//����
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
				//���� �����ϴ� �̹��� ������!!
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
			{	//������
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
				//���� �����ϴ� �̹��� ������!!
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

		if (KEYMANAGER->isStayKeyDown('C'))		//���� ����
		{
			if (addtionalPower <= 1.6f)			//�������� �Ŀ��� 1.6f���ϸ� 
			{
				addtionalPower += 0.2f;			//�Ŀ��� �߰������ش�.
			}
			if (addtionalPower <= 1.6f)
			{
				gravity -= addtionalPower;
			}
		}
		if (KEYMANAGER->isOnceKeyUp('C'))
		{
			//gravity = 0.0f;
			addtionalPower = 0.0f;				//���� Ű�� ���� ���� ���� �Ŀ� 0.0f�� �ʱ�ȭ
			sensorBottom.isJump = true;			//2�� ���� �������� ���ϰ� ���� true�� ����
		}
	}

	//�÷��̾� ���� ���� ������Ʈ
	playerRc = RectMake(x, y, width, height);
}

//���� ������
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

	//sensorBottom.sensorRc = RectMakeCenter(sensorBottom.x, sensorBottom.y, 30, 5);
	sensorLeftBottom.sensorRc = RectMakeCenter(sensorLeftBottom.x, sensorLeftBottom.y, 5, 5);
	sensorRightBottom.sensorRc = RectMakeCenter(sensorRightBottom.x, sensorRightBottom.y, 5, 5);

	sensorLeftDiagonal.sensorRc = RectMakeCenter(sensorLeftDiagonal.x, sensorLeftDiagonal.y, 5, 5);
	sensorRightDiagonal.sensorRc = RectMakeCenter(sensorRightDiagonal.x, sensorRightDiagonal.y, 5, 5);
}

//�ȼ� �浹
void PlayerClass::pixelCollision()
//���ڰ��� ������Ʈ�� �̰� ���� ��� ���� ������ �ȼ��浹�� �����ϰ� 
{
	//���� �ȼ� �浹(Left)//
	for (int i = sensorLeft.x; i < sensorLeft.x + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), i, sensorLeft.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 255 && b == 0))					//RGB���� 0,255,0 �̸�
		{
			x = i + width / 5 - 5;							//�÷��̾� x���� �������� �÷��̾� ���θ� 5�� ���� �����ش�.
															//�������� �İ���� �ʰ� �ϱ� ����
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))			//���� ����ä�� ����Ű�� ������
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
			break;

		}
	}

	//�� �ȼ� �浹(Top)//
	for (int i = sensorTop.y - 5; i < sensorTop.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorTop.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 0))
		{
			y += 5;				//�������� ���� �Ÿ��� �̰ݽ�Ų��.
			gravity = 0.0f;		//�� �� �߷��� 0���� ��������� �߷°��� �ٽ� �ް�
			break;
		}
	}

	//������ �ȼ� �浹(Right)//
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
			break;
		}
	}

	//�Ʒ� �ȼ� �浹(Bottom)//
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

	//���� �Ʒ� �ȼ� �浹(Bottom)//
	for (int i = sensorLeftBottom.y - 5; i < sensorLeftBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorLeftBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		//�Ϲ� Ÿ�� �浹
		if ((r == 255 && g == 255 && b == 0))
		{
			y = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
		//�������� Ÿ�� �浹
		if ((r == 91 && g == 63 && b == 34))
		{
			y = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
	}

	//������ �Ʒ� �ȼ� �浹(Bottom)//
	for (int i = sensorRightBottom.y - 5; i < sensorRightBottom.y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Collision")->getMemDC(), sensorRightBottom.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//�Ϲ� Ÿ�� �浹
		if ((r == 255 && g == 255 && b == 0))
		{
			y = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
		//�������� Ÿ�� �浹
		if ((r == 91 && g == 63 && b == 34))
		{
			y = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
	}

	//�߷��� 0�̻��̶��� �ȼ��浹��//
	if (gravity > 0)
	{
		//���� �밢�� �ȼ� �浹(LeftDiagonal)//
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

		//������ �밢�� �ȼ� �浹(RightDiagonal)//
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
