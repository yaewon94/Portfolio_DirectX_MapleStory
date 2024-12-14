#include "pch.h"
#include "StringParser.h"

float ToFloat(const string& str)
{
	float result = 0.0f;
	float exp = 1.f;
	float sign = 1.f;
	string::const_iterator iter = str.cbegin();

	// 부호
	if (*iter == '-')
	{
		sign = -1.f;
		++iter;
	}

	// 소수점 윗부분
	for (; iter != str.cend(); ++iter)
	{
		if (*iter == '.')
		{
			++iter;
			break;
		}

		char c = *iter - '0';
		if (c < 0 || c > 9) assert(nullptr);

		result *= exp;
		exp *= 10.f;

		if (result + (float)c - result < 0) assert(nullptr); // overflow
		result += (float)c;
	}

	// 소수점 아랫부분
	exp = 0.1f;
	for (; iter != str.cend(); ++iter)
	{
		auto test = *iter;
		char c = *iter - '0';
		if (c < 0 || c > 9) assert(nullptr);

		result += (float)c * exp;
		exp *= 0.1f;
		if (exp > 1.f) break; // underflow
	}

	return result * sign;
}

int ToInteger(const string& str)
{
	int result = 0;
	int exp = 1;
	int sign = 1;
	string::const_iterator iter = str.cbegin();

	// 부호
	if (*iter == '-')
	{
		sign = -1;
		++iter;
	}

	// 값
	for (; iter != str.cend(); ++iter)
	{
		char c = *iter - '0';
		if (c < 0 || c > 9) assert(nullptr);

		result *= exp;
		exp *= 10.f;

		if (result + (int)c - result < 0) assert(nullptr); // overflow
		result += (int)c;
	}

	return result * sign;
}