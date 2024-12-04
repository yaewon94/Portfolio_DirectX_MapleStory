#pragma once
#include "MeshRender.h"
#include "Flipbook.h"

// Flipbook ��� ������Ʈ
class FlipbookPlayer final : public MeshRender
{
	NO_COPY_MOVE(FlipbookPlayer)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::FLIPBOOKPLAYER)

private:
	unordered_map<string, SharedPtr<Flipbook>> m_flipbookMap;
	SharedPtr<Flipbook> m_curFlipbook;
	float m_term; // ���� ���������� �Ѿ����� �ð�
	float m_playAccTime; // ��� �����ð� (������ ��ȯ�� ������ �ʱ�ȭ��)
	byte m_curFrameIndex; // ���� ������� ������ �ε���
	bool m_isRepeat;

public:
	FlipbookPlayer(GameObject* const owner);
	FlipbookPlayer(const FlipbookPlayer& origin, GameObject* const newOwner);
	~FlipbookPlayer();

private: // GameObject : Component* �� ���� ȣ��
	virtual void Init() final;
	virtual void FinalTick() final;

private: // Camera : IRenderable* �� ���� ȣ��
	virtual void Render() final;

public:
	UINT GetFPS() const { return (UINT)(1.f / m_term); }
	void SetFPS(UINT fps);

	bool IsRepeat() const { return m_isRepeat; }
	void SetRepeat(bool flag) { m_isRepeat = flag; }

public:
	void AddFlipbook(const string& key, SharedPtr<Flipbook> flipbook)
	{
		if (flipbook == nullptr || flipbook->GetAtlasTexture() == nullptr)
		{
#ifdef _DEBUG
			assert(nullptr);
#else
			return;
#endif // _DEBUG
		}
		if (m_flipbookMap.find(key) != m_flipbookMap.end())
		{
			MessageBox(nullptr, L"�̹� ���� KEY���� Flipbook�� ��ϵǾ� �ֽ��ϴ�", L"Flipbook �߰� ����", MB_OK);
			return;
		}
		m_flipbookMap.insert(make_pair(key, flipbook));
		if(m_curFlipbook == nullptr) ChangeFlipbook(m_flipbookMap.begin()->first);
	}

	void ChangeFlipbook(const string& key)
	{
		unordered_map<string, SharedPtr<Flipbook>>::const_iterator iter = m_flipbookMap.find(key);
		if (iter == m_flipbookMap.end())
		{
#ifdef _DEBUG
			assert(nullptr);
#else
			return;
#endif // _DEBUG
		}
		m_curFlipbook = iter->second;
		m_curFrameIndex = 0;
	}

private: // GameObject::��������� ���� ȣ��
	virtual FlipbookPlayer* Clone(GameObject* const newOwner) final { return new FlipbookPlayer(*this, newOwner); }
};