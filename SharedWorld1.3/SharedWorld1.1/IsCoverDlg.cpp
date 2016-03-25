// IsCoverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "IsCoverDlg.h"
#include "afxdialogex.h"


// CIsCoverDlg �Ի���

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


// CIsCoverDlg ��Ϣ�������


void CIsCoverDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_IsCover = false;
	CDialogEx::OnCancel();
}


void CIsCoverDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_IsCover = true;
	CDialogEx::OnOK();
}
