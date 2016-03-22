#include "stdafx.h"
#include "UpLoadFileThread.h"
#include "SharedSession.h"
#include "Singleton.h"
#include "TransactionManager.h"
#include "Exception.h"

UpLoadFileThread::UpLoadFileThread()
{
}


UpLoadFileThread::~UpLoadFileThread()
{
}


void UpLoadFileThread::SetUserName(CString userName)
{
	this->m_userName = userName;
}

void UpLoadFileThread::SetFilePath(CString filePath)
{
	this->m_filePath = filePath;
}

void UpLoadFileThread::SetFileName(CString filename)
{
	this->m_fileName = filename;
}

void UpLoadFileThread::Run()
{
	try{
		std::shared_ptr<SharedSession> ss(new SharedSession);
		//SharedSession* ss = new SharedSession;
		ss->Clear();
		ss->SetCmd(CMD_UPLOAD_FILE_RESOURCE);
		ss->SetAttribute("username", m_userName.GetBuffer(0));
		ss->SetAttribute("dirname", m_filePath.GetBuffer(0));
		ss->SetAttribute("filename", m_fileName.GetBuffer(0));
		Singleton<TransactionManager>::Instance().DoAction(*ss);
	}
	catch (Exception& e)
	{
		::AfxMessageBox(e.what(), MB_OK, 0);
		return;
	}
}
