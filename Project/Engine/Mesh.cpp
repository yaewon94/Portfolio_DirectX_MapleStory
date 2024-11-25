#include "pch.h"
#include "Mesh.h"
#include "Device.h"

Mesh::Mesh(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
	, m_vertexSysmem(nullptr), m_vertexDesc{}, m_vertexCount(0)
	, m_indexSysmem(nullptr), m_indexDesc{}, m_indexCount(0)
{
}

Mesh::~Mesh()
{
	if (m_vertexSysmem != nullptr)
	{
		delete m_vertexSysmem;
		m_vertexSysmem = nullptr;
	}

	if (m_indexSysmem != nullptr)
	{
		delete m_indexSysmem;
		m_indexSysmem = nullptr;
	}
}

int Mesh::Create(Vertex* vertexSysmem, UINT vertexCount, UINT* indexSysmem, UINT indexCount)
{
#ifdef _DEBUG
	if (vertexSysmem == nullptr || indexSysmem == nullptr) assert(nullptr);
#endif // DEBUG

	if (m_vertexBuffer != nullptr || m_indexBuffer != nullptr)
	{
		MessageBoxA(nullptr, "Buffer is already created", "Mesh Create is failed", MB_OK);
		return E_FAIL;
	}

	// 정점 버퍼
	m_vertexCount = vertexCount;
	m_vertexSysmem = new Vertex[m_vertexCount];
	memcpy(m_vertexSysmem, vertexSysmem, sizeof(Vertex) * m_vertexCount);

	// 정점 데이터를 시스템 메모리 => GPU로 이동
	m_vertexDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
	m_vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vertexDesc.CPUAccessFlags = 0;
	m_vertexDesc.Usage = D3D11_USAGE_DEFAULT;

	// 생성시킬 버퍼의 초기데이터 전달용
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = m_vertexSysmem;

	// 버텍스 용도의 ID3D11Buffer 객체 생성
	if (FAILED(DEVICE->CreateBuffer(&m_vertexDesc, &tSub, m_vertexBuffer.GetAddressOf())))
	{
		MessageBoxA(nullptr, "Create Vertex Buffer is failed", "Mesh Create is failed", MB_OK);
		return E_FAIL;
	}

	// 인덱스 버퍼
	m_indexCount = indexCount;
	m_indexSysmem = new UINT[m_indexCount];
	memcpy(m_indexSysmem, indexSysmem, sizeof(UINT) * m_indexCount);

	m_indexDesc.ByteWidth = sizeof(UINT) * m_indexCount;
	m_indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_indexDesc.CPUAccessFlags = 0;
	m_indexDesc.Usage = D3D11_USAGE_DEFAULT;

	// 생성시킬 버퍼의 초기데이터 전달용	
	tSub.pSysMem = m_indexSysmem;

	// 인덱스 용도의 ID3D11Buffer 객체 생성
	if (FAILED(DEVICE->CreateBuffer(&m_indexDesc, &tSub, m_indexBuffer.GetAddressOf())))
	{
		MessageBoxA(nullptr, "Create Index Buffer is failed", "Mesh Create is failed", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Mesh::Render()
{
	Binding();
	CONTEXT->DrawIndexed(m_indexCount, 0, 0);
}

void Mesh::Binding()
{
	// 렌더링할 정점 정보 전달
	UINT Stride = sizeof(Vertex);
	UINT Offset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &Stride, &Offset);
	CONTEXT->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}