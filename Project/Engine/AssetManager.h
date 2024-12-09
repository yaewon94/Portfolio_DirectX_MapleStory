#pragma once
#include "Asset.h"

// 에셋 관리 클래스
class AssetManager final : public Singleton<AssetManager>
{
	SINGLETON(AssetManager);

private:
	unordered_map<ASSET_TYPE, unordered_map<string, SharedPtr<Asset>>> m_assetMap;

public:
	int Init();

public:
	template<typename T> requires std::derived_from<T, Asset>
	SharedPtr<T> AddAsset(const string& Key, const string& relativePath)
	{
		auto type_iter = m_assetMap.find(T::Type);
		
		if (type_iter == m_assetMap.end())
		{
			SharedPtr<T> asset = SharedPtr<T>(Key, relativePath);
			if (FAILED(asset->Load())) return nullptr;
			unordered_map<string, SharedPtr<Asset>> map;

			m_assetMap.insert(make_pair(T::Type, map));
			type_iter = m_assetMap.find(T::Type);
			type_iter->second.insert(make_pair(Key, asset.ptr_dynamic_cast<Asset>()));
			return asset;
		}
		else
		{
			auto iter = type_iter->second.find(Key);
			if (iter != type_iter->second.end())
			{
				MessageBox(nullptr, L"해당 KEY를 가진 에셋이 이미 존재합니다", L"에셋 추가 실패", MB_OK);
				return iter->second.ptr_dynamic_cast<T>();
			}
			else
			{
				SharedPtr<T> asset = SharedPtr<T>(Key, relativePath);
				if (FAILED(asset->Load())) return nullptr;
				type_iter->second.insert(make_pair(Key, asset.ptr_dynamic_cast<Asset>()));
				return asset;
			}
		}
	}

	template<typename T> requires std::derived_from<T, Asset>
	SharedPtr<T> FindAsset(const string& Key)
	{
		auto type_iter = m_assetMap.find(T::Type);
		if (type_iter == m_assetMap.end()) return nullptr;

		auto iter = type_iter->second.find(Key);
		if (iter != type_iter->second.end()) return (iter->second).ptr_dynamic_cast<T>();
		else return nullptr;
	}

	template<typename T> requires std::derived_from<T, Asset>
	SharedPtr<T> FindOrAddAsset(const string& Key, const string& relativePath)
	{
		auto type_iter = m_assetMap.find(T::Type);
		if (type_iter == m_assetMap.end())
		{
			return AddAsset<T>(Key, relativePath);
		}
		else
		{
			auto iter = type_iter->second.find(Key);
			if (iter != type_iter->second.end()) return (iter->second).ptr_dynamic_cast<T>();
			else return AddAsset<T>(Key, relativePath);
		}
	}
};