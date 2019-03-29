#pragma once
class CameraClass //싱글톤 패턴으로 구현된 카메라
{
public:
	static CameraClass& getInstance() //참조자 반환형 함수
	{
		static CameraClass instance; // 소멸자 호출이 보장됨. 카메라 해당 클래스에서만 가능한 지역정적 변수
		return instance; //스태틱 정적변수는 초기화가 처음 한번만 이루어진다는 사실을 이용, 만약 존재하면 존재하는걸 참조자로 반환, 없다면 새로 이닛
	}

private:
	CameraClass(); //싱글톤이니 딴사람이 추가로 생성하지 못하게 막아둠
	~CameraClass() {}; //정적변수는 프로그램 종료시 알아서 뒤지니 외부 호출로 인한 꼬임을 막기위해 소멸자도 일단은 숨겨둠
	

private: //▼ 원래 하던대로 프라이빗에 들어갈 변수들 넣고 진행하면 됩니다
	
	RECT cRc;				//카메라 렉트
	float cX, cY;			//카메라 중심좌표
	float cWidth;			//카메라 가로길이
	float cHeight;			//카메라 세로길이


public: //▼겟터셋터같은 원래 하던대로 여기 퍼블릭에 함수 만들면 됨!

	//카메라가 따라가는 함수
	void cameraFollow(float _cX, float _cY);
	//카메라가 외각만 보정되는 함수
	void cameraRevision(float _bgWidth, float _bgHeight);
	void cameraRevisionWorldMap(float _bgWidth, float _bgHeight, float zoom);
	//카메라가 구간에 따라 보정되게 하는 함수
	void cameraRevision(float _startCX, float _startCY, float _endCX, float _endCY);


	RECT getCRc() { return cRc; }
	void setCRc(RECT _cRc) { cRc = _cRc; }

	float getCX() { return cX; }
	void setCX(float _cX) { cX = _cX; }

	float getCY() { return cY; }
	void setCY(float _cY) { cY = _cY; }

};

