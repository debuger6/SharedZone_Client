// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "Exception.h"
#include "SharedSession.h"
#include "TransactionManager.h"
#include "Client.h"

// CRegisterDlg �Ի���

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


// CRegisterDlg ��Ϣ�������


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_accountedit_reg.SetWindowText(_T("�������û���"));
	m_passwordedit_reg.SetWindowText(_T("����������"));
	m_repasswordedit_reg.SetWindowTextA("����ȷ��");

	m_accountedit_reg.setType(NORMAL);
	m_passwordedit_reg.setType(PASSWD);
	m_repasswordedit_reg.setType(PASSWD);

	m_focus.SetFocus();
	return false;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//register
void CRegisterDlg::OnBnClickedMfcbutton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString account, password, repassword;
	m_accountedit_reg.GetWindowTextA(account);
	m_passwordedit_reg.GetWindowTextA(password);
	m_repasswordedit_reg.GetWindowTextA(repassword);

	if (account.GetLength() < 3)
	{
		::AfxMessageBox("�û�������С��3λ", MB_OK, 0);
		return;
	}

	if (password.GetLength() < 6)
	{
		::AfxMessageBox("���벻��С��6λ", MB_OK, 0);
		return;
	}
	else{
		if (password != repassword)
		{
			::AfxMessageBox("�����������벻һ�£�����������", MB_OK, 0);
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
			::AfxMessageBox("ע��ɹ�", MB_OK, 0);
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//���������ڿͻ���ô���ڵĻ��Ͱ������ɱ�����
	return CDialogEx::OnNcHitTest(point);
}


void CRegisterDlg::OnBnClickedMfcbutton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_SHOWMINIMIZED);
}


void CRegisterDlg::OnBnClickedMfcbutton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
