#pragma once

// KEY ��
enum KEY_CODE
{
	KEY_LEFT = VK_LEFT, KEY_RIGHT = VK_RIGHT
};

// KEY ����
enum class KEY_STATE
{
	NONE, DOWN, RELEASED
};

// Ű �Է� �ݹ��Լ� ����� ���� �������̽�
class IKeyEvent
{
	friend class KeyManager;

protected:
	virtual ~IKeyEvent() {}
};

typedef void (IKeyEvent::*KEY_CALLBACK)(KEY_CODE);

// Ű����, ���콺 �Է� ó�� Ŭ����
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