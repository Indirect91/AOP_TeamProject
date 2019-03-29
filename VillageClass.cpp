#include "stdafx.h"
#include "VillageClass.h"
#include "PlayerClass.h"
#include "UIClass.h"

//=============�ʱ�ȭ=============
HRESULT VillageClass::init(void)
{
	SOUNDMANAGER->play("����", TXTDATA.refBGMSound());
	villageImg = IMAGEMANAGER->findImage("Village");
	villageBgImg = IMAGEMANAGER->findImage("Village ���");

	merchantHiImg = IMAGEMANAGER->findImage("����Ʈ-��ǳ��");
	merchantImg = IMAGEMANAGER->findImage("NPC-����");
	merchantRc = RectMakeCenter(1791, 665, 128, 132);
	imgVCount = 0;
	frameVX = 0;

	isMeet = false;

	vEmpty = { 0 };

	//�÷��̾� Ŭ���� ���� �� �ʱ�ȭ
	vPlayerPtr = new PlayerClass;
	vPlayerPtr->init(1594, 400, "VillageCollision");

	//UI Ŭ���� ���� �� �ʱ�ȭ
	vUIPtr = new UIClass;
	vUIPtr->init("");

	return S_OK;
}
//=============����=============
void VillageClass::release(void)
{
	//�÷��̾� Ŭ���� ����
	vPlayerPtr->release();
	SAFE_DELETE(vPlayerPtr);

	//UI Ŭ���� ����
	vUIPtr->release();
	SAFE_DELETE(vUIPtr);
}
//=============������Ʈ=============
void VillageClass::update(void)
{
	loopX++;

	//�÷��̾� Ŭ���� ������Ʈ
	if (vUIPtr->getIsShop() == false) vPlayerPtr->update();

	//UI Ŭ���� ������Ʈ
	vUIPtr->update();

	//���ΰ� ������ ��ǳ���� ������ �� ���¿��� �������� ��
	if (IntersectRect(&vEmpty, &vPlayerPtr->getRect(), &merchantRc)) isMeet = true;
	else isMeet = false;

	if (KEYMANAGER->isOnceKeyDown('M') && vUIPtr->getIsShop() == false)
	{
		vector<string> tempVec;
		char tempStr[50];

		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->pipMaxHP, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->pipRescued, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->pipMoney, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->pipCinematic, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindSealS1, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindBatS1, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindSharkS1, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindSealB, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindBatB, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindSharkB, tempStr, 10));
		tempVec.push_back(TXTDATA.getCurrentPipData()->firstItem);
		tempVec.push_back(TXTDATA.getCurrentPipData()->secondItem);
		tempVec.push_back(TXTDATA.getCurrentPipData()->thirdItem);

		TXTDATA.txtSave(TXTDATA.getWhichfile(), tempVec);


		SOUNDMANAGER->pause("����");
		SCENEMANAGER->loadScene("WorldMap");
	}

	//���ο��Լ� ������ ����� ���� ����
	if (KEYMANAGER->isStayKeyDown('J') && isMeet == true)
	{
		vUIPtr->setIsShop(true);
	}


	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && vUIPtr->getIsShop() == true)
	{
		vUIPtr->setSelectX(582);
		vUIPtr->setSelectY(227);
		vUIPtr->setIsShop(false);
	}




	//���� �ִϸ��̼�
	imgVCount++;
	if (imgVCount % 7 == 0)
	{
		frameVX++;
		if (frameVX > 11)
		{
			frameVX = 0;
		}
	}

	//ī�޶� �ޱ��� �÷��̾�� ��
	CAMERA.cameraFollow(vPlayerPtr->getX(), vPlayerPtr->getY());

	//���� ���
	CAMERA.cameraRevision(0, 0, 2750, 768);
}
//=============����=============
void VillageClass::render(void)
{
	RECT bgRc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	villageBgImg->loopRender(getMemDC(), &bgRc, loopX, 0);

	villageImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);

	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(merchantRc));
	}

	if (isMeet == true) merchantHiImg->render(getMemDC(), 1798 - CAMERA.getCRc().left, 549 - CAMERA.getCRc().top);
	merchantImg->frameRender(getMemDC(), merchantRc.left - CAMERA.getCRc().left, merchantRc.top - CAMERA.getCRc().top, frameVX, 0);

	//�÷��̾� ����
	vPlayerPtr->render();

	//UI ����
	vUIPtr->render();

	/*��ǥ Ȯ�ο�*/
	//SetBkMode(getMemDC(), TRANSPARENT);
	//TextOutfloat(getMemDC(), 10, 10, "���콺 X", _ptMouse.x + CAMERA.getCRc().left);
	//TextOutfloat(getMemDC(), 10, 30, "���콺 Y", _ptMouse.y + CAMERA.getCRc().top);
	//TextOutfloat(getMemDC(), 10, 50, "ī�޶� left", CAMERA.getCRc().left);
}
