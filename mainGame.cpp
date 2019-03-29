#include "stdafx.h"
#include "mainGame.h"
//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ�� �Ѵ�

	//������ ���ΰ��� Ŭ���� �ȿ����� ���鸸 ������ �Ѵ�
	//�׸��� ������ ������ ���ΰ��� ������ �ϸ� �ȴ�

	/*���߰�*/
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("Stage1", new Stage1Class);
	SCENEMANAGER->addScene("BossStage", new BossStageClass);
	SCENEMANAGER->addScene("Title", new TitleClass);
	SCENEMANAGER->addScene("WorldMap", new WorldMapScene);
	SCENEMANAGER->addScene("Village", new VillageClass);
	SCENEMANAGER->addScene("Cinema", new CinematicClass);
	SCENEMANAGER->addScene("Ending", new EndingSceneClass);

	//����� ����
	SCENEMANAGER->loadScene("�ε�ȭ��");

	return S_OK;
	//return S_OK; �Ʒ��� �ڵ尡 ������ �ȵ�!!!
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
	
}

//=============================================================
//	## ���� ## render(void)
//=============================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �α�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//���Ŵ��� ����
	SCENEMANAGER->render();

//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());
}


