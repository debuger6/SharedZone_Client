#include "stdafx.h"
#include "SendChatContent.h"
#include "CharSetConvert.h"
#include "Logging.h"
#include "JUtil.h"

using namespace PUBLIC;
using namespace CMD;

void SendChatContent::Execute(SharedSession& session)
{
	JOutStream jos;

	// ��ͷ����
	uint16 cmd = CMD_SEND_CONTENT;
	jos << cmd;

	// Ԥ�������ֽڰ�ͷlen������+��β���ȣ�
	size_t lengthPos = jos.Length();
	jos.Skip(2);

	// �������û���
	string username; 
	CharSetConvert::MultiToUtf8(session.GetAttribute("username"), username);
	jos << username;
	int a = username.length();
	// ���͵�����
	string content;
	/*CharSetConvert::MultiToUtf8(session.GetAttribute("sendContent"), content);
	jos << content;*/
	jos << session.GetAttribute("sendContent");
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
}


