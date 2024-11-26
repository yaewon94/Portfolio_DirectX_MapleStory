#include "pch.h"
#include "Shader.h"

Shader::Shader(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
{
}

Shader::~Shader()
{
}