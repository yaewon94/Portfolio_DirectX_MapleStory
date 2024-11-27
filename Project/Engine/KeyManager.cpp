#include "pch.h"
#include "KeyManager.h"
#include "Engine.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

void KeyManager::Init()
{
	AddKey(KEY_LEFT);
	AddKey(KEY_RIGHT);
}

void KeyManager::Tick()
{
	// �����찡 ��Ŀ�� ���϶�
	if (Engine::GetInstance()->IsFocused())
	{
		for (auto& key : m_keyMap)
		{
			// �̹� �����ӿ� �ش� Ű�� ����
			if (GetAsyncKeyState(key.first) & 0x8001)
			{
				if (key.second == KEY_STATE::NONE) key.second = KEY_STATE::TAP;
				else if (key.second == KEY_STATE::TAP) key.second = KEY_STATE::DOWN;

				// TODO : ���� KEY���� ȣ���ϴ� �Լ� �Ϲ�ȭ �ϱ�
			}
			// �ȴ���
			else
			{
				if (key.second == KEY_STATE::TAP || key.second == KEY_STATE::DOWN) key.second = KEY_STATE::RELEASED;
				else if (key.second == KEY_STATE::RELEASED) key.second = KEY_STATE::NONE;
			}
		}
	}
	// �����찡 ��Ŀ�� ���� �ƴ�
	else
	{
		for (auto& key : m_keyMap)
		{
			key.second = KEY_STATE::NONE;
		}
	}
}