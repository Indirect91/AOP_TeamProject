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
		//SCENEMANAGER->loadScene("BossStage");
		//SCENEMANAGER->loadScene("Stage1");
		SCENEMANAGER->loadScene("Title");
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
	//�������� 1��
	_loading->loadImage("Stage1Collision", "(����) �ٸ������ 1��������.bmp", 17520, 2436, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1", "Stage1_Resized.bmp", 17520, 2436, true, RGB(255, 0, 255));
	//���� ��������
	_loading->loadImage("BossStage", "Boss_stage_Resized.bmp", 10976, 2436, true, RGB(255, 0, 255));
	_loading->loadImage("BossStageCollision", "���� ��������.bmp", 10976, 2436, true, RGB(255, 0, 255));

	//Ÿ��Ʋ ��
	_loading->loadImage("titleBg", "titleBg.bmp", 1366, 768);
	_loading->loadImage("titleLogo", "titleLogo.bmp", 599, 254, true, RGB(255, 0, 255));
	_loading->loadImage("pip1", "pip1.bmp", 240, 228, true, RGB(255, 0, 255));
	_loading->loadImage("pip2", "pip2.bmp", 252, 325, true, RGB(255, 0, 255));
	_loading->loadImage("pip3", "pip3.bmp", 450, 472, true, RGB(255, 0, 255));
	_loading->loadImage("PressEnter", "PressEnter.bmp", 488, 97, true, RGB(255, 0, 255));
	_loading->loadImage("PressEsc", "PressEsc.bmp", 217, 63, true, RGB(255, 0, 255));
	
	//���̺� ���� ��ȭ��
	_loading->loadImage("fileSelect", "FileSelect(1000,510).bmp", 1000, 510, true, RGB(255, 0, 255));
	_loading->loadImage("loadFile", "LoadFile(219,266).bmp", 219, 266, true, RGB(255, 0, 255));
	_loading->loadImage("ESC_YSetting", "ESC_YSetting(1368,82).bmp", 1368, 82, true, RGB(255, 0, 255));
	_loading->loadImage("newEmpty", "newEmpty(219,266).bmp", 219, 266, true, RGB(255, 0, 255));
	_loading->loadImage("selection", "Selection (338, 361).bmp", 338, 361, true, RGB(255, 0, 255));

	//�ΰ� ��(�ȼ�)
	_loading->loadFrameImage("pipIdle", "image/pipidle(49,76) 15��.bmp", 735, 152, 15, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipAttackLeft", "image/pipattack(95,75)Left 12��.bmp", 1140, 75, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipAttackRight", "image/pipattack(95,75)Right 12��.bmp", 1140, 75, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipRun", "image/pipRun (73,71) 12��.bmp", 876, 142, 12, 2, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrabLeft", "image/pipGrabLeft.bmp", 54, 73, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrabRight", "image/pipGrabRight.bmp", 54, 73, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipJumpUp", "image/�ΰ��� ������� (54,76) 7��.bmp", 378, 152, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipJumpDown", "image/�ΰ��� �����϶� (73,82)6��.bmp", 438, 164, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipDownAttack", "image/�ΰ��� �����ϴ�(93,184) 11��.bmp", 1023, 184, 11, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipChangeForm", "image/������(76,114) 10��.bmp", 570, 152, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("changeEffect", "image/changeEffect.bmp", 4400, 100, 44, 1, true, RGB(255, 0, 255));
	//���� ��(����)
	_loading->loadFrameImage("jellyStay", "image/�������(46,37) 8��.bmp", 368, 37, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jellyMove", "image/�����̵�.bmp", 120, 47, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jellyJumpUp", "image/��������.bmp", 400, 42, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jellyJumpDown", "image/���������ٿ�.bmp", 562, 43, 11, 1, true, RGB(255, 0, 255));

	//�������� �޹��
	_loading->loadImage("�������1", "�������1.bmp", 1788, 740);
	_loading->loadImage("�������2", "�������2.bmp", 1700, 794, true, RGB(255, 0, 255));
	_loading->loadImage("�������3", "�������3.bmp", 1487, 771, true, RGB(255, 0, 255));
	_loading->loadImage("�������4", "�������4.bmp", 1204, 1412, true, RGB(255, 0, 255));

	//���ʹ�
	_loading->loadFrameImage("enemy-���ٴϴ� ����", "enemy-���ٴϴ� ����.bmp", 940, 66, 20, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-���ٴϴ� ����", "enemy-���ٴϴ� ����.bmp", 940, 48, 20, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-���ٴϴ� ũ����Ż", "enemy-���ٴϴ� ũ����Ż.bmp", 1170, 166, 13, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-�յ��� ����", "enemy-�յ��� ����.bmp", 236, 140, 4, 2, true, RGB(255, 0, 255));

	//��
	_loading->loadFrameImage("pets-����", "pets-����.bmp", 840, 96, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pets-����", "pets-����.bmp", 960, 130, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pets-���", "pets-���.bmp", 320, 104, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�� ��Ʈ", "����Ʈ - ��Ʈ _5��.bmp", 250, 42, 5, 1, true, RGB(255, 0, 255));

	//������
	_loading->loadFrameImage("���̺� ����Ʈ", "���̺� ����Ʈ.bmp", 390, 126, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("���̺� ��", "���̺� ��.bmp", 1850, 105, 37, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��������", "��������.bmp", 180, 88, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����", "����.bmp", 260, 20, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ŭ���� ����Ʈ", "����Ʈ-Ŭ���� ����Ʈ 2_8��.bmp", 1856, 308, 8, 1, true, RGB(255, 0, 255));

	//����
	_loading->loadFrameImage("����Ÿ��", "�����ϸ�μ����� Ÿ��.bmp", 1260, 45, 28, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����", "����Ÿ�� �����¸��.bmp", 540, 45, 12, 1, true, RGB(255, 0, 255));

	//�Ѿ�
	_loading->loadImage("�Ѿ�", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));

	//UI
	_loading->loadImage("UI-�������", "UI - �����̹���.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadFrameImage("UI-ü��", "UI - ü�� _2��.bmp", 102, 47, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("UI-�� �߰�", "UI - �� �߰� �̹���.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));


}

void loadingScene::loadingSound()
{

}
