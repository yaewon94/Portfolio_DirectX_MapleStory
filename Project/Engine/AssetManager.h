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

public:
	template<typename T> requires std::derived_from<T, Asset>
	T* const AddAsset(const string& Key, const string& relativePath)
	{
		auto type_iter = m_assetMap.find(T::Type);
		
		if (type_iter == m_assetMap.end())
		{
			unordered_map<string, Asset*> map;
			m_assetMap.insert(make_pair(T::Type, map));
			type_iter = m_assetMap.find(T::Type);
			type_iter->second.insert(make_pair(Key, new T(Key, relativePath)));
			return (T*)(type_iter->second.find(Key)->second);
		}
		else
		{
			unordered_map<string, Asset*>::const_iterator iter = type_iter->second.find(Key);

			if (iter != type_iter->second.end())
			{
				MessageBox(nullptr, L"해당 KEY를 가진 에셋이 이미 존재합니다", L"에셋 추가 실패", MB_OK);
				return (T*)(iter->second);
			}
			else
			{
				type_iter->second.insert(make_pair(Key, new T(Key, relativePath)));
				return (T*)(type_iter->second.find(Key)->second);
			}
		}
	}

	template<typename T> requires std::derived_from<T, Asset>
	T* const FindAsset(const string& Key, const string& relativePath = "")
	{
		unordered_map<ASSET_TYPE, unordered_map<string, Asset*>>::const_iterator type_iter = m_assetMap.find(T::Type);
		if (type_iter == m_assetMap.end()) return nullptr;
		
		unordered_map<string, Asset*>::const_iterator iter = type_iter->second.find(Key);
		if (iter != type_iter->second.end()) return (T*)(iter->second);
		
		if (relativePath != "") return AddAsset<T>(Key, relativePath);
		else return nullptr;
	}
};