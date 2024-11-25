#pragma once
#include "Entity.h"

enum class CONST_BUFFER_TYPE : byte
{
    TRANSFORM
};

// 상수 버퍼
class ConstBuffer final : public Entity
{
    NO_COPY_MOVE(ConstBuffer);

private:
    ComPtr<ID3D11Buffer> m_buffer;
    D3D11_BUFFER_DESC m_desc;
    const CONST_BUFFER_TYPE m_type;

public:
    ConstBuffer(CONST_BUFFER_TYPE type);
    ~ConstBuffer();

public:
    int Create(UINT size);
    void SetData(void* data);
    void Binding();

private:
    virtual Entity* Clone() final { return nullptr; } // delete
};