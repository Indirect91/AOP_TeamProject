#pragma once
class CollisionClass
{
public:
	static CollisionClass& getInstance() //�ѹ��� �浹�� ���� �̱���ȭ
	{
		static CollisionClass instance;
		return instance; //����ƽ ���������� �ʱ�ȭ�� ó�� �ѹ��� �̷�����ٴ� ����� �̿�, ���� �����ϸ� �����ϴ°� �����ڷ� ��ȯ, ���ٸ� ���� �̴�
	}
private:
	CollisionClass() {}; //�̱����̴� ������� �߰��� �������� ���ϰ� ���Ƶ�
	~CollisionClass() {}; //���������� ���α׷� ����� �˾Ƽ� ������ �ܺ� ȣ��� ���� ������ �������� �Ҹ��ڵ� �ϴ��� ���ܵ�


private: //�� ���� �ϴ���� �����̺��� �� ������ �ְ� �����ϸ� �˴ϴ�

	class PlayerClass* cPlayerPtr;
	class FieldManagerClass* cFieldPtr;

	vector <class EnemyManagerClass*>* cEnemyPtrV;
	vector <class PetsClass*>* cPetsPtrV;
	vector <class treasureBox*>* cTreasureBoxPtrV;
	class savePoint* cSavePointPtr;

	RECT cEmpty = { 0 };

	//get �÷��̾� ������
	//get ���ʹ� ����ִ� ����
	//get Ÿ�� ����ִ� ����


public: //����ͼ��Ͱ��� ���� �ϴ���� ���� �ۺ��� �Լ� ����� ��!

	void setPlayer(class PlayerClass* _cplayerPtr) { cPlayerPtr = _cplayerPtr; }

	void setFieldManagerClass(class FieldManagerClass* _cFieldPtrV) { cFieldPtr = _cFieldPtrV; }

	void setEnemyManagerClass(vector<class EnemyManagerClass*>* _cEnemyPtrV) { cEnemyPtrV = _cEnemyPtrV; }

	void setPetsClass(vector<class PetsClass*>* _cPetsPtrV) { cPetsPtrV = _cPetsPtrV; }

	void setTreasureBox(vector<class treasureBox*>* _cTreasureBoxPtrV) { cTreasureBoxPtrV = _cTreasureBoxPtrV; }

	void setSavePoint(class savePoint* _cSavePointPtr) { cSavePointPtr = _cSavePointPtr; }

	//�÷��̾ ���ʹ̸� ����
	void playerStepEnemy();
	//�÷��̾ ���ʹ̶� �ε���
	void playerCrashedEnemy();

	//�÷��̾ ���� �߰�
	void playerFindPets();
	//�÷��̾ ���̺� ����Ʈ�� ����
	void playerSavePoint();
	//�÷��̾ �������ڸ� �߰�
	void playerFindTreasureBox();

	void playerGetJewel();
};
