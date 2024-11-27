#pragma once

//template<typename T>
class IRenderable
{
	//friend class T;
	friend class Camera;

protected:
	virtual ~IRenderable() {}
	virtual void Render() = 0;
};