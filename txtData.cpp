#include "stdafx.h"
#include "txtData.h"

//���̺�
void txtData::txtSave(const char * fileName, vector<string> vStr)
{
	//���⼭ ���� ����� winapi�� ����̸�, ���뼺�� �����ؼ� �ٸ� ������� ���Ѵٸ� c++�� fstream�� �˾ƺ����� ����

	HANDLE file; //������ ������ �ڵ��� �ӽ÷� ����
	DWORD write; //�׳� ���� ���� �ϳ�
	char str[128]; //���� ������ ��� �ӽ� ��Ʈ��
	ZeroMemory(str, sizeof(str)); //�ӽ� ��Ʈ�� �޸� �ʱ�ȭ

	strcpy(str, vectorArrayCombine(vStr)); //�޾ƿ� ���͸� ��Ʈ������ �ٲ۴�. �ϴ� ����� �Ʒ� ���;���Ĺ��� �Լ��� ��������

	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//(https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-createfilea) 

	//file = CreateFile			ũ������Ʈ ���� �Ϸ�Ȱ� �ٷ� file�� ��ڴٴ� ��
	//fileName					savefile.txt ���� ��¥ ���� �̸�. �츮�� ���ڰ����� �Ѱܹ޾���?
	//GENERIC_WRITE				���Ѽ����ϴ°��̾�. or �����ڷ� GENERIC_Read�� ���� �߰� ������
	//0							�츰 ���� �������� ���� ������, 0�� ����
	//NULL						���� ���õȰ��̶�� �ϳ�. Null �� �������
	//CREATE_ALWAYS				���� �� �߿��ѵ�, CREATE_NEW�� ������ �ߺ����ϸ� ����� ������. ALways�� ������ ���ϸ� �ߺ��Ǿ ����������� ������Ŵ. �ٸ� �ɼǵ鵵 ������ �ʿ��ϸ� ã�ƺ���!
	//FILE_ATTRIBUTE_NORMAL		���� �Ӽ��� �����ϴ°��̾� File_attribute_normal�� F12 �������� �ٸ� �� ������ �ӽ����������� �ɼǵ鵵 ������ �̸��鵵 �������̴� ���� �ѵ�, ������ 0 �Է��Ѵٳ�
	//NULL						���ȼ��� Ȥ�� ����� �����ϴ°��̾�. ���� �ܰ��� �츮�� �׳� Null�� �Է�����

	WriteFile(file, str, 128, &write, NULL);
	//file						�Ʊ� �츮�� ������� ������ ���⿡ ����. �� ���Ͽ� ���ڴٴ� ���̰ŵ� 
	//str						���� ������ ���⿡ ��. �츰 ��������, ��Ʈ���� �����ž�
	//128						��� ũ�⸸ŭ �����ΰ��� ���� ���ڰ��̾�
	//&write					�󸶸�ŭ ��ϵǾ��°��� ���� ���ġ�� �Ѱ��� �ּҿ� ��°����ε�, �׷��� �ּҰ��� �����־��ذž�
	//NULL						ip�������� �ִ°�. �񵿱�, ����, ��ø(overlapped)�� ����� �� ���ԵǴµ� �츰 NULL�� �ֵ��� ����
	//
	CloseHandle(file);			//new���� delete�� �ְ�, fopen�� fclose�� �ִ°�ó��, winapi�� �����ڵ� �������� �ݾ�����
}

//���̺� ���� ���� ���� ����
char * txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128]; //�޾ƿ� ���͸� ��Ʈ������ ���� ��ȯ�� �����̴�, �ӽ� ��Ʈ�� ����
	ZeroMemory(str, sizeof(str)); //�ӽ� ��Ʈ�� �����Ⱚ �ȵ��ְ� �ʱ�ȭ

	for (int i = 0; i < vArray.size(); i++) //���Ϳ� ����ִ� ��Ʈ�� ���ڸ�ŭ
	{
		strcat(str, vArray[i].c_str()); 
		//strcat�� ��Ʈ�� ��ĳƼ���̼�����, ù° ���� ���ڿ� �ڿ� ��° ���ڰ� ���ڿ��� ���ϴ� ���.
		//�� ó�� str�� ���������, str + ������ ù° ���� ���ڿ��� ���ϰ� �ι�°���� �������ִ� str + ������ ��° ���ڿ�

		if (i + 1 < vArray.size())//������ ���� ��Ұ� ������ ��쿡�� ����ǥ ����
		{
			strcat(str, ","); //���� ������Ұ� �����Ѵٸ� ","�� ��� ������ ���ڿ� �ڿ� ����
		}
	}

	return str; //�� ������ ���ڿ� ��ȯ
}

vector<string> txtData::txtLoad(const char * fileName)
{
	//�����ڰ����� ���ɰ͵�, ���̺�� �ߺ��Ǵ� �κ��̹Ƿ� ���� ��ŵ
	HANDLE file; 
	DWORD read;
	char str[128];
	ZeroMemory(str, sizeof(str));

	
	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//file = CreateFile			write�� �ߺ�����, �̹����� ��� ���� �ڵ� ����
	//fileName					write�� �ߺ�����, ���ڷ� �Ѱܹ��� ���� ���ϸ� save.txt����
	//GENERIC_READ				����� �޸� �̹��� �������̴� READ�� ����
	//0							write�� �ߺ�����, ������ 0
	//NULL						write�� �ߺ�����, ���Ȱ��� NULL
	//OPEN_EXISTING				OPEN_ALWAYS�� ���� �������� ������ �� �װ� ����, ������ ���� ����. OPEN_EXISTING�� �����, �����Ϸ��� ������ �������� ������ ��������
	//FILE_ATTRIBUTE_NORMAL		write�� �ߺ�����, �⺻��
	//NULL						write�� �ߺ�����, NULL

	ReadFile(file, str, 128, &read, NULL); 
	//file						������� �����ڵ� �־���
	//str						str�� ��������
	//128						128����Ʈ �����ŭ.
	//&read						���� �� �о����� ������ ���� �ּҰ� �����ִ°ǵ�, �츰 �� ������� ���� ���ɾ����Ƿ� �����ȹ�� �ϴ� ��ƴ� �� ���� ������
	//NULL						������ NULL

	CloseHandle(file); //���Ŵ� �׻� ����

	return charArraySeparation(str); //��� ����� str�� �߶� ���Ϳ� ������ �����Ѵ�. �̰� ���� ���ο� �Լ��� ȣ���ϴµ� �Ʒ��� �˾ƺ���
}

//�幮�ڿ��� �ɰ��� ���Ϳ� ��°���
vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray; //��ȯ�� �ӽ� ���� ����
	const char* separation = ","; //�� �������� �и��Ǵ��� �Ǵ��� �޸�
	char* token; //�ϳ��ϳ� �и��� �������� �߷��� ���ڿ� ����

	token = strtok(charArray, separation); //strtok�� string + tokenize�� ���ڷ�, ù ���ڷδ� �ڸ����� ����, ��° ���ڷδ� �� �������� �ڸ�����(delimiter)�� ����
	vArray.push_back(token); //���۷��̼����� �и��� ��ū�� ���Ϳ� ����

	while (NULL != (token = strtok(NULL, separation))) //strtok �Լ��� ó�� �ѹ� �ڸ����� ���� �ְ�, �������� ù ���ڷ� NULL�� �־���! �ȱ׷��� charArray�� ù ��ū�� ������ �о
	//�߰� ������ ���ڸ� strtok�� ù ���ڰ� NULL�� ���������� strtok�� ������ �߶��� ����Ʈ��ŭ �̵��� �ؼ� �ڸ��� ������
	//�� �۾��� ���� NULL�� ���ö����� �ݺ��Ұ���. ���Ը��� ����������.
	{
		vArray.push_back(token); //NULL�� �ƴҶ����� �����ϴ� ��� ��ū�� ����
	}

	return vArray;
}
