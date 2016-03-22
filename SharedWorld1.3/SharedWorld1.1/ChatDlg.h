#pragma once
#include "afxbutton.h"
#include "afxwin.h"
#include "MyButton.h"
#include "afxcmn.h"
#include <vector>


// CChatDlg �Ի���

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChatDlg();

// �Ի�������
	enum { IDD = IDD_FILE_TREE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	
public:
	afx_msg void OnEnChangeEdit2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	virtual BOOL OnInitDialog();

	void SetTreeListStyle();
	void InitFileTree( std::vector<CString>& files);
	void LoadPicFiles(CTreeCtrl& nTreeCtrl, CString nFilePath, HTREEITEM nRoot);
	BOOL AddParentFolder(CString nParentFolder[10], CString nParent);
	CString AllCString(CString nParentFolder[10]);
	CString GetItemPath(CTreeCtrl* pCtrl, HTREEITEM hItem);
	void SetUserName(CString userName);
	CString GetUserName();
private:
	CTreeCtrl m_dirTree;
	HTREEITEM m_hTreeItemRoot, hSubItem;
	HICON hIcon[3];      // ͼ��������   
	CBitmap m_bitmap;  //����
	CImageList   m_img;
	CString m_ParentFolder[10];
	CString m_OldParentFolder[10];
	CString m_userName;
	bool IsInitFileTree = false;
	HTREEITEM CurrentItem;
public:
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_username_title;
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On32771();
};
