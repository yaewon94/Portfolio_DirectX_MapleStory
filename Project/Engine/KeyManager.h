#pragma once

// KEY 값
enum KEY_CODE
{
	KEY_LEFT = VK_LEFT, KEY_RIGHT = VK_RIGHT
};

// KEY 상태
enum class KEY_STATE
{
	NONE, DOWN, RELEASED
};

// 키 입력 콜백함수 사용을 위한 인터페이스
class IKeyEvent
{
	friend class KeyManager;

protected:
	virtual ~IKeyEvent() {}
};

typedef void (IKeyEvent::*KEY_CALLBACK)(KEY_CODE);

// 키보드, 마우스 입력 처리 클래스
class KeyManager final : public Singleton<KeyManager>
{
	SINGLETON(KeyManager);

private:
	struct KeyInfo
	{
		KEY_STATE state;
		IKeyEvent* instance = nullptr;
		KEY_CALLBACK keyDownCallback;
	};

private:
	unordered_map<KEY_CODE, KeyInfo> m_keyMap;

public:
	void Tick();

public:
	void AddKey(KEY_CODE key, IKeyEvent* const instance, KEY_CALLBACK keyDownCallback)
	{
		m_keyMap.insert(make_pair(key, KeyInfo{KEY_STATE::NONE, instance, keyDownCallback}));
	}
};