#pragma once
#include "IKeyEvent.h"

typedef void (IKeyEvent::*KEY_CALLBACK)(KEY_CODE);

// 키보드, 마우스 입력 처리 클래스
class KeyManager final : public Singleton<KeyManager>
{
	SINGLETON(KeyManager);

private:
	// KEY 상태
	enum class KEY_STATE
	{
		NONE, DOWN, RELEASED
	};

	// KEY 정보
	struct KeyInfo
	{
		KEY_STATE state;
		IKeyEvent* instance = nullptr; // TODO : IKeyEvent* 하나당 여러개의 KEY_CODE 가지는 식으로 구조 변경 생각해보기
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