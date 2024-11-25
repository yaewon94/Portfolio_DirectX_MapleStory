#include "pch.h"
#include "Device.h"
#include "Engine.h"

Device::Device() 
    : m_viewport{}
{
}


Device::~Device()
{
}

int Device::Init()
{
    if (m_device != nullptr)
    {
        MessageBoxA(nullptr, "Device was already created", "Initialize Device is failed", MB_OK);
        return E_FAIL;
    }

    // Device 생성
    {
        UINT iFlag = 0;
#ifdef _DEBUG
        iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
        D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

        if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
            , iFlag, nullptr, 0, D3D11_SDK_VERSION
            , m_device.GetAddressOf(), &level, m_context.GetAddressOf())))
        {
            MessageBoxA(nullptr, "D3D11CreateDevice is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }
    }

    // swap chain 생성
    {
        DXGI_SWAP_CHAIN_DESC Desc = {};

        Desc.BufferCount = 1;                               // 백버퍼 개수
        Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Swapchain 백버퍼 텍스쳐의 용도 설정

        Desc.BufferDesc.Width = RESOLUTION.x; // 백버퍼 해상도 Width
        Desc.BufferDesc.Height = RESOLUTION.y; // 백버퍼 해상도 Height
        Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 정규화된 64비트 RGBA 색상 사용

        Desc.BufferDesc.RefreshRate.Denominator = 1; // 화면 갱신 속도, 분모
        Desc.BufferDesc.RefreshRate.Numerator = 60;  // 화면 갱신 속도, 분자

        Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

        Desc.OutputWindow = Engine::GetInstance()->GetMainWnd(); // 백버퍼에 그려진 이미지를 출력시킬 윈도우
        Desc.Windowed = true; // 창모드(true), 전체화면 모드(false)

        Desc.SampleDesc.Count = 1;
        Desc.SampleDesc.Quality = 0;

        Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 이전에 그려진 이미지를 저장하지 않음
        Desc.Flags = 0;

        ComPtr<IDXGIDevice> IDXGIDevice = nullptr;
        ComPtr<IDXGIAdapter> pAdapter = nullptr;
        ComPtr<IDXGIFactory> pFactory = nullptr;

        // 128 비트
        // GUID (Global Unique ID)
        m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)IDXGIDevice.GetAddressOf());
        IDXGIDevice->GetAdapter(pAdapter.GetAddressOf());
        pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

        if (FAILED(pFactory->CreateSwapChain(m_device.Get(), &Desc, m_swapChain.GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateSwapChain is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }
    }

    // Render Target, Depth Stencil 생성
    {
        // RenderTarget 텍스처 : SwapChain 이 생성될때 만들어진 ID3D11Texture2D 객체를 가리킨다.
        m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_rtTex.GetAddressOf());

        // RenderTargetView 생성
        if (FAILED(m_device->CreateRenderTargetView(m_rtTex.Get(), nullptr, m_rtView.GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateRenderTargetView is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // Depth Stencil 텍스처
        D3D11_TEXTURE2D_DESC Desc = {};

        Desc.Width = RESOLUTION.x;
        Desc.Height = RESOLUTION.y;

        Desc.ArraySize = 1;
        Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

        Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 텍스처 용도

        // CPU 에서 생성 이후에 접근이 가능한지 옵션 (Usage, CPUAccessFlags는 같이 쓰임)
        Desc.Usage = D3D11_USAGE_DEFAULT;
        Desc.CPUAccessFlags = 0;
        // => 접근 불가

        Desc.MipLevels = 1; // 밉맵 개수 1 (원본만 존재)

        Desc.MiscFlags = 0;
        Desc.SampleDesc.Count = 1;
        Desc.SampleDesc.Quality = 0;

        if (FAILED(m_device->CreateTexture2D(&Desc, nullptr, m_dsTex.GetAddressOf())))
        {
            MessageBoxA(nullptr, "Create Depth/Stencil Texture is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // DepthStencilView 생성
        if (FAILED(m_device->CreateDepthStencilView(m_dsTex.Get(), nullptr, m_dsView.GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthsStencilView is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }
    }

    // Rasterizer State 생성
    {
        // CULL BACK (뒷면 삼각형 제거)
        m_rs.at((size_t)RASTERIZER_TYPE::CULL_BACK) = nullptr;
        
        // CULL FRONT (앞면 삼각형 제거)
        D3D11_RASTERIZER_DESC Desc = {};
        Desc.CullMode = D3D11_CULL_FRONT;
        Desc.FillMode = D3D11_FILL_SOLID;
        if (FAILED(DEVICE->CreateRasterizerState(&Desc, m_rs.at((size_t)RASTERIZER_TYPE::CULL_FRONT).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateRasterizerState(CULL_FRONT) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // CULL NONE
        Desc.CullMode = D3D11_CULL_NONE;
        Desc.FillMode = D3D11_FILL_SOLID;
        if (FAILED(DEVICE->CreateRasterizerState(&Desc, m_rs.at((size_t)RASTERIZER_TYPE::CULL_NONE).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateRasterizerState(CULL_NONE) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // WIRE FRAME
        Desc.CullMode = D3D11_CULL_NONE;
        Desc.FillMode = D3D11_FILL_WIREFRAME;
        if (FAILED(DEVICE->CreateRasterizerState(&Desc, m_rs.at((size_t)RASTERIZER_TYPE::WIREFRAME).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateRasterizerState(WIRE FRAME) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }
    }

    // Sampler State 생성
    {
        D3D11_SAMPLER_DESC Desc = {};
        ComPtr<ID3D11SamplerState> sampler = m_sampler.at((size_t)SAMPLER_TYPE::AF);

        // 이방성 필터링 샘플러
        Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        Desc.Filter = D3D11_FILTER_ANISOTROPIC;
        if (FAILED(DEVICE->CreateSamplerState(&Desc, sampler.GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateSamplerState(AF) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        CONTEXT->VSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->HSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->DSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->GSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->PSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->CSSetSamplers(0, 1, sampler.GetAddressOf());

        // MIN_MAG_POINT 필터
        sampler = m_sampler.at((size_t)SAMPLER_TYPE::MIN_MAG_POINT);
        Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        Desc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
        if (FAILED(DEVICE->CreateSamplerState(&Desc, sampler.GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateSamplerState(MIN_MAG_POINT) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        CONTEXT->VSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->HSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->DSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->GSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->PSSetSamplers(0, 1, sampler.GetAddressOf());
        CONTEXT->CSSetSamplers(0, 1, sampler.GetAddressOf());
    }

    // Blend State 생성
    {
        m_bs.at((size_t)BLEND_TYPE::DEFAULT) = nullptr;

        D3D11_BLEND_DESC Desc = {};

        Desc.AlphaToCoverageEnable = false;
        Desc.IndependentBlendEnable = false;
        Desc.RenderTarget[0].BlendEnable = true;
        Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;       // 색상끼리 더하기
        Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;    // Source : PixelShader return 값에 곱할 계수
        Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;// Destination : 색상이 출력될 렌더타겟

        Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
        Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

        Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        if (FAILED(DEVICE->CreateBlendState(&Desc, m_bs.at((size_t)BLEND_TYPE::ALPHABLEND).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateBlendState(ALPHA BLEND) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }
    }

    // Depth Stencil State 생성
    {
        // Less
        m_ds.at((size_t)DEPTH_STENCIL_TYPE::LESS) = nullptr;

        // LessEqual
        D3D11_DEPTH_STENCIL_DESC Desc = {};
        Desc.StencilEnable = false;
        Desc.DepthEnable = true;                            // 깊이판정 진행
        Desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;       // 작거나 같은경우 통과
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // 깊이 기록
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::LESS_EQUAL).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(LESS EQUAL) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // Greater
        Desc.StencilEnable = false;
        Desc.DepthEnable = true;                            // 깊이판정 진행
        Desc.DepthFunc = D3D11_COMPARISON_GREATER;          // 깊이가 큰 경우 통과
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // 깊이 기록
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::GREATER).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(GREATER) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // NoTest
        Desc.StencilEnable = false;
        Desc.DepthEnable = false;                           // 깊이판정 수행하지 않음
        Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;           // 항상 통과
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // 깊이 기록
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::NO_TEST).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(NO TEST) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // NoWrite
        Desc.StencilEnable = false;
        Desc.DepthEnable = true;                            // 깊이판정 진행
        Desc.DepthFunc = D3D11_COMPARISON_LESS;             // 작은경우 통과
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;  // 깊이 기록하지 않음
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::NO_WRITE).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(NO WRITE) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // NoTest NoWrite
        Desc.StencilEnable = false;
        Desc.DepthEnable = false;                           // 깊이판정 X
        Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;           // 항상 통과
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;  // 깊이 기록하지 않음
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::NO_TEST_NO_WRITE).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(NO TEST NO WRITE) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }
    }

    // viewport 설정
    {
        m_viewport.TopLeftX = 0;
        m_viewport.TopLeftY = 0;

        m_viewport.Width = RESOLUTION.x;
        m_viewport.Height = RESOLUTION.y;

        m_viewport.MinDepth = 0.f;
        m_viewport.MaxDepth = 1.f;
    }

	return S_OK;
}

void Device::Present()
{
    CONTEXT->RSSetViewports(1, &m_viewport);

    CONTEXT->ClearRenderTargetView(m_rtView.Get(), Vec4(0.f, 0.f, 0.f, 1.f));
    CONTEXT->ClearDepthStencilView(m_dsView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

    CONTEXT->OMSetRenderTargets(1, m_rtView.GetAddressOf(), m_dsView.Get());

    m_swapChain->Present(0, 0);
}