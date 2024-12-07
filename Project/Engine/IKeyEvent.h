#pragma once

// KEY ��
enum KEY_CODE
{
	KEY_LEFT = VK_LEFT, KEY_RIGHT = VK_RIGHT, KEY_UP = VK_UP,
	KEY_ALT = VK_MENU
};

// Ű �Է� �ݹ��Լ� ����� ���� �������̽�
class IKeyEvent
{
	friend class KeyManager;

protected:
	virtual ~IKeyEvent() {}
	virtual void OnKeyTap(KEY_CODE key) = 0;
	virtual void OnKeyDown(KEY_CODE key) = 0;
	virtual void OnKeyReleased(KEY_CODE key) = 0;
};