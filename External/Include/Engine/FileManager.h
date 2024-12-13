#pragma once
#include <fstream>
using std::ifstream;
#include "StringParser.h"

#define SIZE_READ_BUFFER 256

// ���� ���
enum class FILE_MODE
{
	READ_BINARY, READ_TEXT
};

// ���� ����, �б�/���� ��� Ŭ����
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

	// ������ : data�� �޴� ����ü�� char[] Ÿ�Ը� ���� �� �ְ�, �迭 ũ�⵵ SIZE_BUFFER�� �����Ǿ�� ��
	// @ Key != "" : ���� �ϳ��� Entity�� ���� �� ���� ��, Key���� ��ġ�ϴ� �κи� ������ ����
	//int Read(const string& FullPath, void* data, size_t size, const string& Key = "");
};