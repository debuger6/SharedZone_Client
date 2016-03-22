#include "stdafx.h"
#include "ServerThread.h"
#include "Server.h"


ServerThread::ServerThread()
{
}


ServerThread::~ServerThread()
{
}

void ServerThread::Run()
{
	Singleton<Server>::Instance().Start();
}