#pragma once
#include "afxwin.h"


// CClientChatDlg 对话框

class CClientChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientChatDlg)

public:
	CClientChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClientChatDlg();

// 对话框数据
	enum { IDD = IDD_CLIENTCHAT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void SetPeerName(CString peerName);
private:
	CButton m_userName_btn;
	CEdit m_chatContent_edit;
	CEdit m_sendContent_edit;
	CString m_peerName;
	CString m_chatContent;
	CString m_userName;
public:
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};
