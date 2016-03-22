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
	
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)

	ON_WM_NCHITTEST()
	
	
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_REG, &CRegisterDlg::OnBnClickedButtonCloseReg)
	ON_BN_CLICKED(IDC_BUTTON_REGSTER, &CRegisterDlg::OnBnClickedButtonRegster)
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

	GetDlgItem(IDC_BUTTON_REGSTER)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_registerbtn_reg.Attach(IDC_BUTTON_REGSTER, this);
	m_registerbtn_reg.SetDownColor(RGB(255, 0, 0));
	m_registerbtn_reg.SetUpColor(RGB(70, 144, 251));

	GetDlgItem(IDC_BUTTON_CLOSE_REG)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_closebtn_reg.Attach(IDC_BUTTON_CLOSE_REG, this);
	m_closebtn_reg.SetDownColor(RGB(255, 0, 0));
	m_closebtn_reg.SetUpColor(RGB(0, 206, 185));
	
	return false;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



LRESULT CRegisterDlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//鼠标的坐标在客户区么？在的话就把它当成标题栏
	return CDialogEx::OnNcHitTest(point);
}






void CRegisterDlg::OnPaint()
{
	CPaintDC dc(this);
	CFile m_file("register.jpg", CFile::modeRead);
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


void CRegisterDlg::OnBnClickedButtonCloseReg()
{
	// TODO:  在此添加控件通知处理程序代码
	OnOK();
}


void CRegisterDlg::OnBnClickedButtonRegster()
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
