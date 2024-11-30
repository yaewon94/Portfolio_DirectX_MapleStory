// [구성 : Release] 파일 우클릭 > 속성 > 일반 > 빌드에서 제외 > 예 
#pragma once

class IDebugRenderable
{
	friend class RenderManager;

protected:
	virtual ~IDebugRenderable() {}
	virtual void Render() = 0;
};