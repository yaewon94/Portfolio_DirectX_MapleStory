#pragma once
#define SIZE_BUFFER 30

// ���� ����, �б�/���� ��� Ŭ����
class FileManager final : public Singleton<FileManager>
{
	SINGLETON(FileManager);

public:
	// ������ : data�� �޴� ����ü�� char[] Ÿ�Ը� ���� �� �ְ�, �迭 ũ�⵵ SIZE_BUFFER�� �����Ǿ�� ��
	// @ Key != "" : ���� �ϳ��� Entity�� ���� �� ���� ��, Key���� ��ġ�ϴ� �κи� ������ ����
	int Read(const string& FullPath, void* data, size_t size, const string& Key = "");
};