#pragma once

class PathManager final : public Singleton<PathManager>
{
	SINGLETON(PathManager);

private:
	string m_contentPath;

public:
	void Init();

public:
	const string& GetContentPath() { return m_contentPath; }

private:
	void GetParentPath(char* path);
};