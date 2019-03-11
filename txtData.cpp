#include "stdafx.h"
#include "txtData.h"

txtData::txtData()
{
	PipLoad("saveSlot1.txt", "saveSlot2.txt", "saveSlot3.txt");
}

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

	
	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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


//���̰��� ���� �ε�
void txtData::PipLoad(const char * saveSlot1, const char * saveSlot2, const char * saveSlot3)
{
	vector<string> pip1V; //������ ������ �ӽ� ���� ����. �߰�ȣ�� ���� ����� ��¥��
	vector<string> pip2V;
	vector<string> pip3V;

	pip1V = txtLoad(saveSlot1); //����� ���Ϳ� ���̺� ���Ժ��� ����
	pip2V = txtLoad(saveSlot2);
	pip3V = txtLoad(saveSlot3);

	saveData1.pipMaxHP = atoi(pip1V[0].c_str()); //����� ���Ϳ� �ִ� ��� �ϳ��� ������ ���� �����鿡�� ��
	saveData1.pipRescued = atoi(pip1V[1].c_str());
	saveData1.pipMoney = atoi(pip1V[2].c_str());
	saveData1.pipCinematic = atoi(pip1V[3].c_str());
	saveData1.isFindSealS1 = atoi(pip1V[4].c_str());
	saveData1.isFindBatS1 = atoi(pip1V[5].c_str());
	saveData1.isFindSharkS1 = atoi(pip1V[6].c_str());
	saveData1.isFindSealB = atoi(pip1V[7].c_str());
	saveData1.isFindBatB = atoi(pip1V[8].c_str());
	saveData1.isFindSharkB = atoi(pip1V[9].c_str());

	saveData2.pipMaxHP	= atoi(pip2V[0].c_str()); //����� ���Ϳ� �ִ� ��� �ϳ��� ������ ���� �����鿡�� ��
	saveData2.pipRescued = atoi(pip2V[1].c_str());
	saveData2.pipMoney = atoi(pip2V[2].c_str());
	saveData2.pipCinematic = atoi(pip2V[3].c_str());
	saveData2.isFindSealS1 = atoi(pip2V[4].c_str());
	saveData2.isFindBatS1 = atoi(pip2V[5].c_str());
	saveData2.isFindSharkS1 = atoi(pip2V[6].c_str());
	saveData2.isFindSealB = atoi(pip2V[7].c_str());
	saveData2.isFindBatB = atoi(pip2V[8].c_str());
	saveData2.isFindSharkB = atoi(pip2V[9].c_str());

	saveData3.pipMaxHP = atoi(pip3V[0].c_str()); //����� ���Ϳ� �ִ� ��� �ϳ��� ������ ���� �����鿡�� ��
	saveData3.pipRescued = atoi(pip3V[1].c_str());
	saveData3.pipMoney = atoi(pip3V[2].c_str());
	saveData3.pipCinematic = atoi(pip3V[3].c_str());
	saveData3.isFindSealS1 = atoi(pip3V[4].c_str());
	saveData3.isFindBatS1 = atoi(pip3V[5].c_str());
	saveData3.isFindSharkS1 = atoi(pip3V[6].c_str());
	saveData3.isFindSealB = atoi(pip3V[7].c_str());
	saveData3.isFindBatB = atoi(pip3V[8].c_str());
	saveData3.isFindSharkB = atoi(pip3V[9].c_str());



	//��Ʒ����� ������� ���ٷ� �ڵ��� �����ϳ�, �ڵ�� ��������� �ؽ�Ʈ �ε� �Լ��� ���� ���� ȣ���Ѵ�. ����� ������������� �ϳ� ���̴�.
	//pip3MaxHP = atoi(txtLoad(saveSlot3)[0].c_str());
	//pip3Saved = atoi(txtLoad(saveSlot3)[1].c_str());
	//pip3Money = atoi(txtLoad(saveSlot3)[2].c_str());


	//char temp[128];
	//vector<string> vStr;
	//vStr.push_back(itoa(_rocket->getX(), temp, 10));
	//vStr.push_back(itoa(_rocket->getY(), temp, 10));
	//vStr.push_back(itoa(_currentHp, temp, 10));
	
	//
	//TXTDATA->txtSave("save.txt", vStr);

}

void txtData::setWhichSavefile(const char * selectedSaveFile)
{
	whichFileLoaded = selectedSaveFile;
	if(whichFileLoaded == "saveSlot1.txt")
	{
		CurrentPipData = &saveData1;
	}
	else if (whichFileLoaded == "saveSlot2.txt")
	{ 
		CurrentPipData = &saveData2;
	}
	else if (whichFileLoaded == "saveSlot3.txt")
	{
		CurrentPipData = &saveData3;
	}
	
}
