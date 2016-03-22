// ClientChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "ClientChatDlg.h"
#include "afxdialogex.h"


// CClientChatDlg 对话框

IMPLEMENT_DYNAMIC(CClientChatDlg, CDialogEx)

CClientChatDlg::CClientChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientChatDlg::IDD, pParent)
{

}

CClientChatDlg::~CClientChatDlg()
{
}

void CClientChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_userName_btn);
	DDX_Control(pDX, IDC_EDIT1, m_chatContent_edit);
	DDX_Control(pDX, IDC_EDIT2, m_sendContent_edit);
}


BEGIN_MESSAGE_MAP(CClientChatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientChatDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CClientChatDlg 消息处理程序


//发送
void CClientChatDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CString sendContent;
	m_sendContent_edit.GetWindowText(sendContent);
	if (sendContent.GetLength() > 0)
	{
		m_sendContent_edit.SetWindowTextA("");
		m_chatContent += "\r\n\r\n" + m_userName + ":\r\n    " + sendContent;
		m_chatContent_edit.SetWindowTextA(m_chatContent);
	}
}

void CClientChatDlg::SetPeerName(CString peerName)
{
	m_peerName = peerName;
}


BOOL CClientChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_userName_btn.GetWindowTextA(m_userName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
