#include "pch.h"
#include "Asset.h"
#include "PathManager.h"

Asset::Asset(const string& Key, const string& relativePath) 
	: m_Key(Key), m_relativePath(relativePath)
{
}

Asset::~Asset()
{
}

string Asset::GetFullPathA() const
{
	return PathManager::GetInstance()->GetContentPath() + m_relativePath;
}

wstring Asset::GetFullPathW() const
{
	string fullPath = GetFullPathA();
	wstring fullPath_w;
	fullPath_w.assign(fullPath.begin(), fullPath.end());
	return fullPath_w;
}