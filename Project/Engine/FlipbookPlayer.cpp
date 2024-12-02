#include "pch.h"
#include "FlipbookPlayer.h"
#include "Device.h"
#include "AssetManager.h"
#include "TimeManager.h"

FlipbookPlayer::FlipbookPlayer(GameObject* const owner) 
	: MeshRender(owner)
	, m_curFlipbook(nullptr)
	, m_term(1.f)
	, m_isRepeat(true)
{
	Init();
}

FlipbookPlayer::FlipbookPlayer(const FlipbookPlayer& origin, GameObject* const newOwner) 
	: MeshRender(origin, newOwner)
	, m_curFlipbook(origin.m_curFlipbook)
	, m_term(origin.m_term)
	, m_isRepeat(origin.m_isRepeat)
{
	Init();
}

FlipbookPlayer::~FlipbookPlayer()
{
}

void FlipbookPlayer::Init()
{
	// ���� �ʱ�ȭ
	SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));

	// Flipbook ��� ���� �ʱ�ȭ
	m_playAccTime = 0.f;
	m_curFrameIndex = 0;

	// Gameobject���� Init()�� ȣ���ϴ°� �ƴ϶� ȣ��� ���� ����
	//if (m_flipbookMap.size() > 0) ChangeFlipbook(m_flipbookMap.begin()->first);
}

void FlipbookPlayer::FinalTick()
{
	if (m_curFlipbook == nullptr) return;

	if (m_playAccTime >= m_term)
	{
		m_playAccTime -= m_term;

		// ������ �������� ���
		if (++m_curFrameIndex == m_curFlipbook->GetFrameCount())
		{
			m_curFrameIndex = 0;

			if (!m_isRepeat)
			{
				// TODO : ���� �ִϸ��̼� ���� �Ǵ� �ٸ� �ִϸ��̼����� ��ȯ
			}
		}
	}
	else
	{
		m_playAccTime += DT;
	}
}

void FlipbookPlayer::Render()
{
	if (m_curFlipbook == nullptr) return;

	m_curFlipbook->Bind(m_curFrameIndex);
	GetMaterial()->SetTextureParam(TEX_0, m_curFlipbook->GetAtlasTexture());
	MeshRender::Render();
	m_curFlipbook->Clear(m_curFrameIndex);
}

void FlipbookPlayer::SetFPS(UINT fps)
{
	const UINT MaxFPS = 1.f / Device::GetInstance()->GetRefreshRateDT();
	if (fps > MaxFPS)
	{
		wstring msg = std::to_wstring(MaxFPS) + L"���� ���� ���� ������ �� �����ϴ�";
		MessageBox(nullptr, msg.c_str(), L"FPS ���� ����", MB_OK);
		return;
	}
	m_term = 1.f / fps;
}