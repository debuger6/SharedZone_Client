// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Exception.h"
#include "SharedSession.h"
#include "TransactionManager.h"
#include "Client.h"
#include "Server.h"

// CLoginDlg �Ի���

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
	
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_NCHITTEST()
	
	
	ON_WM_PAINT()
	
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoginDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CLoginDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CLoginDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


LRESULT CLoginDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//���������ڿͻ���ô���ڵĻ��Ͱ������ɱ�����
	return CDialogEx::OnNcHitTest(point);
}




BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	account_edit.SetWindowText(_T("�û���"));
	passwd_edit.SetWindowText(_T("��  ��"));
	account_edit.setType(NORMAL);
	passwd_edit.setType(PASSWD);
	
	
	//����ť�޸�ΪBS_OWNERDRAW���,���������Ч
	GetDlgItem(IDC_BUTTON2)->ModifyStyle(0, BS_OWNERDRAW, 0);
	//�󶨿ؼ�IDC_BUTTON1����CMyButton����Ӧ���غ���DrawItem()
	m_regbtn_login.Attach(IDC_BUTTON2, this);
	//����Button Down�ı���ɫ
	m_regbtn_login.SetDownColor(RGB(236, 236, 236));
	//����Button Up�ı���ɫ
	m_regbtn_login.SetUpColor(RGB(236, 236, 236));

	GetDlgItem(IDC_BUTTON1)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_findpasswdbtn_login.Attach(IDC_BUTTON1, this);
	m_findpasswdbtn_login.SetDownColor(RGB(236, 236, 236));
	m_findpasswdbtn_login.SetUpColor(RGB(236, 236, 236));

	GetDlgItem(IDC_BUTTON3)->ModifyStyle(0, BS_OWNERDRAW, 0);
	::SetTextColor(::GetDC(GetDlgItem(IDC_BUTTON3)->GetSafeHwnd()), RGB(255, 255, 255));
	m_loginbtn_login.Attach(IDC_BUTTON3, this);
	m_loginbtn_login.SetDownColor(RGB(15, 100, 212));
	m_loginbtn_login.SetUpColor(RGB(41, 129, 242));

	GetDlgItem(IDC_BUTTON4)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_minbtn_login.Attach(IDC_BUTTON4, this);
	m_minbtn_login.SetDownColor(RGB(255,255,255));
	m_minbtn_login.SetUpColor(RGB(245, 104, 61));
	

	GetDlgItem(IDC_BUTTON5)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_closebtn_login.Attach(IDC_BUTTON5, this);
	m_closebtn_login.SetDownColor(RGB(255, 0, 0));
	m_closebtn_login.SetUpColor(RGB(245, 104, 61));
	return false;

}



void CLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CFile m_file("login.jpg", CFile::modeRead);
		//��ȡ�ļ�����
		DWORD m_filelen = m_file.GetLength();
		//�ڶ��Ϸ���ռ�
		HGLOBAL m_hglobal = GlobalAlloc(GMEM_MOVEABLE, m_filelen);

		LPVOID pvdata = NULL;
		//�����ѿռ�,��ȡָ��ѿռ��ָ��
		pvdata = GlobalLock(m_hglobal);

		//���ļ����ݶ���������
		m_file.Read(pvdata, m_filelen);

		IStream*  m_stream;

		GlobalUnlock(m_hglobal);

		//�ڶ��д���������
		CreateStreamOnHGlobal(m_hglobal, TRUE, &m_stream);

		//����������ͼ��
		OleLoadPicture(m_stream, m_filelen, TRUE, IID_IPicture, (LPVOID*)&m_picture);
		m_stream->Release();

		m_picture->get_Width(&m_width);// ��ߣ�MM_HIMETRIC ģʽ����λ��0.01����
		m_picture->get_Height(&m_height);
		m_IsShow = TRUE;
		m_file.Close();

		if (m_IsShow == TRUE){
			CRect rect;
			GetClientRect(rect);
			int nW, nH;
			nW = (int)(rect.Width());
			nH = (int)(rect.Height());
			m_picture->Render(dc, 0, 0, nW, nH, 0, m_height, m_width, -m_height, &rect);
		}
		CDialogEx::OnPaint();
	}
}

//ע��
void CLoginDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

//��¼
void CLoginDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString account;
	CString password;
	account_edit.GetWindowText(account);
	passwd_edit.GetWindowText(password);
	if (account.GetLength() < 3)
	{
		::AfxMessageBox("�û�������С��3λ", MB_OK, 0);
		account_edit.SetWindowText("");
		return;
	}

	if (password.GetLength() < 6)
	{
		::AfxMessageBox("���벻��С��6λ", MB_OK, 0);
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
			::AfxMessageBox("��¼�ɹ�", MB_OK, 0);
			theApp.setAccount(account);
			theApp.setActiveUsers(ss->GetActiveUsers());

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
		return;
	}

	this->OnOK();
}

//��С��
void CLoginDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_SHOWMINIMIZED);
}

//�رմ���
void CLoginDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	exit(1);
}
