#include "pch.h"
#include "PathManager.h"

char PathManager::projPath[MAX_BUFFER_SIZE] = {};
char PathManager::includePath[MAX_BUFFER_SIZE] = {};

int PathManager::Init()
{
	// ���� ���͸� : $(SolutionPath)\CodeGen
	// �ַ�� ���͸� ���ϱ�
	char solutionPath[MAX_BUFFER_SIZE] = {};
	GetCurrentDirectoryA(sizeof(solutionPath)/sizeof(char), solutionPath);
	size_t iCount = 0;
	for (size_t i = strlen(solutionPath) - 1; i > 0; --i)
	{
		if (solutionPath[i] == '\\')
		{
			solutionPath[i + 1] = 0;
			++iCount;
		}

		if (iCount == 1) break;
	}

	// ���ҽ� ���͸� ���ϱ� : $(SolutionDir)\Output\Contents
	char resourcePath[MAX_BUFFER_SIZE] = {};
	strcpy_s(resourcePath, sizeof(resourcePath)/sizeof(char), solutionPath);
	strcat_s(resourcePath, "\\Output\\Contents\\");

	// Include ���� ���͸� ���ϱ� : $(SolutionDir)\External\Include
	GetCurrentDirectoryA(sizeof(includePath)/sizeof(char), includePath);
	iCount = 0;
	for (size_t i = strlen(includePath) - 1; i > 0; --i)
	{
		if (includePath[i] == '\\')
		{
			includePath[i + 1] = 0;
			++iCount;
		}

		if (iCount == 1) break;
	}
	strcat_s(includePath, "\\External\\Include\\");


	// ������Ʈ ���� ��� ���ϱ� : $(SolutionDir)\Project
	GetCurrentDirectoryA(sizeof(projPath)/sizeof(char), projPath);
	iCount = 0;
	for (size_t i = strlen(projPath) - 1; i > 0; --i)
	{
		if (projPath[i] == '\\')
		{
			projPath[i + 1] = 0;
			++iCount;
		}

		if (iCount == 1) break;
	}
	strcat_s(projPath, "\\Project\\");

	return 0;
}