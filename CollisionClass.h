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

	class EnemyManagerClass* cEnemyMPtr;
	vector <class PetsClass*>* cPetsPtrV;
	vector <class treasureBox*>* cTreasureBoxPtrV;
	class savePoint* cSavePointPtr;

	//vector <class bullet*>* cEBulletV;

	RECT cEmpty = { 0 };

	//get �÷��̾� ������
	//get ���ʹ� ����ִ� ����
	//get Ÿ�� ����ִ� ����


public: //����ͼ��Ͱ��� ���� �ϴ���� ���� �ۺ��� �Լ� ����� ��!

	void setPlayer(class PlayerClass* _cplayerPtr) { cPlayerPtr = _cplayerPtr; }

	void setFieldManagerClass(class FieldManagerClass* _cFieldPtrV) { cFieldPtr = _cFieldPtrV; }

	void setEnemyManagerClass(class EnemyManagerClass* _cEnemyPtr) { cEnemyMPtr = _cEnemyPtr; }

	void setPetsClass(vector<class PetsClass*>* _cPetsPtrV) { cPetsPtrV = _cPetsPtrV; }

	void setTreasureBox(vector<class treasureBox*>* _cTreasureBoxPtrV) { cTreasureBoxPtrV = _cTreasureBoxPtrV; }

	void setSavePoint(class savePoint* _cSavePointPtr) { cSavePointPtr = _cSavePointPtr; }

	//void setCEBullet(vector<class bullet*>* _cEBulletV) { cEBulletV = _cEBulletV; }

	//�÷��̾ ���ʹ̸� ����
	void playerStepEnemy();
	//�÷��̾ ���ʹ̶� �ε���
	void playerCrashedEnemy();

	//�÷��̾ �յ��� �Ѿ˿� ����
	void playerCrashedEBullet();
	//�Ѿ��� ���� ����
	void bulletCrashedWall();

	//�÷��̾ ���� �߰�
	void playerFindPets();
	//�÷��̾ ���̺� ����Ʈ�� ����
	void playerSavePoint();
	//�÷��̾ �������ڸ� �߰�
	void playerFindTreasureBox();
	//�÷��̾ ������ �ֿ�
	void playerGetJewel();
	//������ ���ư�
	void jewelIsBelieveCanFly();


};
