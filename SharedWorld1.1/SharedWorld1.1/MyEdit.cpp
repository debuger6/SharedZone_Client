// MyEdit.cpp : 实现文件
//
#include "stdafx.h"

#include "SharedWorld1.1.h"
#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{

}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CMyEdit 消息处理程序




void CMyEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	
	// TODO:  在此处添加消息处理程序代码
	
	this->GetWindowText(initString);
	if (type == NORMAL && (initString == "用户名" || initString == "请输入用户名"))
	{
		this->SetWindowText(_T(""));
	}
	else if (type == PASSWD && (initString == "密  码" || initString == "请输入密码" || initString == "密码确认"))
	{
		this->SetWindowText(_T(""));
		this->SetPasswordChar(_T('*'));
	}
}

void CMyEdit::setType(int type)
{
	this->type = type;
}


void CMyEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO:  在此处添加消息处理程序代码
	CString text;
	this->GetWindowText(text);
	if (type == NORMAL && text == "")
	{
		this->SetWindowText(initString);
	}
	else if (type == PASSWD && text == "")
	{
		this->SetPasswordChar(NULL);
		this->SetWindowText(initString);
	}
}
