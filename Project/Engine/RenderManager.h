#pragma once
#include "IDebugRenderable.h"

class Camera;
class GameObject;

// 렌더링 전담, 카메라 관리 클래스
class RenderManager final : public Singleton<RenderManager>
{
	SINGLETON(RenderManager);

private:
	vector<Camera*> m_cams;

public:
	void Render();

public:
	byte GetCameraCount() const { return m_cams.size(); }
	void AddCamera(Camera* const cam);
	void DeleteCamera(Camera* const cam);

	//@ (camPriority == 0) : main camera
	void AddObject(GameObject* const obj, byte camPriority = 0);

#ifdef _DEBUG
private:
	vector<IDebugRenderable*> m_dbgRenderList;

public:
	void AddDebugRender(IDebugRenderable* dbgRender)
	{
		for (auto _dbgRender : m_dbgRenderList)
		{
			if (dbgRender == _dbgRender) assert(nullptr);
		}

		m_dbgRenderList.push_back(dbgRender);
	}
#endif // _DEBUG
};