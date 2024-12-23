#pragma once
#define MAX_BUFFER_SIZE 255


static class PathManager final
{
private:
	static char projPath[MAX_BUFFER_SIZE];
	static char includePath[MAX_BUFFER_SIZE];

private:
	PathManager() {}
	~PathManager() {}

public:
	static int Init();

public:
	static const char* const GetProjectPath() { return projPath; }
	static const char* const GetIncludePath() { return includePath; }
};