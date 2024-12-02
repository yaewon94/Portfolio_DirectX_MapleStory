#pragma once
#include "Entity.h"

enum class CONST_BUFFER_TYPE : byte
{
    TRANSFORM, MATERIAL, FLIPBOOK, COUNT_END
};

// 상수 버퍼
class ConstBuffer final : public Entity
{
    NO_COPY_MOVE(ConstBuffer);
    friend class Device;

private:
    ComPtr<ID3D11Buffer> m_buffer;
    D3D11_BUFFER_DESC m_desc;
    const CONST_BUFFER_TYPE m_type;

private:
    ConstBuffer(CONST_BUFFER_TYPE type);
    ~ConstBuffer();
    int Create(UINT size);

public:
    void SetData(void* data);
    void Binding_GS();

private:
    virtual Entity* Clone() final { return nullptr; } // delete
};