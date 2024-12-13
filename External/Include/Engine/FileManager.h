#pragma once
#include <fstream>
using std::ifstream;
#include "StringParser.h"

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
	ifstream m_ifstream;

public:
	int Open(const string& FullPath, FILE_MODE mode);
	int ReadJsonValue(const string& Key, void* const data, size_t index = 0, bool isReadFromBegin = false);
	void Close()
	{
		m_ifstream.close();
	}

	// ������ : data�� �޴� ����ü�� char[] Ÿ�Ը� ���� �� �ְ�, �迭 ũ�⵵ SIZE_BUFFER�� �����Ǿ�� ��
	// @ Key != "" : ���� �ϳ��� Entity�� ���� �� ���� ��, Key���� ��ġ�ϴ� �κи� ������ ����
	//int Read(const string& FullPath, void* data, size_t size, const string& Key = "");
};