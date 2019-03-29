#pragma once
class CameraClass //�̱��� �������� ������ ī�޶�
{
public:
	static CameraClass& getInstance() //������ ��ȯ�� �Լ�
	{
		static CameraClass instance; // �Ҹ��� ȣ���� �����. ī�޶� �ش� Ŭ���������� ������ �������� ����
		return instance; //����ƽ ���������� �ʱ�ȭ�� ó�� �ѹ��� �̷�����ٴ� ����� �̿�, ���� �����ϸ� �����ϴ°� �����ڷ� ��ȯ, ���ٸ� ���� �̴�
	}

private:
	CameraClass(); //�̱����̴� ������� �߰��� �������� ���ϰ� ���Ƶ�
	~CameraClass() {}; //���������� ���α׷� ����� �˾Ƽ� ������ �ܺ� ȣ��� ���� ������ �������� �Ҹ��ڵ� �ϴ��� ���ܵ�
	

private: //�� ���� �ϴ���� �����̺��� �� ������ �ְ� �����ϸ� �˴ϴ�
	
	RECT cRc;				//ī�޶� ��Ʈ
	float cX, cY;			//ī�޶� �߽���ǥ
	float cWidth;			//ī�޶� ���α���
	float cHeight;			//ī�޶� ���α���


public: //����ͼ��Ͱ��� ���� �ϴ���� ���� �ۺ��� �Լ� ����� ��!

	//ī�޶� ���󰡴� �Լ�
	void cameraFollow(float _cX, float _cY);
	//ī�޶� �ܰ��� �����Ǵ� �Լ�
	void cameraRevision(float _bgWidth, float _bgHeight);
	void cameraRevisionWorldMap(float _bgWidth, float _bgHeight, float zoom);
	//ī�޶� ������ ���� �����ǰ� �ϴ� �Լ�
	void cameraRevision(float _startCX, float _startCY, float _endCX, float _endCY);


	RECT getCRc() { return cRc; }
	void setCRc(RECT _cRc) { cRc = _cRc; }

	float getCX() { return cX; }
	void setCX(float _cX) { cX = _cX; }

	float getCY() { return cY; }
	void setCY(float _cY) { cY = _cY; }

};

