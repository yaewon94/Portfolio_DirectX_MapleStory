#pragma once
#include "IKeyEvent.h"

typedef void (IKeyEvent::*KEY_CALLBACK)(KEY_CODE);

// Ű����, ���콺 �Է� ó�� Ŭ����
class KeyManager final : public Singleton<KeyManager>
{
	SINGLETON(KeyManager);

private:
	// KEY ����
	enum class KEY_STATE
	{
		NONE, DOWN, RELEASED
	};

	// KEY ����
	struct KeyInfo
	{
		KEY_STATE state;
		IKeyEvent* instance = nullptr; // TODO : IKeyEvent* �ϳ��� �������� KEY_CODE ������ ������ ���� ���� �����غ���
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