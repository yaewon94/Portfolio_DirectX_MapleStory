#include "pch.h"
#include "RenderManager.h"
#include "Camera.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
	for (auto cam : m_cams)
	{
		cam = nullptr;
	}
}

void RenderManager::Render()
{
	for (auto cam : m_cams)
	{
		cam->Render();
	}
}

void RenderManager::AddCamera(Camera* const cam)
{
#ifdef _DEBUG
	// �ߺ�üũ
	for (auto _cam : m_cams)
	{
		if (cam == _cam) assert(nullptr);
	}
#endif // _DEBUG

	if (cam->GetPriority() == 0)
	{
		if (m_cams.empty()) m_cams.push_back(cam); // ���� ī�޶�� ���
#ifdef _DEBUG
		else assert(nullptr);
#endif // _DEBUG
	}
	else
	{
		if (cam->GetPriority() == m_cams.size()) m_cams.push_back(cam);

		// SetPriority() �ڵ忡�� RenderManager::AddCamera()�� ȣ���ϹǷ� �ٲ� priority�� �°� ī�޶� ��ϵ�
		else if (cam->GetPriority() > m_cams.size()) cam->SetPriority(m_cams.size());
		else
		{
			// �����Ϸ��� ��ġ�� �ִ� ī�޶� ��ĭ �ڷ� ����
			m_cams[cam->GetPriority()]->SetPriority(cam->GetPriority() + 1);
			// ī�޶� ���
			m_cams[cam->GetPriority()] = cam;
		}
	}
}

void RenderManager::DeleteCamera(Camera* const cam)
{
	// ���α׷� ��ü ������ �� RenderManager �Ҹ��ڰ� Camera �Ҹ��ں��� ���� ȣ��Ǵ� ���
	if (m_cams.empty()) return;

#ifdef _DEBUG
	if (m_cams[cam->GetPriority()] != cam) assert(nullptr);
#endif // _DEBUG
	
	if (cam->GetPriority() == m_cams.size() - 1) m_cams.pop_back();
	else
	{
		// �� �ڿ� �ִ� ī�޶� �� ��ġ�� �ű�
		m_cams[cam->GetPriority()] = m_cams[cam->GetPriority() + 1];
		// �ڿ��ִ� ī�޶� �켱���� ����
		m_cams[cam->GetPriority()]->SetPriority(m_cams[cam->GetPriority()]->GetPriority() - 1);
	}
}

void RenderManager::AddObject(GameObject* const obj, byte camPriority)
{
	if (camPriority >= m_cams.size())
	{
		MessageBox(nullptr
			, L"��ϵ� ī�޶� �������� camPriority ���� Ŀ��, �켱������ ���� ���� ī�޶� ������Ʈ�� ����մϴ�"
			, L"RenderManager AddObject Notice"
			, MB_OK);

		m_cams.back()->AddRenderObject(obj);
	}
	else
	{
		m_cams[camPriority]->AddRenderObject(obj);
	}
}