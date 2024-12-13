#include "pch.h"
#include "StringParser.h"

float ToFloat(const string& str)
{
	float result = 0.0f;
	float exp = 1.f;
	string::const_iterator iter = str.cbegin();

	// 소수점 윗부분
	for (; iter != str.cend(); ++iter)
	{
		char c = *iter - '0';
		if (c == '.') break;
		if (c < 0 || c > 9) assert(nullptr);

		result *= exp;
		exp *= 10.f;

		result += (float)c;
	}

	// 소수점 아랫부분
	exp = 0.1f;
	for (; iter != str.cend(); ++iter)
	{
		char c = *iter - '0';
		if (c < 0 || c > 9) assert(nullptr);

		result += (float)c * exp;
		exp *= 0.1f;
	}

	return result;
}