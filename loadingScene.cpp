#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면(씬)변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("Stage1");
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
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
	_loading->loadImage("Stage1Collision", "(수정) 다만들어진 1스테이지.bmp", 17520, 2436, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1", "Stage1_Resized.bmp", 17520, 2436, true, RGB(255, 0, 255));

	//핍
	_loading->loadFrameImage("pipIdle", "image/핍 대기(49,76) 15장.bmp", 735, 152, 15, 2, true, RGB(255, 0, 255));
	//_loading->loadFrameImage("pipIdleLeft", "image/핍 대기(Left)(49,76) 15장.bmp", 735, 152, 15, 1, true, RGB(255, 0, 255));
	//_loading->loadFrameImage("pipIdleRight", "image/핍 대기(Right)(49,76) 15장.bmp", 735, 152, 15, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipAttack", "인간핍 공격(95,150) 12장.bmp", 1140, 150, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipRun", "image/pipRun (73,71) 12장(new).bmp", 876, 142, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jellyStay", "image/네모핍 대기(46,37) 8장.bmp", 368, 37, 8, 1, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrab", "image/pipGrab.bmp", 54, 146, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrabLeft", "image/pipGrabLeft.bmp", 54, 73, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrabRight", "image/pipGrabRight.bmp", 54, 73, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipJumpUp", "image/인간핍 점프상승 (54,76) 7장.bmp", 378, 152, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipJumpDown", "image/인간핍 점프하락 (73,82)6장.bmp", 438, 164, 6, 2, true, RGB(255, 0, 255));
	
	
	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//스테이지 뒷배경
	_loading->loadImage("나무배경1", "나무배경1.bmp", 1788, 740);
	_loading->loadImage("나무배경2", "나무배경2.bmp", 1700, 794, true, RGB(255, 0, 255));
	_loading->loadImage("나무배경3", "나무배경3.bmp", 1487, 771, true, RGB(255, 0, 255));
	_loading->loadImage("나무배경4", "나무배경4.bmp", 1204, 1412, true, RGB(255, 0, 255));

	//에너미
	_loading->loadFrameImage("enemy-떠다니는 문어", "enemy-떠다니는 문어.bmp", 940, 66, 20, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-기어다니는 벌레", "enemy-기어다니는 벌레.bmp", 940, 48, 20, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-떠다니는 크리스탈", "enemy-떠다니는 크리스탈.bmp", 1170, 166, 13, 2, true, RGB(255, 0, 255));

	//펫
	_loading->loadFrameImage("pets-박쥐", "pets-박쥐.bmp", 840, 96, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pets-물개", "pets-물개.bmp", 960, 130, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pets-상어", "pets-상어.bmp", 320, 104, 4, 2, true, RGB(255, 0, 255));

	//지형물
	_loading->loadFrameImage("세이브 포인트", "세이브 포인트.bmp", 390, 126, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("세이브 빛", "세이브 빛.bmp", 1850, 105, 37, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보물상자", "보물상자.bmp", 180, 88, 3, 2, true, RGB(255, 0, 255));

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
