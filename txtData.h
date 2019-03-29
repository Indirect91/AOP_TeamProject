#pragma once

class txtData
{
public:
	static txtData& getInstance() //������ ����� �̱���ȭ. 
	//C++11���� ���ĺ��� ���� ��� �������� thread safe�� �����ϱ⿡ �̱����� ���ٸ� �� ����� �˾Ƶ��� (���������� ����� �����ڸ� �����ϰ�, ������ �Ҹ��ڸ� �����̺��� ����� ���)
	{
		static txtData instance; //����ƽ ���������� �ʱ�ȭ�� ó�� �ѹ��� �̷�����ٴ� ����� �̿�,�� �ڵ�� ó�� �ҷ����� �ѹ��� �����. 
		return instance; //���� �̹� �� �ڵ尡 �ѹ��̶� ����� �� �ִٸ� �����ϴ� �ν��Ͻ��� �����ڷ� ��ȯ.
	}

	struct tagSavedata
	{
		UINT pipMaxHP;		//��ü��
		UINT pipRescued;	//���� ���� ��
		UINT pipMoney;		//���� ��
		BOOL pipCinematic;	//ù���� ����
		BOOL isFindSealS1;	//��������1 ���� ���⿩��
		BOOL isFindBatS1;	//��������1 ���� ���⿩��
		BOOL isFindSharkS1;	//��������1 ��� ���⿩��
		BOOL isFindSealB;	//������������ ���� ���⿩��
		BOOL isFindBatB;	//������������ ���� ���⿩��
		BOOL isFindSharkB;	//������������ ��� ���⿩��
		string firstItem;	//ù° ������
		string secondItem;	//��° ������
		string thirdItem;	//��° ������
	};

	

private:
	txtData(); //�̱����̴� ������� �߰��� �������� ���ϰ� ���Ƶ�
	~txtData() {} //���������� ���α׷� ����� �˾Ƽ� ������ �ܺ� ȣ��� ���� ������ �������� �Ҹ��ڵ� �ϴ��� ���ܵ�

	char* vectorArrayCombine(vector<string> vArray); //�ܺμ� ������ �� ������ ���� ���� �Լ��� �����̺��� ���ܵξ���
	vector<string> charArraySeparation(char charArray[]); //�������� ������ �����̺��� ��ġ




	//���ؽ�Ʈ ������ ��¥�� �̱������� ��������ó�� �׽� ������ �� �� ������, ���� ����� Pip ������ �ҷ��Դٸ� �� ������ ���⿡ ��Ƶε��� ����
	const char* whichFileLoaded; //������Ϸ� �����ߴ���
	tagSavedata saveData1;
	tagSavedata saveData2;
	tagSavedata saveData3;
	tagSavedata * CurrentPipData; 
	float BGMSound;
	float SFXSound;

public:

	//���� ���̺�
	void txtSave(const char* fileName, vector<string> vStr);
	//���� �ε�
	vector<string> txtLoad(const char* fileName);
	


	//���̰��� ����
	void PipLoad(const char* saveSlot1, const char* saveSlot2, const char* saveSlot3);
	tagSavedata  * getCurrentPipData(){ return CurrentPipData; }
	BOOL getPip1Cinematic() { return saveData1.pipCinematic; }
	BOOL getPip2Cinematic() { return saveData2.pipCinematic; }
	BOOL getPip3Cinematic() { return saveData3.pipCinematic; }
	tagSavedata &getData1() { return saveData1; }
	tagSavedata &getData2() { return saveData2; }
	tagSavedata &getData3() { return saveData3; }


	const char* getWhichfile() { return whichFileLoaded; }


	void setWhichSavefile(const char* selectedSaveFile);
	float &refBGMSound() { return BGMSound; }
	float &refSFXSound() { return SFXSound; }
};

