// ChatDlg.cpp : ʵ���ļ�
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

// CChatDlg �Ի���

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


// CChatDlg ��Ϣ�������


void CChatDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL CChatDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
			return TRUE;//�ػ���Ϣ 
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
	
	
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_dirTree.SetBkColor(RGB(0, 250, 255));//����m_mytree�ı���ɫ
	m_dirTree.SetImageList(&m_img, TVSIL_NORMAL);
	
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//��ʼ���ļ���
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

	m_username_title.SetWindowTextA( m_userName + "�Ĺ�����Դ");
}

void CChatDlg::LoadPicFiles(CTreeCtrl& nTreeCtrl, CString nFilePath, HTREEITEM nRoot)
{

	// �ж�nPicFolder��Ŀ¼�����ļ�  
	// ������ļ�  
	//     ֱ�ӽ��ļ����뵽���ؼ��� nTreeCtrl.InsertItem(nPicFolder,nRoot);  
	// �����Ŀ¼  
	//     ��ȡnPicFolder�ĵ�һ��Ŀ¼  
	//     �ж�nRootĿ¼���Ƿ��Ѿ��д˲�Ŀ¼  
	//     ����д˲�Ŀ¼  
	//         �ݹ��������  
	//     ����޴˲�Ŀ¼  
	//         ����˲�Ŀ¼��Ȼ��ݹ��������  


	CString nSubFolder;     //�ײ�Ŀ¼  
	CString nSubFilePath;   //ȥ���ײ�Ŀ¼����ļ���  
	BOOL IsExist = FALSE;



	int nIndex = -1;
	nIndex = nFilePath.Find("/");

	if (nIndex >= 0) //Ŀ¼  
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

	if (parentItem == NULL) //hItem��Ϊ��Ŀ¼  
		return nSelItemName;

	//���OLD  
	for (int i = 0; i<10; i++) m_OldParentFolder[i] = "";

	//m_OldParentFolder ��¼��һ���ڵ�ĸ��ڵ�    
	for (int i = 0; i<10; i++)
		m_OldParentFolder[i] = m_ParentFolder[i];

	//m_ParentFolder ��¼��ǰ�ڵ�ĸ��׽ڵ�    
	for (int i = 0; i<10; i++)
		m_ParentFolder[i] = L"";

	CString itemPath;
	CString parentFolder = nSelItemName;

	//��parentFolder��ӵ�m_ParentFolder[0],����ֵ���κ���    
	AddParentFolder(m_ParentFolder, parentFolder);



	// m_PicFolder Ϊ���ڵ��Ӧ������    
	while (parentItem != NULL&&pCtrl->GetItemText(parentItem).Compare(""))
	{
		parentFolder = pCtrl->GetItemText(parentItem);
		AddParentFolder(m_ParentFolder, parentFolder);
		parentItem = pCtrl->GetParentItem(parentItem);

	}

	itemPath.Format("%s%s", "", AllCString(m_ParentFolder));

	//���OLD  
	for (int i = 0; i<10; i++) m_OldParentFolder[i] = L"";
	//���     
	for (int i = 0; i<10; i++)
		m_ParentFolder[i] = L"";

	return itemPath;

}



void CChatDlg::OnBnClickedMfcbutton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
}


LRESULT CChatDlg::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//���������ڿͻ���ô���ڵĻ��Ͱ������ɱ�����
	return CDialogEx::OnNcHitTest(point);
}


void CChatDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	

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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CPoint point;
	GetCursorPos(&point);//����������λ��
	ScreenToClient(&point);//ת��Ϊ�ͻ�����
	MapWindowPoints(&m_dirTree, &point, 1);
	UINT uFlags;
	CurrentItem = m_dirTree.HitTest(point, &uFlags);//��õ�ǰ����ڵ��ITEM
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


//������Դ
void CChatDlg::On32771()
{
	// TODO:  �ڴ���������������
	CString filePath = GetItemPath(&m_dirTree, CurrentItem);
	CString fileName = m_dirTree.GetItemText(CurrentItem);
	if (filePath.Left(1) == "\\")
		filePath = filePath.Right(filePath.GetLength() - 1);
	filePath.Replace("\\", "/");
	//filePath.Replace(":","\\:");

	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString dirPath;

	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ����Դ�����Ŀ¼��";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//����ѡ��Ŀ¼�Ի���
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
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
	
}
