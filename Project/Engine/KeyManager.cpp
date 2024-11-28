#include "pch.h"
#include "KeyManager.h"
#include "Engine.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
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
				key.second.state = KEY_STATE::DOWN;
				key.second.instance->OnKeyDown(key.first);
			}
			// �ȴ���
			else
			{
				if (key.second.state == KEY_STATE::DOWN) key.second.state = KEY_STATE::RELEASED;
				else if (key.second.state == KEY_STATE::RELEASED) key.second.state = KEY_STATE::NONE;
			}
		}
	}
	// �����찡 ��Ŀ�� ���� �ƴ�
	else
	{
		for (auto& key : m_keyMap)
		{
			key.second.state = KEY_STATE::NONE;
		}
	}
}