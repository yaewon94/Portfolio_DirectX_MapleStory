#pragma once

// KEY ��
enum KEY_CODE
{
	KEY_LEFT = VK_LEFT, KEY_RIGHT = VK_RIGHT
};

// KEY ����
enum class KEY_STATE
{
	NONE, TAP, DOWN, RELEASED
};

// Ű����, ���콺 �Է� ó�� Ŭ����
class KeyManager final : public Singleton<KeyManager>
{
	SINGLETON(KeyManager);

private:
	map<KEY_CODE, KEY_STATE> m_keyMap;

public:
	void Init();
	void Tick();

public:
	void AddKey(KEY_CODE keyCode) { m_keyMap.insert(make_pair(keyCode, KEY_STATE::NONE)); }
};