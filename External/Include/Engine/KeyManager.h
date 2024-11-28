#pragma once

// KEY 값
enum KEY_CODE
{
	KEY_LEFT = VK_LEFT, KEY_RIGHT = VK_RIGHT,
	KEY_ALT = VK_MENU
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
	virtual void OnKeyDown(KEY_CODE key) = 0;
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
	};

private:
	unordered_map<KEY_CODE, KeyInfo> m_keyMap;

public:
	void Tick();

public:
	// @KEY_CALLBACK : 반드시 IKeyEvent 메소드 오버라이딩한 것이어야 됨
	// ex. Player::Move(KEY_CODE) 같은 IKeyEvent 클래스의 메소드가 아닌 것을 넣는 경우 오류남
	void AddKey(KEY_CODE key, IKeyEvent* const instance)
	{
		m_keyMap.insert(make_pair(key, KeyInfo{KEY_STATE::NONE, instance}));
	}
};