#include "stdafx.h"
#include "CameraClass.h"


CameraClass::CameraClass()
{
	//이닛을 대신함. 여기에 원래 카메라 이닛에 넣던거 여기 코딩하면 됨!

	cX = WINSIZEX / 2;
	cY = WINSIZEY / 2;
	cWidth = WINSIZEX;
	cHeight = WINSIZEY;
}

//카메라가 따라가는 함수
void CameraClass::cameraFollow(float _cX, float _cY)
{
	//움직임을 찍을 해당 위치좌표를 대입
	cX = _cX;
	cY = _cY;

	//그리기
	cRc = RectMakeCenter(cX, cY, cWidth, cHeight);

}

//카메라가 외각만 보정되는 함수
void CameraClass::cameraRevision(float _bgWidth, float _bgHeight)
{
	//카메라가 배경의 왼쪽 밖으로 나갈때
	if (cRc.left < 0)
	{
		cX = WINSIZEX / 2;
	}
	//카메라가 배경의 오른쪽 밖으로 나갈때(배경에 맞추어)
	else if (cRc.right > _bgWidth)
	{
		cX = _bgWidth - WINSIZEX / 2;
	}
	//카메라가 배경의 위쪽 밖으로 나갈때
	if (cRc.top < 0)
	{
		cY = WINSIZEY / 2;
	}
	//카메라가 배경의 아래쪽 밖으로 나갈때(배경에 맞추어)
	else if (cRc.bottom > _bgHeight)
	{
		cY = _bgHeight - WINSIZEY / 2;
	}

	//보정후 또 그리기
	cRc = RectMakeCenter(cX, cY, cWidth, cHeight);

}

void CameraClass::cameraRevisionWorldMap(float _bgWidth, float _bgHeight, float zoom)
{
	//카메라가 배경의 왼쪽 밖으로 나갈때
	if (cRc.left < _bgWidth/2 - (_bgWidth/2)*zoom)
	{
		cX = WINSIZEX/2;
	}
	//카메라가 배경의 오른쪽 밖으로 나갈때(배경에 맞추어)
	else if (cRc.right > _bgWidth / 2 + _bgWidth * zoom / 2)
	{
		cX = _bgWidth - WINSIZEX / 2;
	}
	//카메라가 배경의 위쪽 밖으로 나갈때
	if (cRc.top < 0)
	{
		//cY = WINSIZEY / 2;
	}
	//카메라가 배경의 아래쪽 밖으로 나갈때(배경에 맞추어)
	else if (cRc.bottom > _bgHeight)
	{
		//cY = _bgHeight - WINSIZEY / 2;
	}

	//보정후 또 그리기
	cRc = RectMakeCenter(cX, cY, cWidth, cHeight);

}

//카메라가 구간에 따라 보정되게 하는 함수
void CameraClass::cameraRevision(float _startCX, float _startCY, float _endCX, float _endCY)
{
	if (cX > _startCX && cX < _endCX && cY > _startCY && cY < _endCY)
	{
		//카메라가 배경의 왼쪽 밖으로 나갈때
		if (cRc.left < _startCX)
		{
			cX = _startCX + WINSIZEX / 2;
		}
		//카메라가 배경의 오른쪽 밖으로 나갈때(배경에 맞추어)
		else if (cRc.right > _endCX)
		{
			cX = _endCX - WINSIZEX / 2;
		}
		//카메라가 배경의 위쪽 밖으로 나갈때
		if (cRc.top < _startCY)
		{
			cY = _startCY + WINSIZEY / 2;
		}
		//카메라가 배경의 아래쪽 밖으로 나갈때(배경에 맞추어)
		else if (cRc.bottom > _endCY)
		{
			cY = _endCY - WINSIZEY / 2;
		}
	}

	//보정후 또 그리기
	cRc = RectMakeCenter(cX, cY, cWidth, cHeight);

}

