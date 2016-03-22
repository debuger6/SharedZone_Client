#pragma once
#include "afxwin.h"
#include "MyButton.h"
#include "afxbutton.h"


// CRegisterDlg 对话框

class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegisterDlg();

// 对话框数据
	enum { IDD = IDD_REGISTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyEdit m_accountedit_reg;
	CMyEdit m_passwordedit_reg;
	CMyEdit m_repasswordedit_reg;
	
	CMyButton m_closebtn_reg;
	CMyButton m_registerbtn_reg;
	virtual BOOL OnInitDialog();
	
	
	afx_msg LRESULT OnNcHitTest(CPoint point);

	

private:
	IPicture *m_picture;
	OLE_XSIZE_HIMETRIC m_width;
	OLE_YSIZE_HIMETRIC m_height;
	BOOL m_IsShow;
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonCloseReg();
	afx_msg void OnBnClickedButtonRegster();
};
