#include "pch.h"
#include "RandomManager.h"
#include <stdlib.h>
#include <ctime>

RandomManager::RandomManager()
{
}

RandomManager::~RandomManager()
{
}

int RandomManager::GetRandom(int min, int max)
{
	srand((UINT)time(nullptr));
	return rand() % (max + 1 - min) + min;
}