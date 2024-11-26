#include "pch.h"
#include "PathManager.h"

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

void PathManager::Init()
{
	// .exe ���� ��� �˾Ƴ���
	char curDir[256];
	GetModuleFileNameA(nullptr, curDir, 256); // \Output\bin\.exe
	GetParentPath(curDir);
	GetParentPath(curDir);

	// $(SolutionDir)Output
	m_contentPath = curDir;
	m_contentPath += "\\Contents\\";
}

void PathManager::GetParentPath(char* path)
{
	// �θ� ���͸��� �̵�
	for (size_t i = strlen(path) - 1; i > 0; --i)
	{
		if (path[i] == '\\')
		{
			path[i] = '\0';
			break;
		}
	}
}