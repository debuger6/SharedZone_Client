#pragma once
#include "afxwin.h"


// CClientChatDlg �Ի���

class CClientChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientChatDlg)

public:
	CClientChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CClientChatDlg();

// �Ի�������
	enum { IDD = IDD_CLIENTCHAT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
