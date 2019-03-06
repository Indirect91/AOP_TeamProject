#pragma once
class CollisionClass
{
public:
	static CollisionClass& getInstance() //한번의 충돌을 위해 싱글톤화
	{
		static CollisionClass instance; 
		return instance; //스태틱 정적변수는 초기화가 처음 한번만 이루어진다는 사실을 이용, 만약 존재하면 존재하는걸 참조자로 반환, 없다면 새로 이닛
	}
private:
	CollisionClass() {}; //싱글톤이니 딴사람이 추가로 생성하지 못하게 막아둠
	~CollisionClass() {}; //정적변수는 프로그램 종료시 알아서 뒤지니 외부 호출로 인한 꼬임을 막기위해 소멸자도 일단은 숨겨둠


private: //▼ 원래 하던대로 프라이빗에 들어갈 변수들 넣고 진행하면 됩니다

	//get 플레이어 포인터
	//get 에너미 들어있는 벡터
	//get 타일 들어있는 백터


public: //▼겟터셋터같은 원래 하던대로 여기 퍼블릭에 함수 만들면 됨!

	//플레이어와 에너미 충돌 함수!



};

