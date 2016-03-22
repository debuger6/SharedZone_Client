#include "stdafx.h"
#include "SharedThread.h"

#include "SharedServerSession.h"

#include "Logging.h"
#include "StringUtil.h"
#include "Exception.h"

#include <string>
#include <vector>

SharedThread::SharedThread(std::auto_ptr<Socket>& socket) : socket_(socket)
{
}

SharedThread::~SharedThread()
{
}

void SharedThread::Run()
{
	/*
	int ret;
	while (1)
	{
		char buffer[1024] = {0};
		ret = socket_->Recv(buffer, sizeof(buffer));
		if (ret == -1)
		{
			LOG_INFO<<"读取网络消息错误";
			break;
		}
		if (ret == 0)
		{
			LOG_INFO<<"客户端关闭";
			break;
		}


		std::vector<std::string> v = StringUtil::Split(buffer, '#');
		if (v.size() != 2)
		{
			LOG_INFO<<"错误的消息";
		}
		else
			LOG_INFO<<"user="<<v[0]<<" pass="<<v[1];

		socket_->Send(buffer, ret);

	}
	*/

	SharedServerSession* sss = new SharedServerSession(socket_);	// 所有权转移到了SharedSession
	while (!sss->IsDead())
	{
		try
		{
			sss->Process();
		}
		catch (Exception& e)
		{
			LOG_INFO<<e.what();
			sss->Kill();
		}
	}
	delete sss;
}
