#include "pch.h"
#include "Material.h"
#include "Device.h"

Material::Material(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
	, m_origin(nullptr)
	, m_shader(nullptr)
	, m_cb{}
{
}

Material::Material(SharedPtr<Material> origin)
	: Asset("", "")
	, m_origin(origin)
	, m_shader(origin->m_shader)
	, m_cb(origin->m_cb)
	, m_texMap()
{
	for (const auto& pair : origin->m_texMap)
	{
		m_texMap.insert(make_pair(pair.first, pair.second));
	}
}

Material::~Material()
{
}

void Material::Binding()
{
	if (m_shader == nullptr)
	{
		MessageBoxA(nullptr, "Shader is not exist", "Binding Material is failed", MB_OK);
		return;
	}

	// Texture
	for (auto& pair : m_texMap)
	{
		if (pair.second == nullptr)
		{
			m_cb.bTex[pair.first] = false;
			pair.second->Clear_GS();
		}
		else
		{
			m_cb.bTex[pair.first] = true;
			pair.second->Binding_GS(pair.first);
		}
	}

	// Const Buffer
	ConstBuffer* cb = Device::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::MATERIAL);
	cb->SetData(&m_cb);
	cb->Binding_GS();

	// Shader
	m_shader->Binding();
}

SharedPtr<Texture> Material::GetTexture(TEXTURE_PARAM type) const
{
	map <TEXTURE_PARAM, SharedPtr<Texture>>::const_iterator iter = m_texMap.find(type);
	if (iter != m_texMap.end())
	{
		return iter->second;
	}
	else
	{
		MessageBoxA(nullptr, "Texture is not exist", "Find Texture is failed", MB_OK);
		return nullptr;
	}
}

void Material::SetTextureParam(TEXTURE_PARAM type, SharedPtr<Texture> texture)
{
	auto iter = m_texMap.find(type);

	if (iter != m_texMap.end()) iter->second = texture;
	else m_texMap.insert(make_pair(type, texture));
}