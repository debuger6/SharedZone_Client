#pragma once
#include "JThread.h"
using namespace PUBLIC;
class DownLoadFileThread :
	public JThread
{
public:
	DownLoadFileThread();
	~DownLoadFileThread();
	void Run();
	CString file_userName;
	CString file_path;
	CString save_path;
	void SetUserName(CString userName);
	void SetFilePath(CString filePath);
	void SetSavePath(CString savePath);

};

