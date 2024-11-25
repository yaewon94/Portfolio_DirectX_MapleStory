#pragma once
#include "Asset.h"

// ���� ���� Ŭ����
class AssetManager final : public Singleton<AssetManager>
{
	SINGLETON(AssetManager);

private:
	unordered_map<ASSET_TYPE, unordered_map<string, Asset*>> m_assetMap;

public:
	int Init();
};