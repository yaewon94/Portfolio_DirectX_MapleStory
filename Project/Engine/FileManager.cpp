#include "pch.h"
#include "FileManager.h"
using std::ios_base;

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
	m_ifstream.close();
}

int FileManager::Open(const string& FullPath, FILE_MODE mode)
{
	if (mode == FILE_MODE::READ_BINARY || mode == FILE_MODE::READ_TEXT)
	{
		if (m_ifstream.is_open()) m_ifstream.close();

		ios_base::openmode iosMode = ios_base::in;
		if (mode == FILE_MODE::READ_BINARY) iosMode |= ios_base::binary;
		m_ifstream = std::ifstream(FullPath, iosMode);

		if (!m_ifstream.good())
		{
			string msg = FullPath + " cannot be opened or found";
			MessageBoxA(nullptr, msg.c_str(), "Opening file is failed", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

int FileManager::ReadJsonValue(const string& Key, void* const data, bool isReadFromBegin)
{
	if (isReadFromBegin) m_ifstream.seekg(ios_base::beg);
	
	// 토큰 분리
	char* c = (char*)data;
	bool isKeyFound = false;
	while (m_ifstream.get(*c))
	{
		if (*c == '\n')
		{
			if (*((char*)data) == '\n') // 이전까지 저장한 값이 없는 경우
			{
				*c = '\0';
			}
			else // 이전까지 value를 저장한 경우
			{
				*c = '\0';
				if (isKeyFound) return S_OK;
				else c = (char*)data;
			}
		}
		else if (*c == ':')
		{
			*c = '\0';
			if ((char*)data == Key) isKeyFound = true;
			c = (char*)data;
		}
		else if (*c == '\t' || *c == '{' || *c == '}')
		{
			*c = '\0';
			c = (char*)data;
		}
		else ++c;
	}

	string msg = Key + " is not found";
	MessageBoxA(nullptr, msg.c_str(), "Reading Json value is failed", MB_OK);
	return E_FAIL;
}

//int FileManager::Read(const string& FullPath, void* data, size_t size, const string& Key)
//{
//	ifstream stream(FullPath, ios_base::in);
//	if (!stream.good())
//	{
//		string msg = FullPath + " cannot be opened or found";
//		MessageBoxA(nullptr, msg.c_str(), "Reading file is failed", MB_OK);
//		return E_FAIL;
//	}
//
//	// 토큰 분리
//	char* c = (char*)data;
//	bool isKeyFound = false;
//	if (Key == "") isKeyFound = true;
//	int offset = 0;
//	while (stream.get(*c))
//	{
//		if (*c == '\n')
//		{
//			if (*((char*)data + offset) == '\n') // 이전까지 저장한 값이 없는 경우
//			{
//				*c = 0;
//			}
//			else // 이전까지 value를 저장한 경우
//			{
//				*c = 0;
//				if (isKeyFound)
//				{
//					offset += SIZE_BUFFER;
//					if (offset >= size) break;
//					c = (char*)data + offset;
//				}
//				else if (!isKeyFound && (char*)data + offset == Key) isKeyFound = true;
//			}
//		}
//		else if (*c == ':' || *c == '{' || *c == '}' || *c == '\t')
//		{
//			*c = 0;
//			c = (char*)data + offset;
//		}
//		else ++c;
//	}
//
//	stream.close();
//	return S_OK;
//}