#pragma once
#include "Asset.h"

// Texture param (value : register number)
enum TEXTURE_PARAM : byte
{
	TEX_0, FLIPBOOK, TEXTURE_PARAM_COUNT_END
};

// 텍스처 에셋
class Texture final : public Asset
{
	NO_COPY_MOVE(Texture)
	ASSET_TYPE_DCL(ASSET_TYPE::TEXTURE)

private:
	ScratchImage m_img;						// 이미지파일 로딩, 저장 기능
	ComPtr<ID3D11Texture2D> m_tex2D;		// (ScratchImage)SysMem -> GPUMem

	ComPtr<ID3D11RenderTargetView> m_rtView;
	ComPtr<ID3D11DepthStencilView> m_dsView;
	ComPtr<ID3D11ShaderResourceView> m_srView;

	D3D11_TEXTURE2D_DESC m_desc;

	int m_srRegisterNum;	// shader resource view register number

public:
	Texture(const string& Key, const string& relativePath);
	~Texture();

public:
	virtual int Load() final;

public:
	void Binding_GS(TEXTURE_PARAM registerNum);
	void Clear_GS();

public:
	ComPtr<ID3D11Texture2D> GetTexture2D() const { return m_tex2D; }

	UINT GetWidth() const { return m_desc.Width; }
	UINT GetHeight() const { return m_desc.Height; }

	ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const { return m_rtView; }
	ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const { return m_dsView; }
	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const { return m_srView; }
};