// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Exception.h"
#include "SharedSession.h"
#include "TransactionManager.h"
#include "Client.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent),
	IsExistReg(false)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, account_edit);
	DDX_Control(pDX, IDC_EDIT3, passwd_edit);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_minbtn_login);
	DDX_Control(pDX, IDC_MFCBUTTON3, m_closebtn_login);
	DDX_Control(pDX, IDC_MFCBUTTON4, m_regbtn_login);
	DDX_Control(pDX, IDC_MFCBUTTON5, m_findpasswdbtn_login);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_loginbtn_login);
	DDX_Control(pDX, IDC_STATICNO, m_focus);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CLoginDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CLoginDlg::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CLoginDlg::OnBnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CLoginDlg::OnBnClickedMfcbutton4)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


LRESULT CLoginDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//鼠标的坐标在客户区么？在的话就把它当成标题栏
	return CDialogEx::OnNcHitTest(point);
}

//Login
void CLoginDlg::OnBnClickedMfcbutton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString account;
	CString password;
	account_edit.GetWindowText(account);
	passwd_edit.GetWindowText(password);
	if (account.GetLength() < 3)
	{
		::AfxMessageBox("用户名不能小于3位",MB_OK, 0);
		account_edit.SetWindowText("");
		return;
	}

	if (password.GetLength() < 6)
	{
		::AfxMessageBox("密码不能小于6位", MB_OK, 0);
		passwd_edit.SetWindowText("");
		return;
	}

	try{
		SharedSession* ss = Singleton<Client>::Instance().GetSharedSession();
		ss->Clear();
		ss->SetCmd(CMD_LOGIN);
		ss->SetAttribute("name", string(account.GetBuffer(0)));
		ss->SetAttribute("pass", string(password.GetBuffer(0)));

		Singleton<TransactionManager>::Instance().DoAction(*ss);

		if (ss->GetErrorCode() == 0)
		{
			::AfxMessageBox("登录成功", MB_OK, 0);
			this->OnOK();
		}
		else
		{
			::AfxMessageBox(ss->GetErrorMsg().c_str(), MB_OK, 0);
			return;
		}
	}
	catch (Exception& e)
	{
		::AfxMessageBox(e.what(), MB_OK, 0);
	}

	this->OnOK();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	account_edit.SetWindowText(_T("用户名"));
	passwd_edit.SetWindowText(_T("密  码"));
	account_edit.setType(NORMAL);
	passwd_edit.setType(PASSWD);
	m_focus.SetFocus();
	return false;

}

//最小化窗口
void CLoginDlg::OnBnClickedMfcbutton2()
{
	// TODO:  在此添加控件通知处理程序代码
	this->ShowWindow(SW_SHOWMINIMIZED);
}


//关闭窗口
void CLoginDlg::OnBnClickedMfcbutton3()
{
	// TODO:  在此添加控件通知处理程序代码
	exit(1);
}

//register
void CLoginDlg::OnBnClickedMfcbutton4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!IsExistReg)
	{
		registerDlg.Create(IDD_REGISTER_DIALOG);
		registerDlg.ShowWindow(SW_SHOW);
		IsExistReg = true;
	}
	else
	{
		registerDlg.ShowWindow(SW_SHOW);
	}
	
}
