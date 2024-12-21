#pragma once

class RandomManager final : public Singleton<RandomManager>
{
	SINGLETON(RandomManager)

public:
	int GetRandom(int min, int max);
};