#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "GraphicShader.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

int AssetManager::Init()
{
	// �⺻ Mesh ����
	{
		SharedPtr<Mesh> mesh = nullptr;

		// �簢��
		{
			Vertex vertexArr[4] = {};
			vertexArr[0].pos = Vec3(-0.5f, 0.5f, 0.f);
			vertexArr[0].uv = Vec2(0.f, 0.f);
			vertexArr[0].color = Vec4(1.f, 0.f, 0.f, 1.f);

			vertexArr[1].pos = Vec3(0.5f, 0.5f, 0.f);
			vertexArr[1].uv = Vec2(1.f, 0.f);
			vertexArr[1].color = Vec4(0.f, 0.f, 1.f, 1.f);

			vertexArr[2].pos = Vec3(0.5f, -0.5f, 0.f);
			vertexArr[2].uv = Vec2(1.f, 1.f);
			vertexArr[2].color = Vec4(0.f, 1.f, 0.f, 1.f);

			vertexArr[3].pos = Vec3(-0.5f, -0.5f, 0.f);
			vertexArr[3].uv = Vec2(0.f, 1.f);
			vertexArr[3].color = Vec4(1.f, 0.f, 1.f, 1.f);

			// �ε��� �� ����
			UINT indexArr[] = { 0, 1, 2, 0, 2, 3 };

			// �޽� ���� ����
			mesh = AddAsset<Mesh>("RectMesh", "");
			if (FAILED(mesh->Create(vertexArr, sizeof(vertexArr)/sizeof(Vertex), indexArr, sizeof(indexArr)/sizeof(UINT))))
			{
				MessageBoxA(nullptr, "Create Rect Mesh is failed", "Create Asset is failed", MB_OK);
				return E_FAIL;
			}

#ifdef _DEBUG
			// ������ �簢��
			{
				UINT dbgRectIdx[] = { 0, 1, 2, 3, 0 };
				mesh = AddAsset<Mesh>("RectMesh_D", "");
				if (FAILED(mesh->Create(vertexArr, sizeof(vertexArr) / sizeof(Vertex), dbgRectIdx, sizeof(dbgRectIdx)/sizeof(UINT))))
				{
					MessageBoxA(nullptr, "Create Debug Rect Mesh is failed", "Create Asset is failed", MB_OK);
					return E_FAIL;
				}
			}
#endif // _DEBUG
		}
	}

	// �⺻ Graphic Shader ����
	{
		SharedPtr<GraphicShader> shader = nullptr;

		// �⺻ 2D ���̴�
		{
			shader = AddAsset<GraphicShader>("Std2D_Shader", "Std2D.fx");
			shader->SetRasterizerType(RASTERIZER_TYPE::CULL_NONE);
			shader->SetBlendType(BLEND_TYPE::DEFAULT);
			shader->SetShaderDomain(SHADER_DOMAIN::DOMAIN_OPAQUE);
			if (FAILED(shader->CreateVertexShader("VS_Std2D"))) return E_FAIL;
			if (FAILED(shader->CreatePixelShader("PS_Std2D"))) return E_FAIL;
		}

		// �⺻ 2D ���ĺ��� ���̴�
		{
			shader = AddAsset<GraphicShader>("Std2D_AlphaBlend_Shader", "Std2D.fx");
			shader->SetRasterizerType(RASTERIZER_TYPE::CULL_NONE);
			shader->SetBlendType(BLEND_TYPE::ALPHABLEND);
			shader->SetShaderDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);
			if (FAILED(shader->CreateVertexShader("VS_Std2D"))) return E_FAIL;
			if (FAILED(shader->CreatePixelShader("PS_Std2D_AlphaBlend"))) return E_FAIL;
		}

#ifdef _DEBUG
		// ����� ���̴�
		{
			shader = AddAsset<GraphicShader>("Debug_Shader", "Debug.fx");
			shader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
			shader->SetRasterizerType(RASTERIZER_TYPE::CULL_NONE);
			shader->SetBlendType(BLEND_TYPE::DEFAULT);
			shader->SetDepthStencilType(DEPTH_STENCIL_TYPE::NO_TEST_NO_WRITE);
			shader->SetShaderDomain(SHADER_DOMAIN::DOMAIN_DEBUG);
			if (FAILED(shader->CreateVertexShader("VS_Debug"))) return E_FAIL;
			if (FAILED(shader->CreatePixelShader("PS_Debug"))) return E_FAIL;
		}
#endif // _DEBUG
	}

	// �⺻ Material ����
	{
		SharedPtr<Material> mtrl = nullptr;
		SharedPtr<GraphicShader> shader = nullptr;

		// �⺻ 2D
		{
			mtrl = AddAsset<Material>("Std2D_Material", "");
			if ((shader = FindAsset<GraphicShader>("Std2D_Shader")) == nullptr)
			{
				MessageBoxA(nullptr, "Std2D_Shader is not exist", "Create Std2D_Material is failed", MB_OK);
				return E_FAIL;
			}
			mtrl->SetShader(shader);
		}

		// �⺻ 2D ���ĺ���
		{
			mtrl = AddAsset<Material>("Std2D_AlphaBlend_Material", "");
			if ((shader = FindAsset<GraphicShader>("Std2D_AlphaBlend_Shader")) == nullptr)
			{
				MessageBoxA(nullptr, "Std2D_AlphaBlend_Shader is not exist", "Create Std2D_AlphaBlend_Material is failed", MB_OK);
				return E_FAIL;
			}
			mtrl->SetShader(shader);
		}

#ifdef _DEBUG
		// �����
		{
			mtrl = AddAsset<Material>("Debug_Material", "");
			if ((shader = FindAsset<GraphicShader>("Debug_Shader")) == nullptr)
			{
				MessageBoxA(nullptr, "Debug_Shader is not exist", "Create Debug_Material is failed", MB_OK);
				return E_FAIL;
			}
			mtrl->SetShader(shader);
		}
#endif // _DEBUG
	}

	return S_OK;
}