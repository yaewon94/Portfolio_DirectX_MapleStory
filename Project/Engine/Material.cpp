#include "pch.h"
#include "Material.h"
#include "Device.h"
#include "GraphicShader.h"

Material::Material(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
	, m_origin(nullptr)
	, m_shader(nullptr)
	, m_cb{}
{
}

Material::Material(const Material& origin) 
	: Asset("", "")
{
	*this = origin;
}

Material::~Material()
{
	m_origin = nullptr;
	m_shader = nullptr;
	m_texMap.clear();
}

Material& Material::operator=(const Material& other)
{
	m_origin = const_cast<Material*>(&other);
	m_shader = other.m_shader;
	m_cb = other.m_cb;

	for (const auto& pair : other.m_texMap)
	{
		m_texMap.insert(make_pair(pair.first, pair.second));
	}

	return *this;
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
		m_cb.bTex[pair.first] = 1;
		pair.second->Binding_GS(pair.first);
	}

	// Const Buffer
	ConstBuffer* cb = Device::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::MATERIAL);
	cb->SetData(&m_cb);
	cb->Binding();

	// Shader
	m_shader->Binding();
}

Texture* const Material::GetTexture(TEXTURE_PARAM type) const
{
	map <TEXTURE_PARAM, Texture*>::const_iterator iter = m_texMap.find(type);
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

void Material::SetTextureParam(TEXTURE_PARAM type, Texture* const texture)
{
	auto iter = m_texMap.find(type);

	if (iter != m_texMap.end()) iter->second = texture;
	else m_texMap.insert(make_pair(type, texture));
}