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

	// ���� ����
	m_vertexCount = vertexCount;
	m_vertexSysmem = new Vertex[m_vertexCount];
	memcpy(m_vertexSysmem, vertexSysmem, sizeof(Vertex) * m_vertexCount);

	// ���� �����͸� �ý��� �޸� => GPU�� �̵�
	m_vertexDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
	m_vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vertexDesc.CPUAccessFlags = 0;
	m_vertexDesc.Usage = D3D11_USAGE_DEFAULT;

	// ������ų ������ �ʱⵥ���� ���޿�
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = m_vertexSysmem;

	// ���ؽ� �뵵�� ID3D11Buffer ��ü ����
	if (FAILED(DEVICE->CreateBuffer(&m_vertexDesc, &tSub, m_vertexBuffer.GetAddressOf())))
	{
		MessageBoxA(nullptr, "Create Vertex Buffer is failed", "Mesh Create is failed", MB_OK);
		return E_FAIL;
	}

	// �ε��� ����
	m_indexCount = indexCount;
	m_indexSysmem = new UINT[m_indexCount];
	memcpy(m_indexSysmem, indexSysmem, sizeof(UINT) * m_indexCount);

	m_indexDesc.ByteWidth = sizeof(UINT) * m_indexCount;
	m_indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_indexDesc.CPUAccessFlags = 0;
	m_indexDesc.Usage = D3D11_USAGE_DEFAULT;

	// ������ų ������ �ʱⵥ���� ���޿�	
	tSub.pSysMem = m_indexSysmem;

	// �ε��� �뵵�� ID3D11Buffer ��ü ����
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
	// �������� ���� ���� ����
	UINT Stride = sizeof(Vertex);
	UINT Offset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &Stride, &Offset);
	CONTEXT->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}