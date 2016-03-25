#include "stdafx.h"
#include "DownLoadFile.h"
#include "CharSetConvert.h"
#include "Logging.h"
#include "JUtil.h"
#include "IsCoverDlg.h"
#define MAX_SIZE 65536

using namespace PUBLIC;
using namespace CMD;


DownLoadFile::DownLoadFile()
{
}


DownLoadFile::~DownLoadFile()
{
}

void DownLoadFile::Execute(SharedSession& session)
{
	JOutStream jos;

	// 包头命令
	uint16 cmd = CMD_DOWN_LOAD_RESOURCE;
	jos << cmd;

	// 预留两个字节包头len（包体+包尾长度）
	size_t lengthPos = jos.Length();
	jos.Skip(2);
	jos << session.GetAttribute("username");
	jos << session.GetAttribute("filepath");
	string savePath = session.GetAttribute("savepath");

	//判断文件是否存在
	if (PathFileExists(savePath.c_str()))
	{
		CIsCoverDlg isCoverDlg;
		isCoverDlg.DoModal();
		if (isCoverDlg.GetIsCover())
			DeleteFile(savePath.c_str());		
		else
			return;
	}
	
	// 包头len
	size_t tailPos = jos.Length();
	jos.Reposition(lengthPos);
	jos << static_cast<uint16>(tailPos + 8 - sizeof(RequestHead)); // 包体长度 + 包尾长度

	// 包尾
	jos.Reposition(tailPos);
	// 计算包尾
	unsigned char hash[16];
	MD5 md5;
	md5.MD5Make(hash, (const unsigned char*)jos.Data(), jos.Length());
	for (int i = 0; i<8; ++i)
	{
		hash[i] = hash[i] ^ hash[i + 8];
		hash[i] = hash[i] ^ ((cmd >> (i % 2)) & 0xff);
	}
	jos.WriteBytes(hash, 8);
	session.Send(jos.Data(), jos.Length());	// 发送请求包

	session.Recv2();	// 接收应答包
	//JInStream jis(session.GetBuffer(), session.GetLen_());
	
	string content(session.GetBuffer() + sizeof uint32, session.GetLen_());
	FILE *fp = fopen(savePath.c_str(), "ab");
	if (NULL == fp)
	{
		AfxMessageBox("打开文件失败");
		return;
	}
	while (content != "end")
	{
		//将传过来文件内容写入文件
		fwrite(session.GetBuffer() + sizeof uint32, session.GetLen_(), 1, fp);
		session.Recv2();
		content = string(session.GetBuffer() + sizeof uint32, session.GetLen_());
	}
	fclose(fp);	
}