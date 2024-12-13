#pragma once
#include <fstream>
using std::ifstream;
#include "StringParser.h"

#define SIZE_READ_BUFFER 256

// 파일 모드
enum class FILE_MODE
{
	READ_BINARY, READ_TEXT
};

// 파일 관리, 읽기/쓰기 담당 클래스
class FileManager final : public Singleton<FileManager>
{
	SINGLETON(FileManager);

private:
	stack<ifstream> m_ifstreamStack;

public:
	int Open(const string& FullPath, FILE_MODE mode);
	int ReadJsonValue(const string& Key, void* const data, size_t index = 0, bool isReadFromBegin = false);
	void Close()
	{
		if (!m_ifstreamStack.empty())
		{
			m_ifstreamStack.top().close();
			m_ifstreamStack.pop();
		}
	}

	// 문제점 : data로 받는 구조체가 char[] 타입만 가질 수 있고, 배열 크기도 SIZE_BUFFER로 고정되어야 함
	// @ Key != "" : 파일 하나에 Entity가 여러 개 있을 때, Key값과 일치하는 부분만 데이터 추출
	//int Read(const string& FullPath, void* data, size_t size, const string& Key = "");
};