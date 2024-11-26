#pragma once
#include "Asset.h"

// GPU 렌더링 효과 계산하는 코드
class Shader : public Asset
{
	NO_COPY_MOVE(Shader);

protected:
	ComPtr<ID3DBlob> m_errorBlob;

protected:
	Shader(const string& Key, const string& relativePath);
	~Shader();
};