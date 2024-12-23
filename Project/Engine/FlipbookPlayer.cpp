#include "pch.h"
#include "FlipbookPlayer.h"
#include "Device.h"
#include "AssetManager.h"
#include "TimeManager.h"

FlipbookPlayer::FlipbookPlayer(GameObject* const owner) 
	: MeshRender(owner)
	, m_term(1.f / 6.f)
	, m_isRepeat(true), m_isFinish(false)
{
	// ���� �ʱ�ȭ
	SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_Material"));
}

FlipbookPlayer::FlipbookPlayer(const FlipbookPlayer& origin, GameObject* const newOwner) 
	: MeshRender(origin, newOwner)
	, m_curFlipbook(origin.m_curFlipbook)
	, m_term(origin.m_term)
	, m_isRepeat(origin.m_isRepeat), m_isFinish(origin.m_isFinish)
{
}

FlipbookPlayer::~FlipbookPlayer()
{
}

void FlipbookPlayer::Init()
{
	// Flipbook ��� ���� �ʱ�ȭ
	m_playAccTime = 0.f;
	m_curFrameIndex = 0;
}

void FlipbookPlayer::FinalTick()
{
	if (m_isFinish || m_curFlipbook == nullptr) return;

	if (m_playAccTime >= m_term)
	{
		m_playAccTime -= m_term;

		// ������ �������� ���
		if (++m_curFrameIndex == m_curFlipbook->GetFrameCount())
		{
			m_curFrameIndex = 0;
			if (!m_isRepeat) m_isFinish = true;
		}
	}
	else
	{
		m_playAccTime += DT;
	}
}

void FlipbookPlayer::Render()
{
	if (m_isFinish || m_curFlipbook == nullptr) return;

	m_curFlipbook->Bind(m_curFrameIndex);
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