#include "stdafx.h"
#include "bullet.h"
//=============================================================
//	## bullet ## (�����Ѿ� - ������� ����� �ȴ�)
//=============================================================
HRESULT bullet::init(const char * imageName, int bulletMax, float range)
{
	this->_bulletMax = bulletMax;
	this->_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ˱���ü ����
		tagBullet bullet;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage = IMAGEMANAGER->findImage(imageName);
		bullet.speed = 5.0f;
		bullet.fire = false;

		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}




	return S_OK;
}

void bullet::release(void)
{

}

void bullet::update(void)
{
	this->move();
}

void bullet::render(void)
{
	for (auto iBullets : _vBullet)
	{
		if (!iBullets.fire) continue;
		iBullets.bulletImage->render(getMemDC(), iBullets.rc.left - CAMERA.getCRc().left, iBullets.rc.top - CAMERA.getCRc().top);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	for (auto& iBullets : _vBullet)
	{
		if (iBullets.fire) continue;

		iBullets.fire = true;
		iBullets.angle = angle;
		iBullets.speed = speed;
		iBullets.x = iBullets.fireX = x;
		iBullets.y = iBullets.fireY = y;
		iBullets.rc = RectMakeCenter(iBullets.x, iBullets.y,
			iBullets.bulletImage->getWidth(),
			iBullets.bulletImage->getHeight());
		break;
	}
}

void bullet::move()
{
	for (auto &iBullet : _vBullet)
	{
		if (!iBullet.fire) continue;

		iBullet.x += cosf(iBullet.angle) * iBullet.speed;
		iBullet.y += -sinf(iBullet.angle) * iBullet.speed;

		iBullet.rc = RectMakeCenter(iBullet.x, iBullet.y,
			iBullet.bulletImage->getWidth(),
			iBullet.bulletImage->getHeight());

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = GetDistance(iBullet.fireX, iBullet.fireY,
			iBullet.x, iBullet.y);

		if (_range < distance)
		{
			iBullet.fire = false;
		}
	}
}

void bullet::removeBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}

