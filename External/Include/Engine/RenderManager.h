#pragma once

class Camera;
class GameObject;

// ������ ����, ī�޶� ���� Ŭ����
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

	//@ camPriority == main camera
	void AddObject(GameObject* const obj, byte camPriority = 0);
};