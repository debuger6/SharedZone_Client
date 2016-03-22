#include "stdafx.h"
#include "UserLogin.h"
#include "CharSetConvert.h"
#include "Logging.h"
#include "JUtil.h"

using namespace PUBLIC;
using namespace CMD;

void UserLogin::Execute(SharedSession& session)
{
	JOutStream jos;

	// ��ͷ����
	uint16 cmd = CMD_LOGIN;
	jos<<cmd;

	// Ԥ�������ֽڰ�ͷlen������+��β���ȣ�
	size_t lengthPos = jos.Length();
	jos.Skip(2);
	
	// ��Ա��¼��
	string name;
	/*CharSetConvert::MultiToUtf8(session.GetAttribute("name"), name);
	jos<<name;*/
	jos << session.GetAttribute("name");

	// ����
	string pass = session.GetAttribute("pass");
	unsigned char ideaKey[16];
	unsigned char buf[2];
	buf[0] = (cmd >> 8) & 0xff;
	buf[1] = cmd & 0xff;
	MD5 md5;
	md5.MD5Make(ideaKey, buf, 2);
	for (int i=0; i<8; ++i)
	{
		ideaKey[i] = ideaKey[i] ^ ideaKey[i+8];
		ideaKey[i] = ideaKey[i] ^ ((cmd >> (i%2)) & 0xff);
		ideaKey[i+8] = ideaKey[i] ^ ideaKey[i+8];
		ideaKey[i+8] = ideaKey[i+8] ^ ((cmd >> (i%2)) & 0xff);
	}
	char encryptedPass[16];
	Idea idea;
	// ����
	idea.Crypt(ideaKey,(const unsigned char*)pass.c_str(), (unsigned char *)encryptedPass, 16, true);
	jos.WriteBytes(encryptedPass, 16);


	// ��ͷlen
	size_t tailPos = jos.Length();
	jos.Reposition(lengthPos);
	jos<<static_cast<uint16>(tailPos + 8 - sizeof(RequestHead)); // ���峤�� + ��β����

	// ��β
	jos.Reposition(tailPos);
	// �����β
	unsigned char hash[16];
	md5.MD5Make(hash, (const unsigned char*)jos.Data(), jos.Length());
	for (int i=0; i<8; ++i)
	{
		hash[i] = hash[i] ^ hash[i+8];
		hash[i] = hash[i] ^ ((cmd >> (i%2)) & 0xff);
	}
	jos.WriteBytes(hash, 8);


	session.Send(jos.Data(), jos.Length());	// ���������
	session.Recv();	// ����Ӧ���
	JInStream jis((const char*)session.GetResponsePack(), session.GetResponsePack()->head.len+sizeof(ResponseHead));
	// ����cmd��len
	
	//uint16 cmd;
	jis >> cmd;
	jis.Skip(2);
	uint16 cnt;
	uint16 seq;
	int16 error_code;
	jis>>cnt>>seq>>error_code;

	char error_msg[31];
	jis.ReadBytes(error_msg, 30);

	session.SetErrorCode(error_code);
	session.SetErrorMsg(error_msg);

	if (error_code == 0)
	{
		for (uint16 i = 0; i < cnt; ++i)
		{
			jis.SetData((const char*)session.GetResponsePack(),
				session.GetResponsePack()->head.len + sizeof(ResponseHead));
			// ����cmd��len
			jis.Skip(4);
			uint16 cnt;
			uint16 seq;
			int16 error_code;
			jis >> cnt >> seq >> error_code;

			char error_msg[31];
			jis.ReadBytes(error_msg, 30);

			string account;
			jis >> account;

			session.AddActiveUsers(account);
			
			if (seq == cnt - 1)
				return;
			session.Recv();
		}
	}
}


