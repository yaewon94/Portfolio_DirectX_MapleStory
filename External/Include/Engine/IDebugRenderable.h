// [���� : Release] ���� ��Ŭ�� > �Ӽ� > �Ϲ� > ���忡�� ���� > �� 
#pragma once

class IDebugRenderable
{
	friend class RenderManager;

protected:
	virtual ~IDebugRenderable() {}
	virtual void Render() = 0;
};