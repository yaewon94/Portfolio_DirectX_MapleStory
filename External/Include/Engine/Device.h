#pragma once
#include "ConstBuffer.h"

enum class RASTERIZER_TYPE : byte
{
    CULL_BACK, CULL_FRONT, CULL_NONE, WIREFRAME, COUNT_END
};

enum class SAMPLER_TYPE : byte
{
    AF, MIN_MAG_POINT, COUNT_END
};

enum class BLEND_TYPE : byte
{
    DEFAULT, ALPHABLEND, COUNT_END
};

enum class DEPTH_STENCIL_TYPE : byte
{
    LESS, LESS_EQUAL, GREATER, NO_TEST, NO_WRITE, NO_TEST_NO_WRITE, COUNT_END
};

// DirectX Device 생성, 사용을 위한 클래스
class Device final : public Singleton<Device>
{
    SINGLETON(Device);

private:
    ComPtr<ID3D11Device> m_device; // GPU 제어, GPU 메모리에 데이터를 생성    
    ComPtr<ID3D11DeviceContext> m_context; // GPU 제어, GPU 동작 명령, Rendering, GPGPU(General Purpose GPU)

    ComPtr<IDXGISwapChain> m_swapChain;    // BackBuffer 관리 및 최종 렌더링 제출

    ComPtr<ID3D11Texture2D>         m_rtTex; // BackBuffer texture
    ComPtr<ID3D11RenderTargetView>  m_rtView; // BackBuffer 중간 전달자

    ComPtr<ID3D11Texture2D>         m_dsTex; // Depth, Stencil texture
    ComPtr<ID3D11DepthStencilView>  m_dsView; // dsTex 의 중간 전달자

    array<ComPtr<ID3D11RasterizerState>, (size_t)RASTERIZER_TYPE::COUNT_END> m_rs;
    array<ComPtr<ID3D11SamplerState>, (size_t)SAMPLER_TYPE::COUNT_END> m_sampler;
    array<ComPtr<ID3D11BlendState>, (size_t)BLEND_TYPE::COUNT_END> m_bs;
    array<ComPtr<ID3D11DepthStencilState>, (size_t)DEPTH_STENCIL_TYPE::COUNT_END> m_ds;

    array<ConstBuffer*, (size_t)CONST_BUFFER_TYPE::COUNT_END> m_constBuffers;

    D3D11_VIEWPORT m_viewport;

public:
    ComPtr<ID3D11Device> GetDevice() const { return m_device; }
    ComPtr<ID3D11DeviceContext> GetContext() const { return m_context; }

    ComPtr<ID3D11RasterizerState> GetRasterizerState(RASTERIZER_TYPE type) const { return m_rs.at((size_t)type); }
    ComPtr<ID3D11BlendState> GetBlendState(BLEND_TYPE type) const { return m_bs.at((size_t)type); }
    ComPtr<ID3D11DepthStencilState> GetDepthStencilState(DEPTH_STENCIL_TYPE type) { return m_ds.at((size_t)type); }

public:
    int Init();
    void Present();
};

#define DEVICE Device::GetInstance()->GetDevice()
#define CONTEXT Device::GetInstance()->GetContext()