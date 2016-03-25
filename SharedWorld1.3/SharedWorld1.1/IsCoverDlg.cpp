// IsCoverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "IsCoverDlg.h"
#include "afxdialogex.h"


// CIsCoverDlg 对话框

IMPLEMENT_DYNAMIC(CIsCoverDlg, CDialogEx)

CIsCoverDlg::CIsCoverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIsCoverDlg::IDD, pParent)
{

}

CIsCoverDlg::~CIsCoverDlg()
{
}

void CIsCoverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

bool CIsCoverDlg::GetIsCover()
{
	return m_IsCover;
}


BEGIN_MESSAGE_MAP(CIsCoverDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CIsCoverDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CIsCoverDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CIsCoverDlg 消息处理程序


void CIsCoverDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	m_IsCover = false;
	CDialogEx::OnCancel();
}


void CIsCoverDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	m_IsCover = true;
	CDialogEx::OnOK();
}
