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

private:
	
	CMyEdit passwd_edit;
	CRegisterDlg  registerDlg;
	bool IsExistReg;
public:
	virtual BOOL OnInitDialog();
	CMyEdit account_edit;
	CMyButton m_minbtn_login;
	CMyButton m_closebtn_login;
	CMyButton m_regbtn_login;
	CMyButton m_findpasswdbtn_login;
	CMyButton m_loginbtn_login;
	
	
public:
	afx_msg void OnPaint();
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

private:
	IPicture *m_picture;
	OLE_XSIZE_HIMETRIC m_width;
	OLE_YSIZE_HIMETRIC m_height;
	BOOL m_IsShow;
};

