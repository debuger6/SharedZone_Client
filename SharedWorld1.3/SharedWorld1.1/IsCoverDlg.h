#pragma once

#include "Resource.h"
// CIsCoverDlg 对话框

class CIsCoverDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIsCoverDlg)

public:
	CIsCoverDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIsCoverDlg();

public:
	bool GetIsCover();

// 对话框数据
	enum { IDD = IDD_ISCOVERDIALOG };

private:
	bool m_IsCover;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
