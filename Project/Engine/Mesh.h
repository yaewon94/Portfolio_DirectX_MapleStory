#pragma once
#include "Asset.h"

// ���� ����
struct Vertex
{
	Vec3 pos;
	Vec2 uv;	// �ؽ�ó�� 3������ �����ϱ� ���� ��ȯ ������ �Ǵ� 2���� ��ǥ��
	Vec4 color;
};

// �ٰ��� ����
class Mesh final : public Asset
{
	NO_COPY_MOVE(Mesh)
	ASSET_TYPE_DCL(ASSET_TYPE::MESH)

private:
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;

	Vertex* m_vertexSysmem;
	UINT* m_indexSysmem;

	D3D11_BUFFER_DESC m_vertexDesc;
	UINT m_vertexCount;

	D3D11_BUFFER_DESC m_indexDesc;
	UINT m_indexCount;

public:
	Mesh(const string& Key, const string& relativePath);
	~Mesh();

public:
	int Create(Vertex* vertexSysmem, UINT vertexCount, UINT* indexSysmem, UINT indexCount);

public:
	void Render();

private:
	void Binding();
};