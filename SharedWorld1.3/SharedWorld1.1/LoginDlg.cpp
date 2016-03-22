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
#include "Server.h"

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
	
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_NCHITTEST()
	
	
	ON_WM_PAINT()
	
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoginDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CLoginDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CLoginDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


LRESULT CLoginDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//鼠标的坐标在客户区么？在的话就把它当成标题栏
	return CDialogEx::OnNcHitTest(point);
}




BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	account_edit.SetWindowText(_T("用户名"));
	passwd_edit.SetWindowText(_T("密  码"));
	account_edit.setType(NORMAL);
	passwd_edit.setType(PASSWD);
	
	
	//将按钮修改为BS_OWNERDRAW风格,其他风格无效
	GetDlgItem(IDC_BUTTON2)->ModifyStyle(0, BS_OWNERDRAW, 0);
	//绑定控件IDC_BUTTON1与类CMyButton，响应重载函数DrawItem()
	m_regbtn_login.Attach(IDC_BUTTON2, this);
	//设置Button Down的背景色
	m_regbtn_login.SetDownColor(RGB(236, 236, 236));
	//设置Button Up的背景色
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
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CFile m_file("login.jpg", CFile::modeRead);
		//获取文件长度
		DWORD m_filelen = m_file.GetLength();
		//在堆上分配空间
		HGLOBAL m_hglobal = GlobalAlloc(GMEM_MOVEABLE, m_filelen);

		LPVOID pvdata = NULL;
		//锁定堆空间,获取指向堆空间的指针
		pvdata = GlobalLock(m_hglobal);

		//将文件数据读区到堆中
		m_file.Read(pvdata, m_filelen);

		IStream*  m_stream;

		GlobalUnlock(m_hglobal);

		//在堆中创建流对象
		CreateStreamOnHGlobal(m_hglobal, TRUE, &m_stream);

		//利用流加载图像
		OleLoadPicture(m_stream, m_filelen, TRUE, IID_IPicture, (LPVOID*)&m_picture);
		m_stream->Release();

		m_picture->get_Width(&m_width);// 宽高，MM_HIMETRIC 模式，单位是0.01毫米
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

//注册
void CLoginDlg::OnBnClickedButton1()
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

//登录
void CLoginDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CString account;
	CString password;
	account_edit.GetWindowText(account);
	passwd_edit.GetWindowText(password);
	if (account.GetLength() < 3)
	{
		::AfxMessageBox("用户名不能小于3位", MB_OK, 0);
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

//最小化
void CLoginDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	this->ShowWindow(SW_SHOWMINIMIZED);
}

//关闭窗口
void CLoginDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	exit(1);
}
