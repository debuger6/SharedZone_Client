
// SharedWorld1.1.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "LoginDlg.h"

// CSharedWorld11App:
// 有关此类的实现，请参阅 SharedWorld1.1.cpp
//

class CSharedWorld11App : public CWinApp
{
public:
	CSharedWorld11App();

// 重写
public:
	virtual BOOL InitInstance();
private:
	CLoginDlg loginDlg;

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CSharedWorld11App theApp;