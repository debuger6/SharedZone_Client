#pragma once
#include "JThread.h"
using namespace PUBLIC;
class UpLoadFileThread :
	public JThread
{
public:
	UpLoadFileThread();
	~UpLoadFileThread();
	void Run();

	void SetUserName(CString userName);
	void SetFilePath(CString filePath);
	void SetFileName(CString filename);

private:
	CString m_userName;
	CString m_filePath;
	CString m_fileName;
};

