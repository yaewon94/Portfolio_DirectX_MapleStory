#pragma once

// KEY ��
enum KEY_CODE
{
	KEY_LEFT = VK_LEFT, KEY_RIGHT = VK_RIGHT,
	KEY_ALT = VK_MENU
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
	virtual void OnKeyDown(KEY_CODE key) = 0;
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
	};

private:
	unordered_map<KEY_CODE, KeyInfo> m_keyMap;

public:
	void Tick();

public:
	// @KEY_CALLBACK : �ݵ�� IKeyEvent �޼ҵ� �������̵��� ���̾�� ��
	// ex. Player::Move(KEY_CODE) ���� IKeyEvent Ŭ������ �޼ҵ尡 �ƴ� ���� �ִ� ��� ������
	void AddKey(KEY_CODE key, IKeyEvent* const instance)
	{
		m_keyMap.insert(make_pair(key, KeyInfo{KEY_STATE::NONE, instance}));
	}
};