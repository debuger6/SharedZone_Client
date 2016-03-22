#include "stdafx.h"
#include "TransactionManager.h"
#include "UserLogin.h"
#include  "UserRegister.h"
#include "SendChatContent.h"
#include "UpLoadFile.h"
#include "GetResource.h"
#include "DownLoadFile.h"



TransactionManager::TransactionManager()
{
	m_actions[CMD_LOGIN] = new UserLogin;
	m_actions[CMD_REGISTER] = new UserRegister;
	m_actions[CMD_SEND_CONTENT] = new SendChatContent;
	m_actions[CMD_UPLOAD_FILE_RESOURCE] = new UpLoadFile;
	m_actions[CMD_GET_RESOURCE] = new GetResource;
	m_actions[CMD_DOWN_LOAD_RESOURCE] = new DownLoadFile;
}

TransactionManager::~TransactionManager()
{
	for (map<uint16, Transaction*>::iterator it=m_actions.begin();
		it!=m_actions.end();++it)
	{
			delete it->second;
	}
}

bool TransactionManager::DoAction(SharedSession& session)
{
	uint16 cmd = session.GetCmd();
	if (m_actions.find(cmd) != m_actions.end())
	{
		m_actions[cmd]->Execute(session);
		return true;
	}

	return false;
}

bool TransactionManager::DoAction(SharedServerSession& session)
{
	uint16 cmd = session.GetCmd();
	if (m_actions.find(cmd) != m_actions.end())
	{
		m_actions[cmd]->Execute(session);
		return true;
	}

	return false;
}