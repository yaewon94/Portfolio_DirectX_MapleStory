#pragma once

//template<typename T>
class IRenderable
{
	//friend class T;
	friend class GameObject;

protected:
	virtual ~IRenderable() {}
	virtual void Render() = 0;
};