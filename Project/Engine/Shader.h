#pragma once
#include "Asset.h"

// GPU ������ ȿ�� ����ϴ� �ڵ�
class Shader : public Asset
{
	NO_COPY_MOVE(Shader);

protected:
	ComPtr<ID3DBlob> m_errorBlob;

protected:
	Shader(const string& Key, const string& relativePath);
	~Shader();
};