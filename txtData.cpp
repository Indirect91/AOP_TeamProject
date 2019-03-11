#include "stdafx.h"
#include "txtData.h"

txtData::txtData()
{
	PipLoad("saveSlot1.txt", "saveSlot2.txt", "saveSlot3.txt");
}

//세이브
void txtData::txtSave(const char * fileName, vector<string> vStr)
{
	//여기서 사용된 방식은 winapi용 방식이며, 범용성을 생각해서 다른 입출력을 원한다면 c++용 fstream도 알아보도록 하자

	HANDLE file; //저장할 파일의 핸들을 임시로 만듦
	DWORD write; //그냥 더블 워드 하나
	char str[128]; //적을 내용이 담길 임시 스트링
	ZeroMemory(str, sizeof(str)); //임시 스트링 메모리 초기화

	strcpy(str, vectorArrayCombine(vStr)); //받아온 백터를 스트링으로 바꾼다. 하는 방법은 아래 벡터어레이컴바인 함수에 적혀있음

	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//(https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-createfilea) 

	//file = CreateFile			크리에이트 파일 완료된걸 바로 file에 담겠다는 뜻
	//fileName					savefile.txt 같이 진짜 파일 이름. 우리는 인자값으로 넘겨받았지?
	//GENERIC_WRITE				권한설정하는곳이얌. or 연산자로 GENERIC_Read등 권한 추가 가능해
	//0							우린 아직 쓰레딩을 하지 않으니, 0을 적자
	//NULL						보안 관련된것이라고 하네. Null 을 적어두자
	//CREATE_ALWAYS				여긴 좀 중요한데, CREATE_NEW를 넣으면 중복파일명 존재시 에러뱉어냄. ALways를 넣으면 파일명 중복되어도 덮어씌워버리고 성공시킴. 다른 옵션들도 있으니 필요하면 찾아봐방!
	//FILE_ATTRIBUTE_NORMAL		파일 속성을 지시하는곳이야 File_attribute_normal에 F12 눌러보면 다른 현 파일이 임시파일인지등 옵션들도 나오고 이름들도 직관적이니 볼만 한데, 보통은 0 입력한다네
	//NULL						보안수준 혹은 방식을 지정하는곳이야. 배우는 단계인 우리는 그냥 Null을 입력하자

	WriteFile(file, str, 128, &write, NULL);
	//file						아까 우리가 만들었던 파일을 여기에 담자. 이 파일에 쓰겠다는 뜻이거든 
	//str						적을 내용이 여기에 들어가. 우린 차포인터, 스트링을 담을거야
	//128						어느 크기만큼 쓸것인가에 대한 인자값이야
	//&write					얼마만큼 기록되었는가에 대한 결과치를 넘겨준 주소에 담는과정인데, 그래서 주소값을 던져넣어준거얌
	//NULL						ip오버랩을 넣는곳. 비동기, 동기, 중첩(overlapped)를 사용할 때 쓰게되는데 우린 NULL을 넣도록 하자
	//
	CloseHandle(file);			//new에는 delete가 있고, fopen엔 fclose가 있는거처럼, winapi도 파일핸들 열었으면 닫아주자
}

//세이브 여러 정보 담을 백터
char * txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128]; //받아온 벡터를 스트링으로 만들어서 반환할 생각이니, 임시 스트링 생성
	ZeroMemory(str, sizeof(str)); //임시 스트링 쓰레기값 안들어가있게 초기화

	for (int i = 0; i < vArray.size(); i++) //벡터에 들어있는 스트링 숫자만큼
	{
		strcat(str, vArray[i].c_str()); 
		//strcat은 스트링 컨캐티네이션으로, 첫째 인자 문자열 뒤에 둘째 인자값 문자열을 더하는 기능.
		//맨 처음 str은 비어있으니, str + 벡터의 첫째 인자 문자열을 더하고 두번째부턴 합해져있는 str + 백터의 둘째 문자열

		if (i + 1 < vArray.size())//백터의 다음 요소가 존재할 경우에만 구분표 포함
		{
			strcat(str, ","); //백터 다음요소가 존재한다면 ","를 방금 합쳐진 문자열 뒤에 붙임
		}
	}

	return str; //다 합쳐진 문자열 반환
}

vector<string> txtData::txtLoad(const char * fileName)
{
	//▼인자값으로 사용될것들, 세이브와 중복되는 부분이므로 설명 스킵
	HANDLE file; 
	DWORD read;
	char str[128];
	ZeroMemory(str, sizeof(str));

	
	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//file = CreateFile			write와 중복설명, 이번에도 열어볼 파일 핸들 선언
	//fileName					write와 중복설명, 인자로 넘겨받은 실제 파일명 save.txt같이
	//GENERIC_READ				쓰기와 달리 이번엔 읽을것이니 READ를 넣자
	//0							write와 중복설명, 쓰레딩 0
	//NULL						write와 중복설명, 보안관련 NULL
	//OPEN_EXISTING				OPEN_ALWAYS를 고르면 기존파일 존재할 시 그거 열고, 없으면 새거 생성. OPEN_EXISTING을 골랐고, 오픈하려는 파일이 존재하지 않으면 에러뱉음
	//FILE_ATTRIBUTE_NORMAL		write와 중복설명, 기본값
	//NULL						write와 중복설명, NULL

	ReadFile(file, str, 128, &read, NULL); 
	//file						만들어진 파일핸들 넣어줌
	//str						str에 담을거임
	//128						128바이트 사이즈만큼.
	//&read						실제 얼마 읽었는지 저장할 변수 주소값 던져주는건데, 우린 이 결과값에 딱히 관심없으므로 에러안뱉게 일단 담아는 둔 다음 버린다
	//NULL						오버랩 NULL

	CloseHandle(file); //연거는 항상 닫자

	return charArraySeparation(str); //방금 담아진 str을 잘라서 백터에 담은걸 리턴한다. 이걸 위해 새로운 함수를 호출하는데 아래서 알아보자
}

//▼문자열을 쪼개서 백터에 담는과정
vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray; //반환할 임시 백터 생성
	const char* separation = ","; //뭘 기준으로 분리되는지 판단할 콤마
	char* token; //하나하나 분리점 기준으로 잘려진 문자열 단위

	token = strtok(charArray, separation); //strtok은 string + tokenize의 약자로, 첫 인자로는 자를려는 원본, 둘째 인자로는 멀 기준으로 자를건지(delimiter)를 넣음
	vArray.push_back(token); //세퍼레이션으로 분리된 토큰을 백터에 담음

	while (NULL != (token = strtok(NULL, separation))) //strtok 함수는 처음 한번 자를때만 원본 넣고, 다음부턴 첫 인자로 NULL을 넣어줌! 안그러면 charArray의 첫 토큰만 무한히 읽어냄
	//추가 설명을 하자면 strtok은 첫 인자가 NULL이 들어있을경우 strtok이 이전에 잘랐던 포인트만큼 이동을 해서 자르기 시작함
	//위 작업을 이제 NULL이 나올때까지 반복할거임. 쉽게말해 끝날때까지.
	{
		vArray.push_back(token); //NULL이 아닐때까지 존재하는 모든 토큰을 담음
	}

	return vArray;
}


//▼핍게임 전용 로드
void txtData::PipLoad(const char * saveSlot1, const char * saveSlot2, const char * saveSlot3)
{
	vector<string> pip1V; //데이터 저장할 임시 벡터 선언. 중괄호와 같이 사라짐 어짜피
	vector<string> pip2V;
	vector<string> pip3V;

	pip1V = txtLoad(saveSlot1); //선언된 벡터에 세이브 슬롯별로 다음
	pip2V = txtLoad(saveSlot2);
	pip3V = txtLoad(saveSlot3);

	saveData1.pipMaxHP = atoi(pip1V[0].c_str()); //담겨진 벡터에 있는 요소 하나씩 꺼내서 여기 변수들에게 줌
	saveData1.pipRescued = atoi(pip1V[1].c_str());
	saveData1.pipMoney = atoi(pip1V[2].c_str());
	saveData1.pipCinematic = atoi(pip1V[3].c_str());
	saveData1.isFindSealS1 = atoi(pip1V[4].c_str());
	saveData1.isFindBatS1 = atoi(pip1V[5].c_str());
	saveData1.isFindSharkS1 = atoi(pip1V[6].c_str());
	saveData1.isFindSealB = atoi(pip1V[7].c_str());
	saveData1.isFindBatB = atoi(pip1V[8].c_str());
	saveData1.isFindSharkB = atoi(pip1V[9].c_str());

	saveData2.pipMaxHP	= atoi(pip2V[0].c_str()); //담겨진 벡터에 있는 요소 하나씩 꺼내서 여기 변수들에게 줌
	saveData2.pipRescued = atoi(pip2V[1].c_str());
	saveData2.pipMoney = atoi(pip2V[2].c_str());
	saveData2.pipCinematic = atoi(pip2V[3].c_str());
	saveData2.isFindSealS1 = atoi(pip2V[4].c_str());
	saveData2.isFindBatS1 = atoi(pip2V[5].c_str());
	saveData2.isFindSharkS1 = atoi(pip2V[6].c_str());
	saveData2.isFindSealB = atoi(pip2V[7].c_str());
	saveData2.isFindBatB = atoi(pip2V[8].c_str());
	saveData2.isFindSharkB = atoi(pip2V[9].c_str());

	saveData3.pipMaxHP = atoi(pip3V[0].c_str()); //담겨진 벡터에 있는 요소 하나씩 꺼내서 여기 변수들에게 줌
	saveData3.pipRescued = atoi(pip3V[1].c_str());
	saveData3.pipMoney = atoi(pip3V[2].c_str());
	saveData3.pipCinematic = atoi(pip3V[3].c_str());
	saveData3.isFindSealS1 = atoi(pip3V[4].c_str());
	saveData3.isFindBatS1 = atoi(pip3V[5].c_str());
	saveData3.isFindSharkS1 = atoi(pip3V[6].c_str());
	saveData3.isFindSealB = atoi(pip3V[7].c_str());
	saveData3.isFindBatB = atoi(pip3V[8].c_str());
	saveData3.isFindSharkB = atoi(pip3V[9].c_str());



	//▼아래같은 방식으로 한줄로 코딩도 가능하나, 코드는 깔끔해져도 텍스트 로드 함수를 무지 많이 호출한다. 참고로 데이터입출력은 꽤나 무겁다.
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
