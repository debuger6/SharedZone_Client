
// SharedWorld1.1Dlg.h : 头文件
//

#pragma once

#include "afxwin.h"
#include "afxcmn.h"
#include "ServerThread.h"
#include "Resource.h"
#include "ChatDlg.h"
#include "afxbutton.h"
#include "MyButton.h"
#include "ClientChatDlg.h"
#include "XProgressCtrl.h"
#include <boost/shared_ptr.hpp>
#include <map>

using namespace std;
// CSharedWorld11Dlg 对话框
class CSharedWorld11Dlg : public CDialogEx
{
// 构造
public:
	CSharedWorld11Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SHAREDWORLD11_DIALOG1 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	
	void setAccount(CString account);
	void InitUserList();
	void ShowFileTree();
private:
	
	CListCtrl m_userlist;
	ServerThread* st;
	std::map<CString, CChatDlg*> chatDlgs;
	std::map<CString, boost::shared_ptr<CClientChatDlg>> clientChatDlgs;
	std::vector<CString> files;
	//CChatDlg chatDlg;
	
public:
	afx_msg void OnNMDblclkUserList(NMHDR *pNMHDR, LRESULT *pResult);
	void SetChatEditText(CString username, CString sendContent);
	void SetFiles(const vector<CString>& files);
	void InitImageList();
	void DirTraverse(CString root);
private:
	CEdit m_showpanel_edit;
	CEdit m_sendpanel_edit;
	CMyButton m_message_btn;
	CMyButton m_myDownLoad_btn;
	CMyButton m_myUpLoad_btn;
	CMyButton m_upLoad_btn;
	CMyButton m_upLoadFile_btn;
	CMyButton m_send_btn;
	CMyButton m_min_btn;
	CMyButton m_close_btn;
	CMyButton m_userName_btn;

	CString m_chatContent;
	CString m_userName;
	CChatDlg *chatDlg;
	CImageList m_ImageList;

	CString username;
	CXProgressCtrl* xp;
	int m_currentItem;

private:
	IPicture *m_picture;
	OLE_XSIZE_HIMETRIC m_width;
	OLE_YSIZE_HIMETRIC m_height;
	BOOL m_IsShow;
public:
	afx_msg void OnBnClickedButtonUpload();
	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonUploadfile();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCheckResource();
};
