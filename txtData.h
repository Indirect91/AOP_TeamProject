#pragma once

class txtData
{
public:
	static txtData& getInstance() //데이터 입출력 싱글톤화. 
	//C++11버전 이후부턴 추후 배울 쓰레딩서 thread safe를 보장하기에 싱글톤을 쓴다면 이 방식을 알아두자 (정적변수로 만들어 참조자를 리턴하고, 생성자 소멸자를 프라이빗에 숨기는 방식)
	{
		static txtData instance; //스태틱 정적변수는 초기화가 처음 한번만 이루어진다는 사실을 이용,이 코드는 처음 불렷을때 한번만 실행됨. 
		return instance; //만약 이미 위 코드가 한번이라도 실행된 적 있다면 존재하는 인스턴스를 참조자로 반환.
	}

private:
	txtData() {} //싱글톤이니 딴사람이 추가로 생성하지 못하게 막아둠
	~txtData() {} //정적변수는 프로그램 종료시 알아서 뒤지니 외부 호출로 인한 꼬임을 막기위해 소멸자도 일단은 숨겨둠

	char* vectorArrayCombine(vector<string> vArray); //외부서 가져다 쓸 이유가 딱히 없는 함수니 프라이빗에 숨겨두었음
	vector<string> charArraySeparation(char charArray[]); //마찬가지 이유로 프라이빗에 위치


	//텍스트 데이터 어짜피 싱글톤이자 전역변수처럼 항시 가져다 쓸 수 있으니, 만약 저장된 Pip 파일을 불러왔다면 그 정보를 여기에 담아두도록 하자
	




	

public:

	//세이브
	void txtSave(const char* fileName, vector<string> vStr);
	
	//로드
	vector<string> txtLoad(const char* fileName);
	
};

