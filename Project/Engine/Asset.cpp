#include "pch.h"
#include "Asset.h"

Asset::Asset(const string& Key, const string& relativePath) 
	: m_Key(Key), m_relativePath(relativePath)
{
}

Asset::~Asset()
{
}