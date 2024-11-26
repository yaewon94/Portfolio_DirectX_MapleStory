#pragma once
#include "Asset.h"
#include "Texture.h"

// 상수버퍼 연동 구조체
struct CB_Material
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matrixArr[2];
	int bTex[TEXTURE_PARAM::TEXTURE_PARAM_COUNT_END]; // TODO : 16바이트 배수로 크기 맞춰야 오류 안남
};

// 재질 에셋
class Material final : public Asset
{
	ASSET_TYPE_DCL(ASSET_TYPE::MATERIAL)

private:
	Material* m_origin;	// 원본 재질을 가리키는 포인터
	class GraphicShader* m_shader;
	map<TEXTURE_PARAM, Texture*> m_texMap;
	CB_Material m_cb;

public:
	Material(const string& Key, const string& relativePath);
	Material(const Material& origin);
	~Material();
	Material& operator=(const Material& other);
	virtual Material* Clone() final { return new Material(*this); }

public:
	void Binding();

public:
	const Material* const GetOrigin() const { return m_origin; }

	GraphicShader* const GetShader() const { return m_shader; }
	void SetShader(GraphicShader* const shader) { m_shader = shader; }

	Texture* const GetTexture(TEXTURE_PARAM type) const;
	void SetTextureParam(TEXTURE_PARAM type, Texture* const texture);

	// 레퍼런스를 통해 수정 가능
	CB_Material& GetConstBuffer() { return m_cb; }
};