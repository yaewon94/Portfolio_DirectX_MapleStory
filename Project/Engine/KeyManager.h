#pragma once

// KEY 값
enum KEY_CODE
{
	KEY_LEFT = VK_LEFT, KEY_RIGHT = VK_RIGHT
};

// KEY 상태
enum class KEY_STATE
{
	NONE, TAP, DOWN, RELEASED
};

// 키보드, 마우스 입력 처리 클래스
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