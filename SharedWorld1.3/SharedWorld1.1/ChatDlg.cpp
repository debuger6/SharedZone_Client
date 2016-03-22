// ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "ChatDlg.h"
#include "afxdialogex.h"
#include "Exception.h"
#include "SharedSession.h"
#include "TransactionManager.h"
#include "Client.h"
#include "Server.h"
#include "DownLoadFileThread.h"

// CChatDlg 对话框

IMPLEMENT_DYNAMIC(CChatDlg, CDialogEx)

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatDlg::IDD, pParent)
{

}

CChatDlg::~CChatDlg()
{
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE1, m_dirTree);
	DDX_Control(pDX, IDC_USERNAME_TITLE, m_username_title);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &CChatDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CChatDlg::OnBnClickedMfcbutton1)
	ON_WM_NCHITTEST()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CChatDlg::OnNMDblclkTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CChatDlg::OnNMRClickTree1)
	ON_COMMAND(ID_32771, &CChatDlg::On32771)
END_MESSAGE_MAP()


// CChatDlg 消息处理程序


void CChatDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


BOOL CChatDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
			return TRUE;//截获消息 
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	m_img.Create(GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		ILC_COLOR24, 50, 50);
	m_img.SetBkColor(GetSysColor(COLOR_WINDOW));
	m_img.Add(ExtractIcon(AfxGetApp()->m_hInstance, "shell32.dll ", 4));
	m_img.Add(ExtractIcon(AfxGetApp()->m_hInstance, "shell32.dll ", 1));
	
	
	
	// TODO:  在此添加额外的初始化
	m_dirTree.SetBkColor(RGB(0, 250, 255));//设置m_mytree的背景色
	m_dirTree.SetImageList(&m_img, TVSIL_NORMAL);
	
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


//初始化文件树
void CChatDlg::InitFileTree(std::vector<CString>& files)
{
	if (!IsInitFileTree)
	{
		m_dirTree.InsertItem("C:", 0, 0);
		m_dirTree.InsertItem("D:", 0, 0);
		m_dirTree.InsertItem("E:", 0, 0);
		m_dirTree.InsertItem("F:", 0, 0);
		m_dirTree.InsertItem("G:", 0, 0);
		m_dirTree.InsertItem("H:", 0, 0);
		m_dirTree.InsertItem("J:", 0, 0);
		IsInitFileTree = true;
	}
	else
	{
		m_dirTree.DeleteAllItems();
		m_dirTree.InsertItem("C:", 0, 0);
		m_dirTree.InsertItem("D:", 0, 0);
		m_dirTree.InsertItem("E:", 0, 0);
		m_dirTree.InsertItem("F:", 0, 0);
		m_dirTree.InsertItem("G:", 0, 0);
		m_dirTree.InsertItem("H:", 0, 0);
		m_dirTree.InsertItem("J:", 0, 0);
		
	}
	
	HTREEITEM RootItem = m_dirTree.GetRootItem();
	HTREEITEM hParentItem;
	
	for (auto iter = files.begin(); iter != files.end(); ++iter)
	{
		RootItem = m_dirTree.GetRootItem();
			int pos = iter->Find("/");
			CString strLeft = iter->Left(pos);

			while (RootItem)
			{
				if (strLeft == m_dirTree.GetItemText(RootItem))
				{
					*iter = iter->Right(iter->GetLength() - pos - 1);
					LoadPicFiles(m_dirTree, *iter, RootItem);
					break;
				}
					
				else
				{
					RootItem = m_dirTree.GetNextItem(RootItem, TVGN_NEXT);

				}
			}
			
	}	

	m_username_title.SetWindowTextA( m_userName + "的共享资源");
}

void CChatDlg::LoadPicFiles(CTreeCtrl& nTreeCtrl, CString nFilePath, HTREEITEM nRoot)
{

	// 判断nPicFolder是目录还是文件  
	// 如果是文件  
	//     直接将文件插入到树控件中 nTreeCtrl.InsertItem(nPicFolder,nRoot);  
	// 如果是目录  
	//     获取nPicFolder的第一层目录  
	//     判断nRoot目录下是否已经有此层目录  
	//     如果有此层目录  
	//         递归插入其他  
	//     如果无此层目录  
	//         插入此层目录，然后递归插入其他  


	CString nSubFolder;     //首层目录  
	CString nSubFilePath;   //去掉首层目录后的文件名  
	BOOL IsExist = FALSE;



	int nIndex = -1;
	nIndex = nFilePath.Find("/");

	if (nIndex >= 0) //目录  
	{
		nSubFolder = nFilePath.Left(nIndex);
		nSubFilePath = nFilePath.Right(nFilePath.GetLength() - nIndex - 1);

		HTREEITEM nSubRoot = NULL;
		if (nTreeCtrl.ItemHasChildren(nRoot))
			nSubRoot = nTreeCtrl.GetChildItem(nRoot);
		CString str;
		BOOL  bExist = FALSE;
		while (nSubRoot)
		{
			str = nTreeCtrl.GetItemText(nSubRoot);

			if (str.CompareNoCase(nSubFolder) == 0)
			{

				bExist = TRUE;
				break;
			}

			nSubRoot = nTreeCtrl.GetNextSiblingItem(nSubRoot);
		}

		if (!bExist)
		{

			nSubRoot = nTreeCtrl.InsertItem(nSubFolder, nRoot);

			LoadPicFiles(nTreeCtrl, nSubFilePath, nSubRoot);
		}
		else{
			LoadPicFiles(nTreeCtrl, nSubFilePath, nSubRoot);
		}
	}
	else 
	{
		nTreeCtrl.InsertItem(nFilePath, 1, 1, nRoot, 0);
	}
}

BOOL CChatDlg::AddParentFolder(CString nParentFolder[10], CString nParent)
{
	for (int i = 9; i>0; i--)
		nParentFolder[i] = nParentFolder[i - 1];
	nParentFolder[0] = nParent;
	return TRUE;
}

CString CChatDlg::AllCString(CString nParentFolder[10])
{
	CString nAllCString = "";
	for (int i = 0; i<10; i++)
	{
		if (nParentFolder[i] == "") break;
		nAllCString += "\\" + nParentFolder[i];
	}
	return nAllCString;
}


void CChatDlg::SetTreeListStyle()
{
	DWORD dwStyle = GetWindowLong(m_dirTree.m_hWnd, GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	SetWindowLong(m_dirTree.m_hWnd, GWL_STYLE, dwStyle);
}

CString CChatDlg::GetItemPath(CTreeCtrl* pCtrl, HTREEITEM hItem)
{
	CString nSelItemName = pCtrl->GetItemText(hItem);

	HTREEITEM parentItem = pCtrl->GetParentItem(hItem);

	if (parentItem == NULL) //hItem即为根目录  
		return nSelItemName;

	//清空OLD  
	for (int i = 0; i<10; i++) m_OldParentFolder[i] = "";

	//m_OldParentFolder 记录上一个节点的父节点    
	for (int i = 0; i<10; i++)
		m_OldParentFolder[i] = m_ParentFolder[i];

	//m_ParentFolder 记录当前节点的父亲节点    
	for (int i = 0; i<10; i++)
		m_ParentFolder[i] = L"";

	CString itemPath;
	CString parentFolder = nSelItemName;

	//将parentFolder添加到m_ParentFolder[0],其他值依次后移    
	AddParentFolder(m_ParentFolder, parentFolder);



	// m_PicFolder 为根节点对应的名字    
	while (parentItem != NULL&&pCtrl->GetItemText(parentItem).Compare(""))
	{
		parentFolder = pCtrl->GetItemText(parentItem);
		AddParentFolder(m_ParentFolder, parentFolder);
		parentItem = pCtrl->GetParentItem(parentItem);

	}

	itemPath.Format("%s%s", "", AllCString(m_ParentFolder));

	//清空OLD  
	for (int i = 0; i<10; i++) m_OldParentFolder[i] = L"";
	//清空     
	for (int i = 0; i<10; i++)
		m_ParentFolder[i] = L"";

	return itemPath;

}



void CChatDlg::OnBnClickedMfcbutton1()
{
	// TODO:  在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
}


LRESULT CChatDlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//鼠标的坐标在客户区么？在的话就把它当成标题栏
	return CDialogEx::OnNcHitTest(point);
}


void CChatDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	

	*pResult = 0;
}

void CChatDlg::SetUserName(CString userName)
{
	m_userName = userName;
}
CString CChatDlg::GetUserName()
{
	return m_userName;
}


void CChatDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	CPoint point;
	GetCursorPos(&point);//获得鼠标点击的位置
	ScreenToClient(&point);//转化为客户坐标
	MapWindowPoints(&m_dirTree, &point, 1);
	UINT uFlags;
	CurrentItem = m_dirTree.HitTest(point, &uFlags);//获得当前点击节点的ITEM
	if ((CurrentItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		
		m_dirTree.Select(CurrentItem, TVGN_CARET);
		ClientToScreen(&point);
		CMenu m_Menu1;
		m_Menu1.LoadMenu(IDR_MENU1);
		CMenu *m_SubMenu1 = m_Menu1.GetSubMenu(0);

		m_SubMenu1->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	*pResult = 0;
}


//下载资源
void CChatDlg::On32771()
{
	// TODO:  在此添加命令处理程序代码
	CString filePath = GetItemPath(&m_dirTree, CurrentItem);
	CString fileName = m_dirTree.GetItemText(CurrentItem);
	if (filePath.Left(1) == "\\")
		filePath = filePath.Right(filePath.GetLength() - 1);
	filePath.Replace("\\", "/");
	//filePath.Replace(":","\\:");

	char szPath[MAX_PATH];     //存放选择的目录路径 
	CString dirPath;

	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择资源保存的目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		AfxMessageBox(szPath);
		DownLoadFileThread* downLoadFileThread = new DownLoadFileThread();
		downLoadFileThread->SetUserName(m_userName);
		downLoadFileThread->SetFilePath(filePath);
		downLoadFileThread->SetSavePath((CString)szPath + "/" + fileName);
		downLoadFileThread->SetAutoDel(true);
		downLoadFileThread->Start();
	}
	else
		AfxMessageBox("无效的目录，请重新选择");
	
}
