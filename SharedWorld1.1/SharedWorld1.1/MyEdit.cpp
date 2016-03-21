// MyEdit.cpp : ʵ���ļ�
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



// CMyEdit ��Ϣ�������




void CMyEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	
	// TODO:  �ڴ˴������Ϣ����������
	
	this->GetWindowText(initString);
	if (type == NORMAL && (initString == "�û���" || initString == "�������û���"))
	{
		this->SetWindowText(_T(""));
	}
	else if (type == PASSWD && (initString == "��  ��" || initString == "����������" || initString == "����ȷ��"))
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

	// TODO:  �ڴ˴������Ϣ����������
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
