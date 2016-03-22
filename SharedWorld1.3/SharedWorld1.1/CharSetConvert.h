#pragma once
#include "stdafx.h"
#include <string>

using namespace std;
class CharSetConvert
{
public:
	static bool MultiToUtf8(const string& multiText,  string& utf8Text)
	{
		// 把输入转换为Unicode
		int size = ::MultiByteToWideChar(CP_ACP,
			0,
			multiText.c_str(),
			-1,
			NULL,
			0);
		if (0 == size)
		{
			return false;
		}

		wchar_t* wszBuffer = new wchar_t[size + 1];
		::ZeroMemory(wszBuffer, (size + 1) * sizeof(wchar_t));

		if (0 == ::MultiByteToWideChar(CP_ACP,
			0,
			multiText.c_str(),
			-1,
			wszBuffer,
			size + 1))
		{
			delete[] wszBuffer;
			return false;
		}

		// Unicode->UTF8的转换
		size = ::WideCharToMultiByte(CP_UTF8,
			0,
			wszBuffer,
			-1,
			NULL,
			0,
			NULL,
			NULL);
		if (0 == size)
		{
			delete[] wszBuffer;
			return false;
		}

		char* szBuffer = new char[size + 1];
		::ZeroMemory(szBuffer, (size + 1) * sizeof(char));

		if (0 == ::WideCharToMultiByte(CP_UTF8,
			0,
			wszBuffer,
			-1,
			szBuffer,
			size + 1,
			NULL,
			NULL))
		{
			delete[] wszBuffer;
			delete[] szBuffer;
			return false;
		}
		utf8Text = szBuffer;
		delete[] wszBuffer;
		delete[] szBuffer;
		return true;
	}
};