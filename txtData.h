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

private:
	txtData() {} //�̱����̴� ������� �߰��� �������� ���ϰ� ���Ƶ�
	~txtData() {} //���������� ���α׷� ����� �˾Ƽ� ������ �ܺ� ȣ��� ���� ������ �������� �Ҹ��ڵ� �ϴ��� ���ܵ�

	char* vectorArrayCombine(vector<string> vArray); //�ܺμ� ������ �� ������ ���� ���� �Լ��� �����̺��� ���ܵξ���
	vector<string> charArraySeparation(char charArray[]); //�������� ������ �����̺��� ��ġ


	//�ؽ�Ʈ ������ ��¥�� �̱������� ��������ó�� �׽� ������ �� �� ������, ���� ����� Pip ������ �ҷ��Դٸ� �� ������ ���⿡ ��Ƶε��� ����
	




	

public:

	//���̺�
	void txtSave(const char* fileName, vector<string> vStr);
	
	//�ε�
	vector<string> txtLoad(const char* fileName);
	
};

