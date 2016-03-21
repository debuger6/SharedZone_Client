#pragma once
#include "afxwin.h"
#include "MyButton.h"
#include "afxbutton.h"


// CRegisterDlg �Ի���

class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegisterDlg();

// �Ի�������
	enum { IDD = IDD_REGISTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyEdit m_accountedit_reg;
	CMyEdit m_passwordedit_reg;
	CMyEdit m_repasswordedit_reg;
	MyButton m_minbtn_reg;
	MyButton m_closebtn_reg;
	MyButton m_registerbtn_reg;
	virtual BOOL OnInitDialog();
	CMFCButton m_focus;
	afx_msg void OnBnClickedMfcbutton3();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedMfcbutton2();
};
