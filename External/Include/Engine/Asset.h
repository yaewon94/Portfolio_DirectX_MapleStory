#pragma once
#include "Entity.h"

// 에셋 타입
enum class ASSET_TYPE : byte
{
    MESH, MATERIAL, GRAPHIC_SHADER
};

#define ASSET_TYPE_DCL(type) public:\
							    static constexpr ASSET_TYPE Type = type;\
								inline virtual ASSET_TYPE GetType() final { return Type; }

// 텍스처, 애니메이션, 사운드 등 리소스
class Asset : public Entity
{
    NO_COPY_MOVE(Asset);
    friend class AssetManager;

private:
    const string m_Key;
    string m_relativePath;

protected:
    Asset(const string& Key, const string& relativePath);
    ~Asset();

public:
    inline virtual ASSET_TYPE GetType() = 0;

    const string& GetKey() const { return m_Key; }
    const string& GetRelativePath() const { return m_relativePath; }
    string GetFullPathA() const;
    wstring GetFullPathW() const;

private:
    virtual Entity* Clone() final { return nullptr; } // delete
};