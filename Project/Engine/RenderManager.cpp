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
	// 중복체크
	for (auto _cam : m_cams)
	{
		if (cam == _cam) assert(nullptr);
	}
#endif // _DEBUG

	if (cam->GetPriority() == 0)
	{
		if (m_cams.empty()) m_cams.push_back(cam); // 메인 카메라로 등록
#ifdef _DEBUG
		else assert(nullptr);
#endif // _DEBUG
	}
	else
	{
		if (cam->GetPriority() == m_cams.size()) m_cams.push_back(cam);

		// SetPriority() 코드에서 RenderManager::AddCamera()를 호출하므로 바뀐 priority에 맞게 카메라 등록됨
		else if (cam->GetPriority() > m_cams.size()) cam->SetPriority(m_cams.size());
		else
		{
			// 삽입하려는 위치에 있는 카메라를 한칸 뒤로 보냄
			m_cams[cam->GetPriority()]->SetPriority(cam->GetPriority() + 1);
			// 카메라 등록
			m_cams[cam->GetPriority()] = cam;
		}
	}
}

void RenderManager::DeleteCamera(Camera* const cam)
{
	// 프로그램 전체 종료할 때 RenderManager 소멸자가 Camera 소멸자보다 먼저 호출되는 경우
	if (m_cams.empty()) return;

#ifdef _DEBUG
	if (m_cams[cam->GetPriority()] != cam) assert(nullptr);
#endif // _DEBUG
	
	if (cam->GetPriority() == m_cams.size() - 1) m_cams.pop_back();
	else
	{
		// 내 뒤에 있는 카메라를 내 위치로 옮김
		m_cams[cam->GetPriority()] = m_cams[cam->GetPriority() + 1];
		// 뒤에있던 카메라 우선순위 변경
		m_cams[cam->GetPriority()]->SetPriority(m_cams[cam->GetPriority()]->GetPriority() - 1);
	}
}

void RenderManager::AddObject(GameObject* const obj, byte camPriority)
{
	if (camPriority >= m_cams.size())
	{
		MessageBox(nullptr
			, L"등록된 카메라 개수보다 camPriority 값이 커서, 우선순위가 제일 낮은 카메라에 오브젝트를 등록합니다"
			, L"RenderManager AddObject Notice"
			, MB_OK);

		m_cams.back()->AddRenderObject(obj);
	}
	else
	{
		m_cams[camPriority]->AddRenderObject(obj);
	}
}