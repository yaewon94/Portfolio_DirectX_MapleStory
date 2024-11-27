#pragma once
#include "Asset.h"

// shader domain (value : 렌더링 순서)
enum SHADER_DOMAIN : byte
{
	DOMAIN_OPAQUE, DOMAIN_MASK, DOMAIN_TRANSPARENT, DOMAIN_PARTICLE, DOMAIN_POST_PROCESS, 
	SHADER_DOMAIN_COUNT_END
};

// GPU 렌더링 효과 계산하는 코드
class Shader : public Asset
{
	NO_COPY_MOVE(Shader);

protected:
	ComPtr<ID3DBlob> m_errorBlob;
	SHADER_DOMAIN m_domain;

protected:
	Shader(const string& Key, const string& relativePath);
	~Shader();

public:
	SHADER_DOMAIN GetShaderDomain() const { return m_domain; }
	void SetShaderDomain(SHADER_DOMAIN domain)
	{
		if (m_domain == domain) return;

#ifdef _DEBUG
		if (domain == SHADER_DOMAIN_COUNT_END) assert(nullptr);
#endif // _DEBUG

		m_domain = domain;
		// TODO : 에디터 모드인 경우 (인게임모드 런타임 중엔 에셋정보 바뀌는 경우 무시할 것)
		// 메인카메라 기존 도메인에 등록되어있던 오브젝트 삭제, 새로운 도메인으로 오브젝트 추가
	}
};