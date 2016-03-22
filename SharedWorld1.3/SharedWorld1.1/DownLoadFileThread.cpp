#include "stdafx.h"
#include "DownLoadFileThread.h"
#include "SharedSession.h"
#include "Singleton.h"
#include "Singleton.h"
#include "TransactionManager.h"
#include "Exception.h"


DownLoadFileThread::DownLoadFileThread()
{
}


DownLoadFileThread::~DownLoadFileThread()
{
}

void DownLoadFileThread::SetUserName(CString userName)
{
	this->file_userName = userName;
}

void DownLoadFileThread::SetFilePath(CString filePath)
{
	this->file_path = filePath;
}

void DownLoadFileThread::SetSavePath(CString savePath)
{
	this->save_path = savePath;
}

void DownLoadFileThread::Run()
{
	try{
		std::shared_ptr<SharedSession> ss(new SharedSession());
		//SharedSession *ss = new SharedSession;
		ss->Clear();
		ss->SetCmd(CMD_DOWN_LOAD_RESOURCE);
		
		ss->SetAttribute("username", file_userName.GetBuffer(0));
		ss->SetAttribute("filepath", file_path.GetBuffer(0));
		ss->SetAttribute("savepath", save_path.GetBuffer(0));
		Singleton<TransactionManager>::Instance().DoAction(*ss);


	}
	catch (Exception& e)
	{
		::AfxMessageBox(e.what(), MB_OK, 0);
		
		return;
	}
}
