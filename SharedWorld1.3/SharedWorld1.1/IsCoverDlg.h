#pragma once

#include "Resource.h"
// CIsCoverDlg �Ի���

class CIsCoverDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIsCoverDlg)

public:
	CIsCoverDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIsCoverDlg();

public:
	bool GetIsCover();

// �Ի�������
	enum { IDD = IDD_ISCOVERDIALOG };

private:
	bool m_IsCover;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
