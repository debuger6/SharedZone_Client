
// SharedWorld1.1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharedWorld1.1.h"
#include "SharedWorld1.1Dlg.h"
#include "afxdialogex.h"
#include "Exception.h"
#include "SharedSession.h"
#include "TransactionManager.h"
#include "Client.h"
#include "Server.h"
#include "UpLoadFileThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSharedWorld11Dlg �Ի���



CSharedWorld11Dlg::CSharedWorld11Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSharedWorld11Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	st = new ServerThread();
}

void CSharedWorld11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_LIST1, m_userlist);
	DDX_Control(pDX, IDC_EDIT1, m_showpanel_edit);

	DDX_Control(pDX, IDC_EDIT2, m_sendpanel_edit);
}

BEGIN_MESSAGE_MAP(CSharedWorld11Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_WM_NCHITTEST()
	
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSharedWorld11Dlg::OnNMDblclkUserList)

	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CSharedWorld11Dlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_MIN, &CSharedWorld11Dlg::OnBnClickedButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSharedWorld11Dlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSharedWorld11Dlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_UPLOADFILE, &CSharedWorld11Dlg::OnBnClickedButtonUploadfile)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CSharedWorld11Dlg::OnLvnItemchangedList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CSharedWorld11Dlg::OnNMRClickList1)
	ON_COMMAND(ID_32774, &CSharedWorld11Dlg::OnCheckResource)
END_MESSAGE_MAP()


// CSharedWorld11Dlg ��Ϣ�������

BOOL CSharedWorld11Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//CProgressCtrl *pProgCtrl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	//pProgCtrl->SetRange(0, 200);//���ý�������Χ  
	//pProgCtrl->SetWindowPos(NULL, 5,5,5,5, 0);

	GetDlgItem(IDC_BUTTON_MSG)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_message_btn.Attach(IDC_BUTTON_MSG, this);
	m_message_btn.SetDownColor(RGB(227, 222, 193));
	m_message_btn.SetUpColor(RGB(227, 222, 193));

	GetDlgItem(IDC_BUTTON_MYDOWNLOAD)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_myDownLoad_btn.Attach(IDC_BUTTON_MYDOWNLOAD, this);
	m_myDownLoad_btn.SetDownColor(RGB(208, 208, 208));
	m_myDownLoad_btn.SetUpColor(RGB(227, 222, 193));

	GetDlgItem(IDC_BUTTON_MYUPLOAD)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_myUpLoad_btn.Attach(IDC_BUTTON_MYUPLOAD, this);
	m_myUpLoad_btn.SetDownColor(RGB(208, 208, 208));
	m_myUpLoad_btn.SetUpColor(RGB(227, 222, 193));

	GetDlgItem(IDC_BUTTON_UPLOAD)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_upLoad_btn.Attach(IDC_BUTTON_UPLOAD, this);
	m_upLoad_btn.SetDownColor(RGB(208, 208, 208));
	m_upLoad_btn.SetUpColor(RGB(227, 222, 193));
	
	GetDlgItem(IDC_BUTTON_UPLOADFILE)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_upLoadFile_btn.Attach(IDC_BUTTON_UPLOADFILE, this);
	m_upLoadFile_btn.SetDownColor(RGB(208, 208, 208));
	m_upLoadFile_btn.SetUpColor(RGB(227, 222, 193));

	GetDlgItem(IDC_BUTTON_SEND)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_send_btn.Attach(IDC_BUTTON_SEND, this);
	m_send_btn.SetDownColor(RGB(208, 208, 208));
	m_send_btn.SetUpColor(RGB(230, 223, 197));

	GetDlgItem(IDC_BUTTON_NAME)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_userName_btn.Attach(IDC_BUTTON_NAME, this);
	m_userName_btn.SetDownColor(RGB(128, 115, 107));
	m_userName_btn.SetUpColor(RGB(128, 115, 107));

	GetDlgItem(IDC_BUTTON_MIN)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_min_btn.Attach(IDC_BUTTON_MIN, this);
	m_min_btn.SetDownColor(RGB(255, 255, 255));
	m_min_btn.SetUpColor(RGB(128, 115, 107));

	GetDlgItem(IDC_BUTTON_CLOSE)->ModifyStyle(0, BS_OWNERDRAW, 0);
	m_close_btn.Attach(IDC_BUTTON_CLOSE, this);
	m_close_btn.SetDownColor(RGB(255, 0, 0));
	m_close_btn.SetUpColor(RGB(128, 115, 107));

	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);
	m_userlist.InsertColumn(0, _T("�����û�"), LVCFMT_LEFT, 260);
	
	/*m_userlist.InsertColumn(1, _T("no2 "), LVCFMT_LEFT, 80);
	m_userlist.InsertColumn(2, _T("no3 "), LVCFMT_LEFT, 80);*/
	InitImageList();
	m_userlist.SetImageList(&m_ImageList, LVSIL_SMALL);

	m_userName_btn.SetWindowTextA(theApp.getAccount());
	m_userName = theApp.getAccount();
	InitUserList();
	st->SetAutoDel(true);
	st->Start();

	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSharedWorld11Dlg::InitImageList()
{
	
	//m_ImageList.Create(GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),ILC_COLOR24, 50, 50);
	m_ImageList.Create(32, 32, ILC_COLOR24, 50, 50);
	m_ImageList.SetBkColor(GetSysColor(COLOR_WINDOW));
	HICON icon[6];
	icon[0] = AfxGetApp()->LoadIcon(IDI_ICON1);
	icon[1] = AfxGetApp()->LoadIcon(IDI_ICON2);
	icon[2] = AfxGetApp()->LoadIcon(IDI_ICON3);
	icon[3] = AfxGetApp()->LoadIcon(IDI_ICON4);
	icon[4] = AfxGetApp()->LoadIcon(IDI_ICON5);
	icon[5] = AfxGetApp()->LoadIcon(IDI_ICON6);

	for (int i = 0; i < 6; ++i)
	{
		m_ImageList.Add(icon[i]);
	}
	//m_ImageList.Add(m_hIcon);
	
}

void CSharedWorld11Dlg::InitUserList()
{
	srand((unsigned)time(NULL));
	m_userlist.DeleteAllItems();
	for (int i = 0; i < theApp.getActiveUsers().size(); ++i)
	{
		m_userlist.InsertItem(i, theApp.getActiveUsers()[i].c_str(), rand() % 6);
		//m_userlist.SetItem(0, 1, LVIF_TEXT | LVIF_IMAGE, _T("123"), 0, 0, 0, 0);//�ڵ�һ�еڶ��м����1��ͼ��
	}
}

void CSharedWorld11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSharedWorld11Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CFile m_file("main.jpg", CFile::modeRead);
		//��ȡ�ļ�����
		DWORD m_filelen = m_file.GetLength();
		//�ڶ��Ϸ���ռ�
		HGLOBAL m_hglobal = GlobalAlloc(GMEM_MOVEABLE, m_filelen);

		LPVOID pvdata = NULL;
		//�����ѿռ�,��ȡָ��ѿռ��ָ��
		pvdata = GlobalLock(m_hglobal);

		//���ļ����ݶ���������
		m_file.Read(pvdata, m_filelen);

		IStream*  m_stream;

		GlobalUnlock(m_hglobal);

		//�ڶ��д���������
		CreateStreamOnHGlobal(m_hglobal, TRUE, &m_stream);

		//����������ͼ��
		OleLoadPicture(m_stream, m_filelen, TRUE, IID_IPicture, (LPVOID*)&m_picture);
		m_stream->Release();

		m_picture->get_Width(&m_width);// ��ߣ�MM_HIMETRIC ģʽ����λ��0.01����
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSharedWorld11Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSharedWorld11Dlg::SetChatEditText(CString username, CString sendContent)
{
	m_sendpanel_edit.SetWindowTextA("");
	m_chatContent += "\r\n\r\n" + username + ":\r\n    " + sendContent;
	m_showpanel_edit.SetWindowTextA(m_chatContent);
}

void CSharedWorld11Dlg::SetFiles(const vector<CString>& files)
{
	this->files = files;
}


LRESULT CSharedWorld11Dlg::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT nResult = CDialog::OnNcHitTest(point);
	return nResult == HTCLIENT ? HTCAPTION : nResult;//���������ڿͻ���ô���ڵĻ��Ͱ������ɱ�����
	return CDialogEx::OnNcHitTest(point);
}







void CSharedWorld11Dlg::OnNMDblclkUserList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	

	*pResult = 0;
}

//
void CSharedWorld11Dlg::ShowFileTree()
{
	chatDlg->InitFileTree(files);
	chatDlg->ShowWindow(SW_SHOW);
	chatDlgs.insert(pair<CString, CChatDlg*>(username, chatDlg));
}

//����Ŀ¼
void CSharedWorld11Dlg::DirTraverse(CString root)
{
	CFileFind fileFinder;
	if (root.Right(1) != "/")
		root += "/";
	root += "*.*";
	BOOL bFinished = fileFinder.FindFile(root);
	while (bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() && !fileFinder.IsDots())  //����Ŀ¼��ݹ���ô˷���
		{
			DirTraverse(fileFinder.GetFilePath());//�ݹ�
		}
		else if (!fileFinder.IsDirectory() && !fileFinder.IsDots())// �ҵ������ļ�
		{
			CString fileName = fileFinder.GetFilePath(); //�ļ�ȫ��
			AfxMessageBox(fileName);
			//�ϴ��ļ�
			/*try{
				SharedSession* ss = Singleton<Client>::Instance().GetSharedSession();
				ss->Clear();
				ss->SetCmd(CMD_UPLOAD_DIR_RESOURCE);
				ss->SetAttribute("filename", fileName.GetBuffer(0));
				Singleton<TransactionManager>::Instance().DoAction(*ss);
			}
			catch (Exception& e)
			{
				::AfxMessageBox(e.what(), MB_OK, 0);
				return;
			}*/
		}
		
	}
	fileFinder.Close();
}

//�ϴ���Դ
void CSharedWorld11Dlg::OnBnClickedButtonUpload()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString dirPath;

	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ����Ҫ�ϴ���Ŀ¼��";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		DirTraverse(szPath);
	}
	else
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
}


void CSharedWorld11Dlg::OnBnClickedButtonMin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_MINIMIZE);
}


void CSharedWorld11Dlg::OnBnClickedButtonClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	exit(0);
	//SendMessage(WM_CLOSE);
}


//����

void CSharedWorld11Dlg::OnBnClickedButtonSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	
	CString sendContent;
	m_sendpanel_edit.GetWindowText(sendContent);
	if (sendContent.GetLength() > 0)
	{
		m_sendpanel_edit.SetWindowTextA("");
		m_chatContent += "\r\n\r\n" + m_userName + ":\r\n    " + sendContent;
		m_showpanel_edit.SetWindowTextA(m_chatContent);

		try{
			SharedSession* ss = Singleton<Client>::Instance().GetSharedSession();
			ss->Clear();
			ss->SetCmd(CMD_SEND_CONTENT);
			ss->SetAttribute("username", m_userName.GetBuffer(0));
			ss->SetAttribute("sendContent", sendContent.GetBuffer(0));

			Singleton<TransactionManager>::Instance().DoAction(*ss);


		}
		catch (Exception& e)
		{
			::AfxMessageBox(e.what(), MB_OK, 0);
			return;
		}
	}
	else{
		//::AfxMessageBox("�������ݲ���Ϊ��", MB_OK, 0);
		return;
	}
}

//�ϴ��ļ���Դ
void CSharedWorld11Dlg::OnBnClickedButtonUploadfile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strFile;
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT);

	if (dlgFile.DoModal())
	{
		POSITION pos = dlgFile.GetStartPosition();
		while (pos)
		{
			CString dirName = dlgFile.GetFolderPath();
			CString fileName = dlgFile.GetNextPathName(pos);
			
			dirName.Replace("\\", "/");
			fileName.Replace("\\", "/");
			UpLoadFileThread* upLoadFileThread = new UpLoadFileThread();		
			upLoadFileThread->SetUserName(m_userName);
			upLoadFileThread->SetFilePath(dirName);
			upLoadFileThread->SetFileName(fileName);
			upLoadFileThread->SetAutoDel(true);
			upLoadFileThread->Start();
		}
	}
}


void CSharedWorld11Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	if (nItem >= 0 && nItem < m_userlist.GetItemCount())
	{
		username = m_userlist.GetItemText(nItem, 0);
		map<CString, CClientChatDlg*>::iterator itDlg;
		if ((itDlg = clientChatDlgs.find(username)) == clientChatDlgs.end())
		{
			
			CClientChatDlg* cchatDlg = new CClientChatDlg();
			cchatDlg->Create(IDD_CLIENTCHAT_DIALOG);
			cchatDlg->SetPeerName(username);
			clientChatDlgs.insert(make_pair(username, cchatDlg));
			cchatDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			itDlg->second->ShowWindow(SW_SHOW);
		}
	}*/
	*pResult = 0;
}


void CSharedWorld11Dlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMenu   oMenu;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	m_currentItem = nItem;
	if (nItem != -1)
	{
		if (oMenu.LoadMenu(IDR_MENU2))
		{
			CMenu*   pPopup = oMenu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			CPoint   oPoint;
			GetCursorPos(&oPoint);
			SetForegroundWindow();
			pPopup->TrackPopupMenu(
				TPM_LEFTALIGN | TPM_RIGHTBUTTON,
				oPoint.x, oPoint.y, this);
		}
	}
	*pResult = 0;
}


void CSharedWorld11Dlg::OnCheckResource()
{
	// TODO:  �ڴ���������������
	if (m_currentItem >= 0 && m_currentItem<m_userlist.GetItemCount())
	{
		username = m_userlist.GetItemText(m_currentItem, 0);
		map<CString, CChatDlg*>::iterator itDlg;
		
		if ((itDlg = chatDlgs.find(username)) == chatDlgs.end())
		{
			chatDlg = new CChatDlg();
			chatDlg->Create(IDD_CHAT_DIALOG);
			chatDlg->SetUserName(username);
			try{
				SharedSession* ss = Singleton<Client>::Instance().GetSharedSession();
				ss->Clear();
				ss->SetCmd(CMD_GET_RESOURCE);
				ss->SetAttribute("username", username.GetBuffer(0));

				Singleton<TransactionManager>::Instance().DoAction(*ss);
			}
			catch (Exception& e)
			{
				::AfxMessageBox(e.what(), MB_OK, 0);
				return;
			}
		}
		else
		{
			chatDlg->SetUserName(username);
			try{
				SharedSession* ss = Singleton<Client>::Instance().GetSharedSession();  //�����Զ���һ���ļ����ص�session�Ҳ���Ϊ��������ΪҪ�õ����̣߳�������Ҫ����ļ�����session����
				//SharedSession *ss = new SharedSession();
				ss->Clear();
				ss->SetCmd(CMD_GET_RESOURCE);
				ss->SetAttribute("username", username.GetBuffer(0));
				Singleton<TransactionManager>::Instance().DoAction(*ss);
			}
			catch (Exception& e)
			{
				::AfxMessageBox(e.what(), MB_OK, 0);
				return;
			}
			//itDlg->second->ShowWindow(SW_SHOW);
		}

	}
}
