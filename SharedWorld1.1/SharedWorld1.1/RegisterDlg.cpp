// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "Exception.h"
#include "SharedSession.h"
#include "TransactionManager.h"
#include "Client.h"

// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterDlg::IDD, pParent)
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, m_accountedit_reg);
	DDX_Control(pDX, IDC_EDIT5, m_passwordedit_reg);
	DDX_Control(pDX, IDC_EDIT6, m_repasswordedit_reg);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_minbtn_reg);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_closebtn_reg);
	DDX_Control(pDX, IDC_MFCBUTTON3, m_registerbtn_reg);
	DDX_Control(pDX, IDC_MFCBUTTON5, m_focus);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CRegisterDlg::OnBnClickedMfcbutton3)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CRegisterDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CRegisterDlg::OnBnClickedMfcbutton2)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_accountedit_reg.SetWindowText(_T("请输入用户名"));
	m_passwordedit_reg.SetWindowText(_T("请输入密码"));
	m_repasswordedit_reg.SetWindowTextA("密码确认");

	m_accountedit_reg.setType(NORMAL);
	m_passwordedit_reg.setType(PASSWD);
	m_repasswordedit_reg.setType(PASSWD);

	m_focus.SetFocus();
	return false;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


//register
void CRegisterDlg::OnBnClickedMfcbutton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CString account, password, repassword;
	m_accountedit_reg.GetWindowTextA(account);
	m_passwordedit_reg.GetWindowTextA(password);
	m_repasswordedit_reg.GetWindowTextA(repassword);

	if (account.GetLength() < 3)
	{
		::AfxMessageBox("用户名不得小于3位", MB_OK, 0);
		return;
	}

	if (password.GetLength() < 6)
	{
		::AfxMessageBox("密码不得小于6位", MB_OK, 0);
		return;
	}
	else{
		if (password != repassword)
		{
			::AfxMessageBox("两次密码输入不一致，请重新输入", MB_OK, 0);
			return;
		}
	}

	//start register
	try{
		SharedSession* ss = Singleton<Client>::Instance().GetSharedSession();
		ss->Clear();
		ss->SetCmd(CMD_REGISTER);
		ss->SetAttribute("name", string(account.GetBuffer(0)));
		ss->SetAttribute("pass", string(password.GetBuffer(0)));

		Singleton<TransactionManager>::Instance().DoAction(*ss);

		if (ss->GetErrorCode() == 0)
		{
			::AfxMessageBox("注册成功", MB_OK, 0);
			return;
			//this->OnOK();
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


LRESULT CRegisterDlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//鼠标的坐标在客户区么？在的话就把它当成标题栏
	return CDialogEx::OnNcHitTest(point);
}


void CRegisterDlg::OnBnClickedMfcbutton1()
{
	// TODO:  在此添加控件通知处理程序代码
	this->ShowWindow(SW_SHOWMINIMIZED);
}


void CRegisterDlg::OnBnClickedMfcbutton2()
{
	// TODO:  在此添加控件通知处理程序代码
	OnOK();
}
