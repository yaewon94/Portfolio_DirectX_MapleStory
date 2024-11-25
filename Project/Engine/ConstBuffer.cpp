#include "pch.h"
#include "ConstBuffer.h"
#include "Device.h"

ConstBuffer::ConstBuffer(CONST_BUFFER_TYPE type) 
	: m_type(type)
	, m_desc{}
{
}

ConstBuffer::~ConstBuffer()
{
}

int ConstBuffer::Create(UINT size)
{
#ifdef _DEBUG
	if (size % 16 != 0) assert(nullptr);
#endif // _DEBUG

	m_desc.ByteWidth = size;
	m_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_desc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&m_desc, nullptr, m_buffer.GetAddressOf())))
	{
		MessageBoxA(nullptr, "CreateBuffer is failed", "Create Const Buffer is failed", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void ConstBuffer::SetData(void* data)
{
	D3D11_MAPPED_SUBRESOURCE tMapSub = {};

	CONTEXT->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);
	memcpy(tMapSub.pData, data, m_desc.ByteWidth);
	CONTEXT->Unmap(m_buffer.Get(), 0);
}

void ConstBuffer::Binding()
{
	UINT startSlot = (UINT)m_type;
	CONTEXT->VSSetConstantBuffers(startSlot, 1, m_buffer.GetAddressOf());
	CONTEXT->HSSetConstantBuffers(startSlot, 1, m_buffer.GetAddressOf());
	CONTEXT->DSSetConstantBuffers(startSlot, 1, m_buffer.GetAddressOf());
	CONTEXT->GSSetConstantBuffers(startSlot, 1, m_buffer.GetAddressOf());
	CONTEXT->PSSetConstantBuffers(startSlot, 1, m_buffer.GetAddressOf());
}