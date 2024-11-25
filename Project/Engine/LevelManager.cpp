#include "pch.h"
#include "LevelManager.h"
#include "Level.h"

LevelManager::LevelManager() 
	: m_curLevel(nullptr)
{
}

LevelManager::~LevelManager()
{
	if (m_curLevel != nullptr)
	{
		delete m_curLevel;
		m_curLevel = nullptr;
	}
}

int LevelManager::Init()
{
	m_curLevel = new Level("test level");
	m_curLevel->Init();

	return S_OK;
}

void LevelManager::Tick()
{
	m_curLevel->Tick();
	m_curLevel->FinalTick();
}