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

	// ��ͷ����
	uint16 cmd = CMD_DOWN_LOAD_RESOURCE;
	jos << cmd;

	// Ԥ�������ֽڰ�ͷlen������+��β���ȣ�
	size_t lengthPos = jos.Length();
	jos.Skip(2);
	jos << session.GetAttribute("username");
	jos << session.GetAttribute("filepath");
	string savePath = session.GetAttribute("savepath");

	//�ж��ļ��Ƿ����
	if (PathFileExists(savePath.c_str()))
	{
		CIsCoverDlg isCoverDlg;
		isCoverDlg.DoModal();
		if (isCoverDlg.GetIsCover())
			DeleteFile(savePath.c_str());		
		else
			return;
	}
	
	// ��ͷlen
	size_t tailPos = jos.Length();
	jos.Reposition(lengthPos);
	jos << static_cast<uint16>(tailPos + 8 - sizeof(RequestHead)); // ���峤�� + ��β����

	// ��β
	jos.Reposition(tailPos);
	// �����β
	unsigned char hash[16];
	MD5 md5;
	md5.MD5Make(hash, (const unsigned char*)jos.Data(), jos.Length());
	for (int i = 0; i<8; ++i)
	{
		hash[i] = hash[i] ^ hash[i + 8];
		hash[i] = hash[i] ^ ((cmd >> (i % 2)) & 0xff);
	}
	jos.WriteBytes(hash, 8);
	session.Send(jos.Data(), jos.Length());	// ���������

	session.Recv2();	// ����Ӧ���
	//JInStream jis(session.GetBuffer(), session.GetLen_());
	
	string content(session.GetBuffer() + sizeof uint32, session.GetLen_());
	FILE *fp = fopen(savePath.c_str(), "ab");
	if (NULL == fp)
	{
		AfxMessageBox("���ļ�ʧ��");
		return;
	}
	while (content != "end")
	{
		//���������ļ�����д���ļ�
		fwrite(session.GetBuffer() + sizeof uint32, session.GetLen_(), 1, fp);
		session.Recv2();
		content = string(session.GetBuffer() + sizeof uint32, session.GetLen_());
	}
	fclose(fp);	
}