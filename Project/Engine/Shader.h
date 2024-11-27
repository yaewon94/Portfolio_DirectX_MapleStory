#pragma once
#include "Asset.h"

// shader domain (value : ������ ����)
enum SHADER_DOMAIN : byte
{
	DOMAIN_OPAQUE, DOMAIN_MASK, DOMAIN_TRANSPARENT, DOMAIN_PARTICLE, DOMAIN_POST_PROCESS, 
	SHADER_DOMAIN_COUNT_END
};

// GPU ������ ȿ�� ����ϴ� �ڵ�
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
		// TODO : ������ ����� ��� (�ΰ��Ӹ�� ��Ÿ�� �߿� �������� �ٲ�� ��� ������ ��)
		// ����ī�޶� ���� �����ο� ��ϵǾ��ִ� ������Ʈ ����, ���ο� ���������� ������Ʈ �߰�
	}
};