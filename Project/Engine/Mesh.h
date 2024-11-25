#pragma once
#include "Asset.h"

// 정점 정보
struct Vertex
{
	Vec3 pos;
	Vec2 uv;	// 텍스처를 3차원에 매핑하기 위해 변환 기준이 되는 2차원 좌표계
	Vec4 color;
};

// 다각형 에셋
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