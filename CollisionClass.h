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

	class UIClass* cUIPtr;

	class EnemyManagerClass* cEnemyMPtr;

	int wherePet;
	int whichPet;
	vector <class PetsClass*>* cPetsPtrV;
	vector <class treasureBox*>* cTreasureBoxPtrV;

	class savePoint* cSavePointPtr;
	class clearPoint* cClearPointPtr;
	//vector <class bullet*>* cEBulletV;

	RECT cEmpty = { 0 };

	//get �÷��̾� ������
	//get ���ʹ� ����ִ� ����
	//get Ÿ�� ����ִ� ����


public: //����ͼ��Ͱ��� ���� �ϴ���� ���� �ۺ��� �Լ� ����� ��!


	void setPlayer(class PlayerClass* _cplayerPtr) { cPlayerPtr = _cplayerPtr; }

	void setFieldManagerClass(class FieldManagerClass* _cFieldPtrV) { cFieldPtr = _cFieldPtrV; }

	void setUIClass(class UIClass* _cUIPtr) { cUIPtr = _cUIPtr; }

	void setEnemyManagerClass(class EnemyManagerClass* _cEnemyPtr) { cEnemyMPtr = _cEnemyPtr; }

	void setPetsClass(vector<class PetsClass*>* _cPetsPtrV) { cPetsPtrV = _cPetsPtrV; }

	void setTreasureBox(vector<class treasureBox*>* _cTreasureBoxPtrV) { cTreasureBoxPtrV = _cTreasureBoxPtrV; }

	void setSavePoint(class savePoint* _cSavePointPtr) { cSavePointPtr = _cSavePointPtr; }

	void setClearPoint(class clearPoint* _cClearPointPtr) { cClearPointPtr = _cClearPointPtr; }

	//void setCEBullet(vector<class bullet*>* _cEBulletV) { cEBulletV = _cEBulletV; }

	//�÷��̾ ���ʹ̸� ����
	void playerStepEnemy();
	//�÷��̾ ���ʹ̶� �ε���
	void playerCrashedEnemy();
	//�÷��̾ �ֳʹ̸� ����
	void playerAttackEnemy();
	//�÷��̾ ���ÿ� ��
	void playerDamegeThorn();
	//�÷��̾ �μ����� Ÿ�� �ѽ�
	void playerChangeTile();
	//������ Ÿ�� �浹
	void playerCollisionHideTile();
	//�÷��̾ �����Ҷ� ����Ʈ�� �ֳʹ� ���̱�
	void playerChangeEnemyCrash();
	//�÷��̾ �յ��� �Ѿ˿� ����
	void playerCrashedEBullet();
	//�Ѿ��� ���� ����
	void bulletCrashedWall();

	//�÷��̾ ���� �߰�
	void playerFindPets(int wherePet);
	//�÷��̾ ���̺� ����Ʈ�� ����
	void playerSavePoint();
	//�÷��̾ Ŭ���� ����Ʈ�� ����
	void playerClearPoint();
	//�÷��̾ �������ڸ� �߰�
	void playerFindTreasureBox();
	//�÷��̾ ������ �ֿ�
	void playerGetJewel();


};
