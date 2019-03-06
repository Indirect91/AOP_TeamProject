#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ��(��)����
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("Stage1");
	}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	float num = _loading->getLoadItem().size();
	float cur = _loading->getCurrentGauge();
	per = cur / num * 100;
	_loading->render(per);

	char str[128];
	sprintf(str, "%.f %%", per);
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOut(getMemDC(), 660, 662, str, strlen(str));

}

void loadingScene::loadingImage()
{
	_loading->loadImage("Stage1Collision", "(����) �ٸ������ 1��������.bmp", 17520, 2436, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1", "Stage1_Resized.bmp", 17520, 2436, true, RGB(255, 0, 255));

	//��
	_loading->loadFrameImage("pipIdle", "image/�� ���(49,76) 15��.bmp", 735, 152, 15, 2, true, RGB(255, 0, 255));
	//_loading->loadFrameImage("pipIdleLeft", "image/�� ���(Left)(49,76) 15��.bmp", 735, 152, 15, 1, true, RGB(255, 0, 255));
	//_loading->loadFrameImage("pipIdleRight", "image/�� ���(Right)(49,76) 15��.bmp", 735, 152, 15, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipAttack", "�ΰ��� ����(95,150) 12��.bmp", 1140, 150, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipRun", "image/pipRun (73,71) 12��(new).bmp", 876, 142, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jellyStay", "image/�׸��� ���(46,37) 8��.bmp", 368, 37, 8, 1, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrab", "image/pipGrab.bmp", 54, 146, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrabLeft", "image/pipGrabLeft.bmp", 54, 73, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrabRight", "image/pipGrabRight.bmp", 54, 73, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipJumpUp", "image/�ΰ��� ������� (54,76) 7��.bmp", 378, 152, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipJumpDown", "image/�ΰ��� �����϶� (73,82)6��.bmp", 438, 164, 6, 2, true, RGB(255, 0, 255));
	
	
	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//�������� �޹��
	_loading->loadImage("�������1", "�������1.bmp", 1788, 740);
	_loading->loadImage("�������2", "�������2.bmp", 1700, 794, true, RGB(255, 0, 255));
	_loading->loadImage("�������3", "�������3.bmp", 1487, 771, true, RGB(255, 0, 255));
	_loading->loadImage("�������4", "�������4.bmp", 1204, 1412, true, RGB(255, 0, 255));

	//���ʹ�
	_loading->loadFrameImage("enemy-���ٴϴ� ����", "enemy-���ٴϴ� ����.bmp", 940, 66, 20, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-���ٴϴ� ����", "enemy-���ٴϴ� ����.bmp", 940, 48, 20, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-���ٴϴ� ũ����Ż", "enemy-���ٴϴ� ũ����Ż.bmp", 1170, 166, 13, 2, true, RGB(255, 0, 255));

	//��
	_loading->loadFrameImage("pets-����", "pets-����.bmp", 840, 96, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pets-����", "pets-����.bmp", 960, 130, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pets-���", "pets-���.bmp", 320, 104, 4, 2, true, RGB(255, 0, 255));

	//������
	_loading->loadFrameImage("���̺� ����Ʈ", "���̺� ����Ʈ.bmp", 390, 126, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("���̺� ��", "���̺� ��.bmp", 1850, 105, 37, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��������", "��������.bmp", 180, 88, 3, 2, true, RGB(255, 0, 255));

	for (int i = 0; i < 50; i++)
	{
		char str[128];
		sprintf(str, "Image/TestImage_%d", i + 1);

		_loading->loadImage(str, WINSIZEX, WINSIZEY);
	}

}

void loadingScene::loadingSound()
{

}
