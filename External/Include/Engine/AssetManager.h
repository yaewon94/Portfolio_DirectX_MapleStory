#pragma once
#include "Asset.h"

// 에셋 관리 클래스
class AssetManager final : public Singleton<AssetManager>
{
	SINGLETON(AssetManager);

private:
	unordered_map<ASSET_TYPE, unordered_map<string, Asset*>> m_assetMap;

public:
	int Init();
};