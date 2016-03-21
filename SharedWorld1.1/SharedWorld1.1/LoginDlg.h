#pragma once

#include "MyEdit.h"
#include "MyButton.h"
#include "RegisterDlg.h"
#include "afxwin.h"
// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedMfcbutton1();
private:
	CMyEdit account_edit;
	CMyEdit passwd_edit;
	CRegisterDlg  registerDlg;
	bool IsExistReg;
public:
	virtual BOOL OnInitDialog();
	MyButton m_minbtn_login;
	MyButton m_closebtn_login;
	MyButton m_regbtn_login;
	MyButton m_findpasswdbtn_login;
	MyButton m_loginbtn_login;
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg void OnBnClickedMfcbutton3();
	afx_msg void OnBnClickedMfcbutton4();
private:
	CStatic m_focus;
};

