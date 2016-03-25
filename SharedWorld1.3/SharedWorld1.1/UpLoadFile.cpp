#include "stdafx.h"
#include "UpLoadFile.h"
#include "CharSetConvert.h"
#include "Logging.h"
#include "JUtil.h"
#define MAX_SIZE 6553

using namespace PUBLIC;
using namespace CMD;


UpLoadFile::UpLoadFile()
{
}


UpLoadFile::~UpLoadFile()
{
}

void UpLoadFile::SendFile(const char* buf, uint16 len, SharedSession& session, FILE *fp, int32 flag)
{
	JOutStream jos;

	// 包头命令
	uint16 cmd = CMD_UPLOAD_FILE_RESOURCE;
	jos << cmd;

	// 预留两个字节包头len（包体+包尾长度）
	size_t lengthPos = jos.Length();
	jos.Skip(2);
	jos << session.GetAttribute("username");
	jos << session.GetAttribute("dirname");
	jos << session.GetAttribute("filename");
	jos << flag;
	jos.AppendWithLen(buf, len);

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
}

void UpLoadFile::Execute(SharedSession& session)
{
	int32 flag = 0;

	FILE *fp = fopen(session.GetAttribute("filename").c_str(), "rb");
	CFileStatus fileStatus;
	if (CFile::GetStatus(session.GetAttribute("filename").c_str(), fileStatus))
	{
		file_size = fileStatus.m_size;
	}

	if (NULL == fp)
	{
		AfxMessageBox("打开文件失败");
		return;
	}
	char buffer[MAX_SIZE];
	memset(buffer, 0, MAX_SIZE * sizeof(char));
	uint32 len = 0;
	while ((len = fread(buffer, sizeof(char), MAX_SIZE, fp)) > 0)
	{	
		SendFile(buffer, len, session, fp, flag);
		flag++;
		memset(buffer, 0, MAX_SIZE * sizeof(char));
	}
	string content = "end";
	flag = -1;
	SendFile(content.c_str(), content.length(), session, fp, flag);
	fclose(fp);
}