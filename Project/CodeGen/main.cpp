#include "pch.h"
#include "PathManager.h"

vector<string> g_fileNameList;

int main()
{
	PathManager::Init();
	string strProjPath = PathManager::GetProjectPath();
	string strCppPath = strProjPath + "\\Scripts\\ScriptManager.cpp";
	string strHeaderPath = strProjPath + "\\Scripts\\ScriptManager.h";

	// ���� �����ϴ� ��� ��ũ��Ʈ �˾Ƴ���
	string strScriptIncludePath = PathManager::GetIncludePath();
	string strScriptCode = strScriptIncludePath + "Scripts\\";

	LPWIN32_FIND_DATAA tData = {};
	HANDLE handle = FindFirstFileA(string(strScriptCode + "\\*.h").c_str(), tData);

	if (handle == INVALID_HANDLE_VALUE)
	{
		cout << "��ũ��Ʈ ������� �˾Ƴ��� ����";
		return -1;
	}

	// ���� ����Ʈ ���
	FILE* exceptFile = nullptr;
	fopen_s(&exceptFile, "exceptlist.txt", "r");
	if (exceptFile == nullptr)
	{
		cout << "exceptlist.txt �� ���� ����";
		return -1;
	}

	vector<string> exceptList;
	char exceptName[MAX_BUFFER_SIZE] = "";

	while (true)
	{
		int iLen = fscanf_s(exceptFile, "%s", exceptName, MAX_BUFFER_SIZE);
		if (iLen == -1) break;

		exceptList.push_back(exceptName);
	}
	fclose(exceptFile);

	while (true)
	{
		// ���ϸ��� ���ؼ� ������������ ��
		bool isException = false;
		for (size_t i = 0; i < exceptList.size(); ++i)
		{
			if (!strcmp(tData->cFileName, exceptList[i].c_str()))
			{
				isException = true;
				break;
			}
		}

		if (!isException)
		{
			g_fileNameList.push_back(string(tData->cFileName).substr(0, strlen(tData->cFileName) - 1));
		}

		if (!FindNextFileA(handle, tData)) break;
	}

	FindClose(handle);

	// ������ CodeGen �� ����ɶ� üũ�ص� ��ũ��Ʈ���� ���
	FILE* scriptListFile = nullptr;
	fopen_s(&scriptListFile, "ScriptList.txt", "r");
	if (scriptListFile == nullptr)
	{
		cout << "ScriptList.txt ���� ����";
		return -1;
	}

	char scriptName[MAX_BUFFER_SIZE] = {};
	vector<string> scriptList;
	while (true)
	{
		int iLen = fscanf_s(scriptListFile, "%s", scriptName, MAX_BUFFER_SIZE);
		if (iLen == -1) break;

		scriptList.push_back(scriptName);
	}
	fclose(scriptListFile);


	if (g_fileNameList.size() == scriptList.size())
	{
		bool isSame = true;
		for (UINT i = 0; i < g_fileNameList.size(); ++i)
		{
			if (g_fileNameList[i] != scriptList[i])
			{
				isSame = false;
				break;
			}
		}

		// ���� ��ϰ�, ���� ��ũ��Ʈ ����� ���� ��ġ�Ѵ�(������� ����)
		if (isSame) return 0;
	}


	FILE* managerFile = NULL;

	//=================
	// ScriptManager. h �ۼ�
	//=================
	fopen_s(&managerFile, strHeaderPath.c_str(), "w");
	fprintf_s(managerFile, "#pragma once\n\n");
	fprintf_s(managerFile, "#include <vector>\n");
	fprintf_s(managerFile, "#include <string>\n\n");
	for (UINT i = 0; i < g_fileNameList.size(); ++i)
	{
		string strScriptUpperName = "";
		for (UINT j = 1; j < g_fileNameList[i].size(); ++j)
		{
			strScriptUpperName += toupper(g_fileNameList[i][j]);
		}

		fprintf_s(managerFile, "\t");
		fprintf_s(managerFile, strScriptUpperName.c_str());
		fprintf_s(managerFile, ",\n");
	}
	fprintf_s(managerFile, "};\n\n");

	fprintf_s(managerFile, "using namespace std;\n\n");
	fprintf_s(managerFile, "class Script;\n\n");

	fprintf_s(managerFile, "class ScriptManager\n{\n");
	fprintf_s(managerFile, "public:\n\tstatic void GetScriptInfo(vector<string>& _vec);\n");
	fprintf_s(managerFile, "\tstatic Script * GetScript(const string& _strScriptName);\n");

	fclose(managerFile);

	//====================
	// ScriptManager.cpp �ۼ�
	//====================
	fopen_s(&managerFile, strCppPath.c_str(), "w");

	// ��� �Է�
	fprintf_s(managerFile, "#include \"pch.h\"\n");
	fprintf_s(managerFile, "#include \"ScriptManager.h\"\n\n");

	for (UINT i = 0; i < g_fileNameList.size(); ++i)
	{
		fprintf_s(managerFile, "#include \"");
		fprintf_s(managerFile, g_fileNameList[i].c_str());
		fprintf_s(managerFile, ".h\"\n");
	}

	// GetScriptInfo() �ۼ�
	fprintf_s(managerFile, "\nvoid ScriptManager::GetScriptInfo(vector<wstring>& _vec)\n{\n");

	for (UINT i = 0; i < g_fileNameList.size(); ++i)
	{
		fprintf_s(managerFile, "\t_vec.push_back(\"");
		fprintf_s(managerFile, g_fileNameList[i].c_str());
		fprintf_s(managerFile, "\");\n");
	}
	fprintf_s(managerFile, "}\n\n");


	// GetScript() �ۼ�
	fprintf_s(managerFile, "Script * ScriptManager::GetScript(const string& _strScriptName)\n{\n");

	for (UINT i = 0; i < g_fileNameList.size(); ++i)
	{
		fprintf_s(managerFile, "\tif (\"");
		fprintf_s(managerFile, g_fileNameList[i].c_str());
		fprintf_s(managerFile, "\" == _strScriptName)\n");
		fprintf_s(managerFile, "\t\treturn new ");
		fprintf_s(managerFile, g_fileNameList[i].c_str());
		fprintf_s(managerFile, ";\n");
	}
	fprintf_s(managerFile, "\treturn nullptr;\n}\n\n");

	// ������ ����� ���ϱ����� ���� ����
	fopen_s(&managerFile, "ScriptList.txt", "w");

	for (UINT i = 0; i < g_fileNameList.size(); ++i)
	{
		fprintf_s(managerFile, g_fileNameList[i].c_str());
		fprintf_s(managerFile, "\n");
	}

	fclose(managerFile);

	return 0;
}