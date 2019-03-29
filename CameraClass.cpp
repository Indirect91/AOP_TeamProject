#include "stdafx.h"
#include "CameraClass.h"


CameraClass::CameraClass()
{
	//�̴��� �����. ���⿡ ���� ī�޶� �̴ֿ� �ִ��� ���� �ڵ��ϸ� ��!

	cX = WINSIZEX / 2;
	cY = WINSIZEY / 2;
	cWidth = WINSIZEX;
	cHeight = WINSIZEY;
}

//ī�޶� ���󰡴� �Լ�
void CameraClass::cameraFollow(float _cX, float _cY)
{
	//�������� ���� �ش� ��ġ��ǥ�� ����
	cX = _cX;
	cY = _cY;

	//�׸���
	cRc = RectMakeCenter(cX, cY, cWidth, cHeight);

}

//ī�޶� �ܰ��� �����Ǵ� �Լ�
void CameraClass::cameraRevision(float _bgWidth, float _bgHeight)
{
	//ī�޶� ����� ���� ������ ������
	if (cRc.left < 0)
	{
		cX = WINSIZEX / 2;
	}
	//ī�޶� ����� ������ ������ ������(��濡 ���߾�)
	else if (cRc.right > _bgWidth)
	{
		cX = _bgWidth - WINSIZEX / 2;
	}
	//ī�޶� ����� ���� ������ ������
	if (cRc.top < 0)
	{
		cY = WINSIZEY / 2;
	}
	//ī�޶� ����� �Ʒ��� ������ ������(��濡 ���߾�)
	else if (cRc.bottom > _bgHeight)
	{
		cY = _bgHeight - WINSIZEY / 2;
	}

	//������ �� �׸���
	cRc = RectMakeCenter(cX, cY, cWidth, cHeight);

}

void CameraClass::cameraRevisionWorldMap(float _bgWidth, float _bgHeight, float zoom)
{
	//ī�޶� ����� ���� ������ ������
	if (cRc.left < _bgWidth/2 - (_bgWidth/2)*zoom)
	{
		cX = WINSIZEX/2;
	}
	//ī�޶� ����� ������ ������ ������(��濡 ���߾�)
	else if (cRc.right > _bgWidth / 2 + _bgWidth * zoom / 2)
	{
		cX = _bgWidth - WINSIZEX / 2;
	}
	//ī�޶� ����� ���� ������ ������
	if (cRc.top < 0)
	{
		//cY = WINSIZEY / 2;
	}
	//ī�޶� ����� �Ʒ��� ������ ������(��濡 ���߾�)
	else if (cRc.bottom > _bgHeight)
	{
		//cY = _bgHeight - WINSIZEY / 2;
	}

	//������ �� �׸���
	cRc = RectMakeCenter(cX, cY, cWidth, cHeight);

}

//ī�޶� ������ ���� �����ǰ� �ϴ� �Լ�
void CameraClass::cameraRevision(float _startCX, float _startCY, float _endCX, float _endCY)
{
	if (cX > _startCX && cX < _endCX && cY > _startCY && cY < _endCY)
	{
		//ī�޶� ����� ���� ������ ������
		if (cRc.left < _startCX)
		{
			cX = _startCX + WINSIZEX / 2;
		}
		//ī�޶� ����� ������ ������ ������(��濡 ���߾�)
		else if (cRc.right > _endCX)
		{
			cX = _endCX - WINSIZEX / 2;
		}
		//ī�޶� ����� ���� ������ ������
		if (cRc.top < _startCY)
		{
			cY = _startCY + WINSIZEY / 2;
		}
		//ī�޶� ����� �Ʒ��� ������ ������(��濡 ���߾�)
		else if (cRc.bottom > _endCY)
		{
			cY = _endCY - WINSIZEY / 2;
		}
	}

	//������ �� �׸���
	cRc = RectMakeCenter(cX, cY, cWidth, cHeight);

}

