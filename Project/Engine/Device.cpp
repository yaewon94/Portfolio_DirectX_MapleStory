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

    // Device ����
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

    // swap chain ����
    {
        DXGI_SWAP_CHAIN_DESC Desc = {};

        Desc.BufferCount = 1;                               // ����� ����
        Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Swapchain ����� �ؽ����� �뵵 ����

        Desc.BufferDesc.Width = RESOLUTION.x; // ����� �ػ� Width
        Desc.BufferDesc.Height = RESOLUTION.y; // ����� �ػ� Height
        Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ����ȭ�� 64��Ʈ RGBA ���� ���

        Desc.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� ���� �ӵ�, �и�
        Desc.BufferDesc.RefreshRate.Numerator = 60;  // ȭ�� ���� �ӵ�, ����

        Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

        Desc.OutputWindow = Engine::GetInstance()->GetMainWnd(); // ����ۿ� �׷��� �̹����� ��½�ų ������
        Desc.Windowed = true; // â���(true), ��üȭ�� ���(false)

        Desc.SampleDesc.Count = 1;
        Desc.SampleDesc.Quality = 0;

        Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // ������ �׷��� �̹����� �������� ����
        Desc.Flags = 0;

        ComPtr<IDXGIDevice> IDXGIDevice = nullptr;
        ComPtr<IDXGIAdapter> pAdapter = nullptr;
        ComPtr<IDXGIFactory> pFactory = nullptr;

        // 128 ��Ʈ
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

    // Render Target, Depth Stencil ����
    {
        // RenderTarget �ؽ�ó : SwapChain �� �����ɶ� ������� ID3D11Texture2D ��ü�� ����Ų��.
        m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_rtTex.GetAddressOf());

        // RenderTargetView ����
        if (FAILED(m_device->CreateRenderTargetView(m_rtTex.Get(), nullptr, m_rtView.GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateRenderTargetView is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // Depth Stencil �ؽ�ó
        D3D11_TEXTURE2D_DESC Desc = {};

        Desc.Width = RESOLUTION.x;
        Desc.Height = RESOLUTION.y;

        Desc.ArraySize = 1;
        Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

        Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // �ؽ�ó �뵵

        // CPU ���� ���� ���Ŀ� ������ �������� �ɼ� (Usage, CPUAccessFlags�� ���� ����)
        Desc.Usage = D3D11_USAGE_DEFAULT;
        Desc.CPUAccessFlags = 0;
        // => ���� �Ұ�

        Desc.MipLevels = 1; // �Ӹ� ���� 1 (������ ����)

        Desc.MiscFlags = 0;
        Desc.SampleDesc.Count = 1;
        Desc.SampleDesc.Quality = 0;

        if (FAILED(m_device->CreateTexture2D(&Desc, nullptr, m_dsTex.GetAddressOf())))
        {
            MessageBoxA(nullptr, "Create Depth/Stencil Texture is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // DepthStencilView ����
        if (FAILED(m_device->CreateDepthStencilView(m_dsTex.Get(), nullptr, m_dsView.GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthsStencilView is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }
    }

    // Rasterizer State ����
    {
        // CULL BACK (�޸� �ﰢ�� ����)
        m_rs.at((size_t)RASTERIZER_TYPE::CULL_BACK) = nullptr;
        
        // CULL FRONT (�ո� �ﰢ�� ����)
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

    // Sampler State ����
    {
        D3D11_SAMPLER_DESC Desc = {};
        ComPtr<ID3D11SamplerState> sampler = m_sampler.at((size_t)SAMPLER_TYPE::AF);

        // �̹漺 ���͸� ���÷�
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

        // MIN_MAG_POINT ����
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

    // Blend State ����
    {
        m_bs.at((size_t)BLEND_TYPE::DEFAULT) = nullptr;

        D3D11_BLEND_DESC Desc = {};

        Desc.AlphaToCoverageEnable = false;
        Desc.IndependentBlendEnable = false;
        Desc.RenderTarget[0].BlendEnable = true;
        Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;       // ���󳢸� ���ϱ�
        Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;    // Source : PixelShader return ���� ���� ���
        Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;// Destination : ������ ��µ� ����Ÿ��

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

    // Depth Stencil State ����
    {
        // Less
        m_ds.at((size_t)DEPTH_STENCIL_TYPE::LESS) = nullptr;

        // LessEqual
        D3D11_DEPTH_STENCIL_DESC Desc = {};
        Desc.StencilEnable = false;
        Desc.DepthEnable = true;                            // �������� ����
        Desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;       // �۰ų� ������� ���
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // ���� ���
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::LESS_EQUAL).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(LESS EQUAL) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // Greater
        Desc.StencilEnable = false;
        Desc.DepthEnable = true;                            // �������� ����
        Desc.DepthFunc = D3D11_COMPARISON_GREATER;          // ���̰� ū ��� ���
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // ���� ���
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::GREATER).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(GREATER) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // NoTest
        Desc.StencilEnable = false;
        Desc.DepthEnable = false;                           // �������� �������� ����
        Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;           // �׻� ���
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // ���� ���
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::NO_TEST).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(NO TEST) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // NoWrite
        Desc.StencilEnable = false;
        Desc.DepthEnable = true;                            // �������� ����
        Desc.DepthFunc = D3D11_COMPARISON_LESS;             // ������� ���
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;  // ���� ������� ����
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::NO_WRITE).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(NO WRITE) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }

        // NoTest NoWrite
        Desc.StencilEnable = false;
        Desc.DepthEnable = false;                           // �������� X
        Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;           // �׻� ���
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;  // ���� ������� ����
        if (FAILED(DEVICE->CreateDepthStencilState(&Desc, m_ds.at((size_t)DEPTH_STENCIL_TYPE::NO_TEST_NO_WRITE).GetAddressOf())))
        {
            MessageBoxA(nullptr, "CreateDepthStencilState(NO TEST NO WRITE) is failed", "Initialize Device is failed", MB_OK);
            return E_FAIL;
        }
    }

    // viewport ����
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