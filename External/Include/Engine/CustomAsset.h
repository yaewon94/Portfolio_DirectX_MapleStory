#pragma once
#include "Asset.h"

// 커스터마이징 타입 에셋
// TODO : 추상클래스로 만들기
class CustomAsset : public Asset
{
	NO_COPY_MOVE(CustomAsset);
	ASSET_TYPE_DCL(ASSET_TYPE::CUSTOM)

public:
	CustomAsset(const string& Key, const string& relativePath);
	~CustomAsset();
};