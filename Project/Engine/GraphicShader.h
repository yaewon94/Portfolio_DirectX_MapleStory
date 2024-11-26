#pragma once
#include "Shader.h"
#include "Device.h"

// shader domain (value : ·»´õ¸µ ¼ø¼­)
enum class SHADER_DOMAIN : byte
{
    DOMAIN_OPAQUE, DOMAIN_MASK, DOMAIN_TRANSPARENT, DOMAIN_PARTICLE, DOMAIN_POST_PROCESS
};

// graphic shader
class GraphicShader final : public Shader
{
    NO_COPY_MOVE(GraphicShader)
    ASSET_TYPE_DCL(ASSET_TYPE::GRAPHIC_SHADER)

private:
    ComPtr<ID3DBlob> m_vsBlob; // vertex shader
    ComPtr<ID3DBlob> m_gsBlob; // geometry shader
    ComPtr<ID3DBlob> m_psBlob; // pixel shader

    ComPtr<ID3D11VertexShader> m_vs;
    ComPtr<ID3D11GeometryShader> m_gs;
    ComPtr<ID3D11PixelShader> m_ps;

    ComPtr<ID3D11InputLayout> m_layout;
    D3D11_PRIMITIVE_TOPOLOGY m_topology;

    RASTERIZER_TYPE m_rsType;
    BLEND_TYPE m_bsType;
    DEPTH_STENCIL_TYPE m_dsType;
    SHADER_DOMAIN m_domain;

public:
    GraphicShader(const string& Key, const string& relativePath);
    ~GraphicShader();

public:
    int CreateVertexShader(const string& funcName);
    int CreateGeometryShader(const string& funcName);
    int CreatePixelShader(const string& funcName);

    void Binding();

public:
    D3D11_PRIMITIVE_TOPOLOGY GetTopology() const { return m_topology; }
    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { m_topology = topology; }

    RASTERIZER_TYPE GetRasterizerType() const { return m_rsType; }
    void SetRasterizerType(RASTERIZER_TYPE type)
    {
#ifdef _DEBUG
        if (type == RASTERIZER_TYPE::COUNT_END) assert(nullptr);
#endif // _DEBUG
        m_rsType = type;
    }

    BLEND_TYPE GetBlendType() const { return m_bsType; }
    void SetBlendType(BLEND_TYPE type)
    {
#ifdef _DEBUG
        if (type == BLEND_TYPE::COUNT_END) assert(nullptr);
#endif // _DEBUG
        m_bsType = type;
    }

    DEPTH_STENCIL_TYPE GetDepthStencilType() const { return m_dsType; }
    void SetDepthStencilType(DEPTH_STENCIL_TYPE type)
    {
#ifdef _DEBUG
        if (type == DEPTH_STENCIL_TYPE::COUNT_END) assert(nullptr);
#endif // _DEBUG
        m_dsType = type;
    }

    SHADER_DOMAIN GetShaderDomain() const { return m_domain; }
    void SetShaderDomain(SHADER_DOMAIN domain) { m_domain = domain; }
};