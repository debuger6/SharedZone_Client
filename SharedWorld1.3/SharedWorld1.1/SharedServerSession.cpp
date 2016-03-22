#include "stdafx.h"
#include "SharedServerSession.h"

#include "TransactionManager.h"

#include "Exception.h"
#include "Singleton.h"


SharedServerSession::SharedServerSession(std::auto_ptr<Socket>& socket) : socket_(socket), isDead_(false)
{
	requestPack_= (RequestPack*)buffer_;
}

SharedServerSession::~SharedServerSession()
{
}

void SharedServerSession::Process()
{
	Recv();
	DoAction();
}

void SharedServerSession::Send(const char* buf, size_t len)
{
	socket_->SendN(buf, len);
}

void SharedServerSession::Recv()
{
	int ret;
	// ���հ�ͷ
	ret = socket_->RecvN(buffer_, sizeof(RequestHead));
	if (ret == 0)	// �ͻ��˹ر�
		throw Exception("�ͻ��˹ر�");
	else if (ret != sizeof(RequestHead))
	{
		throw Exception("�������ݰ�����");
	}

	uint16 cmd = Endian::NetworkToHost16(requestPack_->head.cmd);
	uint16 len = Endian::NetworkToHost16(requestPack_->head.len);
	

	// ���հ���+��β
	ret = socket_->RecvN(/*buffer_+sizeof(RequestHead)*/requestPack_->buf, len);
	if (ret == 0)	// �ͻ��˹ر�
		throw Exception("�ͻ��˹ر�");
	else if (ret != len)
	{
		throw Exception("�������ݰ�����");
	}

	// ����hash
	unsigned char hash[16];
	MD5 md5;
	md5.MD5Make(hash, (unsigned char const *)buffer_, sizeof(RequestHead)+len-8);
	for (int i=0; i<8; ++i)
	{
		hash[i] = hash[i] ^ hash[i+8];
		hash[i] = hash[i] ^ ((cmd >> (i%2)) & 0xff);
	}

	if (memcmp(hash, buffer_+sizeof(RequestHead)+len-8, 8))
		throw Exception("��������ݰ�");

	requestPack_->head.cmd = cmd;
	requestPack_->head.len = len;

}

void SharedServerSession::DoAction()
{
	Singleton<TransactionManager>::Instance().DoAction(*this);
}
