#include "pch.h"
#include "Shader.h"

Shader::Shader(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
	, m_domain(SHADER_DOMAIN::DOMAIN_OPAQUE)
{
}

Shader::~Shader()
{
}