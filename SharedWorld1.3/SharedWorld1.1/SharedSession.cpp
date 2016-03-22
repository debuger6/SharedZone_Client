#include "stdafx.h"
#include "SharedSession.h"
#include "Client.h"

#include "StringUtil.h"
#include "Exception.h"


#include <iostream>
using namespace std;

SharedSession::SharedSession() : socket_(new Socket), errorCode_(0)
{
	socket_->Create();

	if (!socket_->Connect(
		Singleton<Client>::Instance().GetServerIp().c_str(),
		Singleton<Client>::Instance().GetPort())
		)
		throw Exception("连接失败");
	ZeroMemory(buffer_, sizeof(buffer_));
	responsePack_ = (ResponsePack*)buffer_;
	len_ = (uint32*)buffer_;
}

SharedSession::~SharedSession()
{
}

void SharedSession::Send(const char* buf, size_t len)
{
	socket_->SendN(buf, len);
}

void SharedSession::Recv1()
{
	int ret;
	ret = socket_->Recv(buffer1_, sizeof(ResponseHead));

	if (ret == 0)
		throw Exception("服务器端断开");
	else if (ret != sizeof(ResponseHead))
		throw Exception("接收数据包出错");

	uint16 cmd = Endian::NetworkToHost16(responsePack_->head.cmd);
	uint16 len = Endian::NetworkToHost16(responsePack_->head.len);
}

void SharedSession::Recv2()
{
	int ret;
	ret = socket_->RecvN(buffer_, sizeof uint32);
	if (ret == 0)
	{
		throw Exception("服务器端断开");
	}
	else if (ret != sizeof(uint32))
	{
		throw Exception("接收数据包错误");
	}
	uint32 len = *len_;
	 len = Endian::NetworkToHost32(*len_);
	 strlen = len;
	if (0 == len)
		return;

	ret = socket_->RecvN(buffer_ + sizeof uint32, len);
	if (ret == 0)
	{
		throw Exception("服务器端断开");
	}
	else if (ret != len)
	{
		throw Exception("接收数据出错");
	}
}

void SharedSession::Recv()
{
	int ret;
	ret = socket_->RecvN(buffer_, sizeof(ResponseHead));
	//::AfxMessageBox("recv", MB_OK, 0);
	if (ret == 0)
		throw Exception("服务器端断开");
	else if (ret != sizeof(ResponseHead))
		throw Exception("接收数据包出错");

	uint16 cmd = Endian::NetworkToHost16(responsePack_->head.cmd);
	uint16 len = Endian::NetworkToHost16(responsePack_->head.len);

	

	if (len == 0)
		return;

	ret = socket_->RecvN(responsePack_->buf, len);
	if (ret == 0)
		throw Exception("服务器端断开");
	else if (ret != len)
		throw Exception("接收数据包出错");

	// 计算hash
	unsigned char hash[16];
	MD5 md5;
	md5.MD5Make(hash, (unsigned char const *)buffer_, sizeof(ResponseHead)+len-8);
	for (int i=0; i<8; ++i)
	{
		hash[i] = hash[i] ^ hash[i+8];
		hash[i] = hash[i] ^ ((cmd >> (i%2)) & 0xff);
	}

	if (memcmp(hash, buffer_+sizeof(ResponseHead)+len-8, 8))
		throw Exception("错误的数据包");

	responsePack_->head.cmd = cmd;
	responsePack_->head.len = len;

	
}

void SharedSession::Clear()
{
	request_.clear();
	response_.clear();
	errorCode_ = 0;
}

void SharedSession::SetResponse(const string& k, const string& v)
{
	response_[k] = v;
}

const string& SharedSession::GetResponse(const string& k)
{
	return response_[k];
}

void SharedSession::SetAttribute(const string& k, const string& v)
{
	request_[k] = v;
}

const string& SharedSession::GetAttribute(const string& k)
{
	return request_[k];
}

