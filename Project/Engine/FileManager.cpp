#include "pch.h"
#include "FileManager.h"
#include <fstream>
using std::ifstream;
using std::ios_base;

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

int FileManager::Read(const string& FullPath, void* data, size_t size, const string& Key)
{
	ifstream stream(FullPath, ios_base::in);
	if (!stream.good())
	{
		string msg = FullPath + " cannot be opened or found";
		MessageBoxA(nullptr, msg.c_str(), "Reading file is failed", MB_OK);
		return E_FAIL;
	}

	// 토큰 분리
	char* c = (char*)data;
	bool isKeyFound = false;
	if (Key == "") isKeyFound = true;
	int offset = 0;
	while (stream.get(*c))
	{
		if (*c == '\n')
		{
			if (*((char*)data + offset) == '\n') // 이전까지 저장한 값이 없는 경우
			{
				*c = 0;
			}
			else // 이전까지 value를 저장한 경우
			{
				*c = 0;
				if (isKeyFound)
				{
					offset += SIZE_BUFFER;
					if (offset >= size) break;
					c = (char*)data + offset;
				}
				else if (!isKeyFound && (char*)data + offset == Key) isKeyFound = true;
			}
		}
		else if (*c == ':' || *c == '{' || *c == '}' || *c == '\t')
		{
			*c = 0;
			c = (char*)data + offset;
		}
		else ++c;
	}

	stream.close();
	return S_OK;
}