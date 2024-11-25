#pragma once
#include "Entity.h"

// ���� Ÿ��
enum class ASSET_TYPE : byte
{
};

#define ASSET_TYPE_DCL(type) public:\
							    static constexpr ASSET_TYPE Type = type;\
								inline virtual ASSET_TYPE GetType() final { return Type; }

// �ؽ�ó, �ִϸ��̼�, ���� �� ���ҽ�
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

private:
    virtual Entity* Clone() final { return nullptr; } // delete
};