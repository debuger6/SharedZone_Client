#include "stdafx.h"
#include "GetResource.h"
#include "CharSetConvert.h"
#include "Logging.h"
#include "JUtil.h"

using namespace PUBLIC;
using namespace CMD;

GetResource::GetResource()
{
}


GetResource::~GetResource()
{
}

void GetResource::Execute(SharedSession& session)
{
	JOutStream jos;

	// ��ͷ����
	uint16 cmd = CMD_GET_RESOURCE;
	jos << cmd;

	// Ԥ�������ֽڰ�ͷlen������+��β���ȣ�
	size_t lengthPos = jos.Length();
	jos.Skip(2);
	jos << session.GetAttribute("username");

	// ��ͷlen
	size_t tailPos = jos.Length();
	jos.Reposition(lengthPos);
	jos << static_cast<uint16>(tailPos + 8 - sizeof(RequestHead)); // ���峤�� + ��β����

	// ��β
	jos.Reposition(tailPos);
	// �����β
	MD5 md5;
	unsigned char hash[16];
	md5.MD5Make(hash, (const unsigned char*)jos.Data(), jos.Length());
	for (int i = 0; i<8; ++i)
	{
		hash[i] = hash[i] ^ hash[i + 8];
		hash[i] = hash[i] ^ ((cmd >> (i % 2)) & 0xff);
	}
	jos.WriteBytes(hash, 8);


	session.Send(jos.Data(), jos.Length());	// ���������
	
	
}


