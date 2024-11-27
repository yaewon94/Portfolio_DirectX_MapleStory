#pragma once
#include "Asset.h"
#include "Texture.h"
#include "GraphicShader.h"

// ������� ���� ����ü
struct CB_Material
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matrixArr[2];
	int bTex[TEXTURE_PARAM::TEXTURE_PARAM_COUNT_END]; // TODO : 16����Ʈ ����� ũ�� ����� ���� �ȳ�
};

// ���� ����
class Material final : public Asset
{
	NO_COPY_MOVE(Material);
	ASSET_TYPE_DCL(ASSET_TYPE::MATERIAL)

private:
	SharedPtr<Material> m_origin;	// ���� ������ ����Ű�� ������
	SharedPtr<GraphicShader> m_shader;
	map<TEXTURE_PARAM, SharedPtr<Texture>> m_texMap;
	CB_Material m_cb;

public:
	Material(const string& Key, const string& relativePath);
	Material(SharedPtr<Material> origin);
	~Material();

public:
	void Binding();

public:
	SharedPtr<Material> GetOrigin() const { return m_origin; }

	SharedPtr<GraphicShader> GetShader() const { return m_shader; }
	void SetShader(SharedPtr<GraphicShader> shader) { m_shader = shader; }

	SharedPtr<Texture> GetTexture(TEXTURE_PARAM type) const;
	void SetTextureParam(TEXTURE_PARAM type, SharedPtr<Texture> texture);

	// ���۷����� ���� ���� ����
	CB_Material& GetConstBuffer() { return m_cb; }
};