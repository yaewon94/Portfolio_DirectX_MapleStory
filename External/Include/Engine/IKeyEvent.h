#pragma once

// KEY 값
enum KEY_CODE
{
	KEY_LEFT = VK_LEFT, KEY_RIGHT = VK_RIGHT, KEY_UP = VK_UP,
	KEY_ALT = VK_MENU
};

// 키 입력 콜백함수 사용을 위한 인터페이스
class IKeyEvent
{
	friend class KeyManager;

protected:
	virtual ~IKeyEvent() {}
	virtual void OnKeyTap(KEY_CODE key) = 0;
	virtual void OnKeyDown(KEY_CODE key) = 0;
	virtual void OnKeyReleased(KEY_CODE key) = 0;
};