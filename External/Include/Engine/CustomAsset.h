#pragma once
#include "Asset.h"

// Ŀ���͸���¡ ����
// TODO : �߻�Ŭ������ �����
class CustomAsset : public Asset
{
	NO_COPY_MOVE(CustomAsset);
	ASSET_TYPE_DCL(ASSET_TYPE::CUSTOM)

protected:
	CustomAsset(const string& Key, const string& relativePath);
	~CustomAsset();
};