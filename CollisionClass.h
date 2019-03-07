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

	class PlayerClass* cPlayerPtr;
	class FieldManagerClass* cFieldPtr;

	vector <class EnemyManagerClass*>* cEnemyPtrV;
	vector <class PetsClass*>* cPetsPtrV;
	vector <class treasureBox*>* cTreasureBoxPtrV;
	class savePoint* cSavePointPtr;

	RECT cEmpty = { 0 };

	//get 플레이어 포인터
	//get 에너미 들어있는 벡터
	//get 타일 들어있는 백터


public: //▼겟터셋터같은 원래 하던대로 여기 퍼블릭에 함수 만들면 됨!

	void setPlayer(class PlayerClass* _cplayerPtr) { cPlayerPtr = _cplayerPtr; }

	void setFieldManagerClass(class FieldManagerClass* _cFieldPtrV) { cFieldPtr = _cFieldPtrV; }

	void setEnemyManagerClass(vector<class EnemyManagerClass*>* _cEnemyPtrV) { cEnemyPtrV = _cEnemyPtrV; }

	void setPetsClass(vector<class PetsClass*>* _cPetsPtrV) { cPetsPtrV = _cPetsPtrV; }

	void setTreasureBox(vector<class treasureBox*>* _cTreasureBoxPtrV) { cTreasureBoxPtrV = _cTreasureBoxPtrV; }

	void setSavePoint(class savePoint* _cSavePointPtr) { cSavePointPtr = _cSavePointPtr; }

	//플레이어가 에너미를 밟음
	void playerStepEnemy();
	//플레이어가 에너미랑 부딪힘
	void playerCrashedEnemy();

	//플레이어가 펫을 발견
	void playerFindPets();
	//플레이어가 세이브 포인트를 지남
	void playerSavePoint();
	//플레이어가 보물상자를 발견
	void playerFindTreasureBox();

	void playerGetJewel();
};
