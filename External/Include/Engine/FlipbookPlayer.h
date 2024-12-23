#pragma once
#include "MeshRender.h"
#include "Flipbook.h"

// Flipbook 재생 컴포넌트
class FlipbookPlayer final : public MeshRender
{
	NO_COPY_MOVE(FlipbookPlayer)
	COMPONENT_TYPE_DCL(COMPONENT_TYPE::FLIPBOOKPLAYER)

private:
	unordered_map<string, SharedPtr<Flipbook>> m_flipbookMap;
	SharedPtr<Flipbook> m_curFlipbook;
	float m_term; // 다음 프레임으로 넘어가기까지 시간
	float m_playAccTime; // 재생 누적시간 (프레임 전환될 때마다 초기화됨)
	size_t m_curFrameIndex; // 현재 재생중인 프레임 인덱스
	bool m_isRepeat;
	bool m_isFinish;

public:
	FlipbookPlayer(GameObject* const owner);
	FlipbookPlayer(const FlipbookPlayer& origin, GameObject* const newOwner);
	~FlipbookPlayer();

private: // GameObject : Component* 를 통해 호출
	virtual void Init() final;
	virtual void FinalTick() final;
	virtual void SetActive(bool flag) final
	{
		if (flag) m_curFrameIndex = 0;
	}

private: // Camera : IRenderable* 을 통해 호출
	virtual void Render() final;

public:
	UINT GetFPS() const { return (UINT)(1.f / m_term); }
	void SetFPS(UINT fps);

	bool IsRepeat() const { return m_isRepeat; }
	void SetRepeat(bool flag) { m_isRepeat = flag; }

	bool IsFinish() const { return m_isFinish; }

public:
	void Clear()
	{ 
		m_flipbookMap.clear();
		m_curFlipbook = nullptr;
	}

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
			MessageBox(nullptr, L"이미 같은 KEY값의 Flipbook이 등록되어 있습니다", L"Flipbook 추가 실패", MB_OK);
			return;
		}
		m_flipbookMap.insert(make_pair(key, flipbook));
		if(m_curFlipbook == nullptr) ChangeFlipbook(key, false);
	}

	// @ isChangeObjSize : Flipbook 프레임 사이즈에 맞게 게임오브젝트 크기를 변경시킬 것인지 여부
	void ChangeFlipbook(const string& key, bool isAdjustObjSize)
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
		m_isFinish = false;
		if (isAdjustObjSize) m_curFlipbook->AdjustObjSize(GetOwner());
	}

private: // GameObject::복사생성자 에서 호출
	virtual FlipbookPlayer* Clone(GameObject* const newOwner) final { return new FlipbookPlayer(*this, newOwner); }
};