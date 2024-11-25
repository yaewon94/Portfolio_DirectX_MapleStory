#include "pch.h"
#include "AssetManager.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (auto& assetTypePair : m_assetMap)
	{
		for (auto& assetPair : assetTypePair.second)
		{
			if (assetPair.second != nullptr)
			{
				delete assetPair.second;
				assetPair.second = nullptr;
			}
		}
	}
}

int AssetManager::Init()
{
	return S_OK;
}