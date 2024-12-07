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
			KeyInfo& info = key.second;

			// �̹� �����ӿ� �ش� Ű�� ����
			if (GetAsyncKeyState(key.first) & 0x8001)
			{
				if (info.state == KEY_STATE::DOWN)
				{
					info.instance->OnKeyDown(key.first);
				}
				else if (info.state == KEY_STATE::TAP)
				{
					info.state = KEY_STATE::DOWN;
					info.instance->OnKeyDown(key.first);
				}
				else if (info.state == KEY_STATE::NONE)
				{
					info.state = KEY_STATE::TAP;
					info.instance->OnKeyTap(key.first);
				}
			}
			// �ȴ���
			else
			{
				if (info.state == KEY_STATE::DOWN || info.state == KEY_STATE::TAP)
				{
					info.state = KEY_STATE::RELEASED;
					info.instance->OnKeyReleased(key.first);
				}
				else if (info.state == KEY_STATE::RELEASED)
				{
					info.state = KEY_STATE::NONE;
				}
			}
		}
	}
	// �����찡 ��Ŀ�� ���� �ƴ�
	else
	{
		for (auto& key : m_keyMap)
		{
			KeyInfo& info = key.second;
			if (info.state == KEY_STATE::DOWN || info.state == KEY_STATE::TAP)
			{
				info.state = KEY_STATE::RELEASED;
				info.instance->OnKeyReleased(key.first);
			}
			else if (info.state == KEY_STATE::RELEASED)
			{
				info.state = KEY_STATE::NONE;
			}
		}
	}
}