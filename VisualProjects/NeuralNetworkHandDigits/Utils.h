#pragma once

#define UTILS_FUNCS_DLL __declspec(dllexport)

#include <string>

#include "windows.h"

class Utils
{
public:
	UTILS_FUNCS_DLL static std::string GetExePath()
	{
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		return std::string(buffer).substr(0, pos);
	}

	UTILS_FUNCS_DLL static bool IsInVisual()
	{
		char buffer[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, buffer);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::string path = std::string(buffer).substr(0, pos);
		pos = path.find_last_of("\\/");
		path = path.substr(pos + 1, path.size() - pos);

		return (path == "VisualProjects");
	}
};
