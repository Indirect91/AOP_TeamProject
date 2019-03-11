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
		//SCENEMANAGER->loadScene("BossStage");
		//SCENEMANAGER->loadScene("Stage1");
		SCENEMANAGER->loadScene("Title");
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
	//스테이지 1번
	_loading->loadImage("Stage1Collision", "(수정) 다만들어진 1스테이지.bmp", 17520, 2436, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1", "Stage1_Resized.bmp", 17520, 2436, true, RGB(255, 0, 255));
	//보스 스테이지
	_loading->loadImage("BossStage", "Boss_stage_Resized.bmp", 10976, 2436, true, RGB(255, 0, 255));
	_loading->loadImage("BossStageCollision", "보스 스테이지.bmp", 10976, 2436, true, RGB(255, 0, 255));

	//타이틀 씬
	_loading->loadImage("titleBg", "titleBg.bmp", 1366, 768);
	_loading->loadImage("titleLogo", "titleLogo.bmp", 599, 254, true, RGB(255, 0, 255));
	_loading->loadImage("pip1", "pip1.bmp", 240, 228, true, RGB(255, 0, 255));
	_loading->loadImage("pip2", "pip2.bmp", 252, 325, true, RGB(255, 0, 255));
	_loading->loadImage("pip3", "pip3.bmp", 450, 472, true, RGB(255, 0, 255));
	_loading->loadImage("PressEnter", "PressEnter.bmp", 488, 97, true, RGB(255, 0, 255));
	_loading->loadImage("PressEsc", "PressEsc.bmp", 217, 63, true, RGB(255, 0, 255));
	
	//세이브 슬롯 픽화면
	_loading->loadImage("fileSelect", "FileSelect(1000,510).bmp", 1000, 510, true, RGB(255, 0, 255));
	_loading->loadImage("loadFile", "LoadFile(219,266).bmp", 219, 266, true, RGB(255, 0, 255));
	_loading->loadImage("ESC_YSetting", "ESC_YSetting(1368,82).bmp", 1368, 82, true, RGB(255, 0, 255));
	_loading->loadImage("newEmpty", "newEmpty(219,266).bmp", 219, 266, true, RGB(255, 0, 255));
	_loading->loadImage("selection", "Selection (338, 361).bmp", 338, 361, true, RGB(255, 0, 255));

	//인간 핍(픽셀)
	_loading->loadFrameImage("pipIdle", "image/pipidle(49,76) 15장.bmp", 735, 152, 15, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipAttackLeft", "image/pipattack(95,75)Left 12장.bmp", 1140, 75, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipAttackRight", "image/pipattack(95,75)Right 12장.bmp", 1140, 75, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipRun", "image/pipRun (73,71) 12장.bmp", 876, 142, 12, 2, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrabLeft", "image/pipGrabLeft.bmp", 54, 73, true, RGB(255, 0, 255));
	_loading->loadImage("pipGrabRight", "image/pipGrabRight.bmp", 54, 73, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipJumpUp", "image/인간핍 점프상승 (54,76) 7장.bmp", 378, 152, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipJumpDown", "image/인간핍 점프하락 (73,82)6장.bmp", 438, 164, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipDownAttack", "image/인간핍 공격하단(93,184) 11장.bmp", 1023, 184, 11, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pipChangeForm", "image/변신핍(76,114) 10장.bmp", 570, 152, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("changeEffect", "image/changeEffect.bmp", 4400, 100, 44, 1, true, RGB(255, 0, 255));
	//젤리 핍(젤리)
	_loading->loadFrameImage("jellyStay", "image/젤리대기(46,37) 8장.bmp", 368, 37, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jellyMove", "image/젤리이동.bmp", 120, 47, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jellyJumpUp", "image/젤리점프.bmp", 400, 42, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jellyJumpDown", "image/젤리점프다운.bmp", 562, 43, 11, 1, true, RGB(255, 0, 255));

	//스테이지 뒷배경
	_loading->loadImage("나무배경1", "나무배경1.bmp", 1788, 740);
	_loading->loadImage("나무배경2", "나무배경2.bmp", 1700, 794, true, RGB(255, 0, 255));
	_loading->loadImage("나무배경3", "나무배경3.bmp", 1487, 771, true, RGB(255, 0, 255));
	_loading->loadImage("나무배경4", "나무배경4.bmp", 1204, 1412, true, RGB(255, 0, 255));

	//에너미
	_loading->loadFrameImage("enemy-떠다니는 문어", "enemy-떠다니는 문어.bmp", 940, 66, 20, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-기어다니는 벌레", "enemy-기어다니는 벌레.bmp", 940, 48, 20, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-떠다니는 크리스탈", "enemy-떠다니는 크리스탈.bmp", 1170, 166, 13, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("enemy-둥둥이 유령", "enemy-둥둥이 유령.bmp", 236, 140, 4, 2, true, RGB(255, 0, 255));

	//펫
	_loading->loadFrameImage("pets-박쥐", "pets-박쥐.bmp", 840, 96, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pets-물개", "pets-물개.bmp", 960, 130, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("pets-상어", "pets-상어.bmp", 320, 104, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("펫 하트", "이펙트 - 하트 _5장.bmp", 250, 42, 5, 1, true, RGB(255, 0, 255));

	//지형물
	_loading->loadFrameImage("세이브 포인트", "세이브 포인트.bmp", 390, 126, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("세이브 빛", "세이브 빛.bmp", 1850, 105, 37, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보물상자", "보물상자.bmp", 180, 88, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보석", "보석.bmp", 260, 20, 13, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("클리어 포인트", "이펙트-클리어 포인트 2_8장.bmp", 1856, 308, 8, 1, true, RGB(255, 0, 255));

	//지형
	_loading->loadFrameImage("변신타일", "변신하면부서지는 타일.bmp", 1260, 45, 28, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("폭발", "변신타일 터지는모습.bmp", 540, 45, 12, 1, true, RGB(255, 0, 255));

	//총알
	_loading->loadImage("총알", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));

	//UI
	_loading->loadImage("UI-보석모양", "UI - 보석이미지.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadFrameImage("UI-체력", "UI - 체력 _2장.bmp", 102, 47, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("UI-펫 발견", "UI - 펫 발견 이미지.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));


}

void loadingScene::loadingSound()
{

}
