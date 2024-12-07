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
	// 윈도우가 포커싱 중일때
	if (Engine::GetInstance()->IsFocused())
	{
		for (auto& key : m_keyMap)
		{
			KeyInfo& info = key.second;

			// 이번 프레임에 해당 키가 눌림
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
			// 안눌림
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
	// 윈도우가 포커싱 중이 아님
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