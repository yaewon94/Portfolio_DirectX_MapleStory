#include "pch.h"
#include "GraphicShader.h"

#define VERTEX_SHADER_VER "vs_5_0"
#define GEOMETRY_SHADER_VER "gs_5_0"
#define PIXEL_SHADER_VER "ps_5_0"

GraphicShader::GraphicShader(const string& Key, const string& relativePath) 
	: Shader(Key, relativePath)
	, m_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, m_rsType(RASTERIZER_TYPE::CULL_BACK)
	, m_bsType(BLEND_TYPE::DEFAULT)
	, m_dsType(DEPTH_STENCIL_TYPE::LESS)
{
}

GraphicShader::~GraphicShader()
{
}

int GraphicShader::CreateVertexShader(const string& funcName)
{
	// ¼ÎÀÌ´õ ÆÄÀÏ ÄÄÆÄÀÏ
	UINT flag = D3DCOMPILE_DEBUG;
	HRESULT result = S_OK;

	result = D3DCompileFromFile(GetFullPathW().c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, funcName.c_str()
		, VERTEX_SHADER_VER
		, flag
		, 0
		, m_vsBlob.GetAddressOf()
		, m_errorBlob.GetAddressOf());

	if (FAILED(result))
	{
		errno_t errNum = GetLastError();

		if (errNum == 2 || errNum == 3)
		{
			MessageBoxA(nullptr, "Shader file does not exist", "Compilation of Vertex Shader is failed", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, (char*)m_errorBlob->GetBufferPointer(), "Compilation of Vertex Shader is failed", MB_OK);
		}

		return E_FAIL;
	}

	// ¼ÎÀÌ´õ °´Ã¼ »ý¼º
	DEVICE->CreateVertexShader(m_vsBlob->GetBufferPointer()
		, m_vsBlob->GetBufferSize()
		, nullptr
		, m_vs.GetAddressOf());

	// ¼ÎÀÌ´õ input layout
	D3D11_INPUT_ELEMENT_DESC layoutDesc[2] = {};

	layoutDesc[0].AlignedByteOffset = 0;
	layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[0].InputSlot = 0;
	layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[0].InstanceDataStepRate = 0;
	layoutDesc[0].SemanticName = "POSITION";
	layoutDesc[0].SemanticIndex = 0;

	layoutDesc[1].AlignedByteOffset = 12;
	layoutDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	layoutDesc[1].InputSlot = 0;
	layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[1].InstanceDataStepRate = 0;
	layoutDesc[1].SemanticName = "TEXCOORD";
	layoutDesc[1].SemanticIndex = 0;

	if (FAILED(DEVICE->CreateInputLayout(layoutDesc
		, sizeof(layoutDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC)
		, m_vsBlob->GetBufferPointer()
		, m_vsBlob->GetBufferSize()
		, m_layout.GetAddressOf())))
	{
		MessageBoxA(nullptr, "Create Input Layout is failed", "Compilation of Vertex Shader is failed", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

int GraphicShader::CreateGeometryShader(const string& funcName)
{
	UINT flag = D3DCOMPILE_DEBUG;
	HRESULT result = S_OK;

	result = D3DCompileFromFile(GetFullPathW().c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, funcName.c_str()
		, GEOMETRY_SHADER_VER
		, flag
		, 0
		, m_gsBlob.GetAddressOf()
		, m_errorBlob.GetAddressOf());

	if (FAILED(result))
	{
		errno_t errNum = GetLastError();

		if (errNum == 2 || errNum == 3)
		{
			MessageBoxA(nullptr, "Shader file does not exist", "Compilation of Geometry Shader is failed", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, (char*)m_errorBlob->GetBufferPointer(), "Compilation of Geometry Shader is failed", MB_OK);
		}

		return E_FAIL;
	}

	DEVICE->CreateGeometryShader(m_gsBlob->GetBufferPointer()
		, m_gsBlob->GetBufferSize()
		, nullptr
		, m_gs.GetAddressOf());

	return S_OK;
}

int GraphicShader::CreatePixelShader(const string& funcName)
{
	// ¼ÎÀÌ´õ ÆÄÀÏ ÄÄÆÄÀÏ
	UINT flag = D3DCOMPILE_DEBUG;
	HRESULT result = S_OK;

	result = D3DCompileFromFile(GetFullPathW().c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, funcName.c_str()
		, PIXEL_SHADER_VER
		, flag
		, 0
		, m_psBlob.GetAddressOf()
		, m_errorBlob.GetAddressOf());

	if (FAILED(result))
	{
		errno_t errNum = GetLastError();

		if (errNum == 2 || errNum == 3)
		{
			MessageBoxA(nullptr, "Shader file does not exist", "Compilation of Pixel Shader is failed", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, (char*)m_errorBlob->GetBufferPointer(), "Compilation of Pixel Shader is failed", MB_OK);
		}

		return E_FAIL;
	}

	// ¼ÎÀÌ´õ °´Ã¼ »ý¼º
	DEVICE->CreatePixelShader(m_psBlob->GetBufferPointer()
		, m_psBlob->GetBufferSize()
		, nullptr
		, m_ps.GetAddressOf());

	return S_OK;
}

void GraphicShader::Binding()
{
	// Input Assembler
	CONTEXT->IASetPrimitiveTopology(m_topology);
	CONTEXT->IASetInputLayout(m_layout.Get());

	// Vertex Shader Stage
	CONTEXT->VSSetShader(m_vs.Get(), nullptr, 0);

	// Geometry Shader Stage
	CONTEXT->GSSetShader(m_gs.Get(), nullptr, 0);

	// Pixel Shader Stage
	CONTEXT->PSSetShader(m_ps.Get(), nullptr, 0);

	// Rasterizer Stage
	CONTEXT->RSSetState(Device::GetInstance()->GetRasterizerState(m_rsType).Get());

	// Output Merge : Blend
	CONTEXT->OMSetBlendState(Device::GetInstance()->GetBlendState(m_bsType).Get(), nullptr, 0xffffffff);

	// Output Merge : Depth Stencil
	CONTEXT->OMSetDepthStencilState(Device::GetInstance()->GetDepthStencilState(m_dsType).Get(), 0);
}