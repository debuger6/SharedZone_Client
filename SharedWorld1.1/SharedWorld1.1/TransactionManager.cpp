#include "stdafx.h"
#include "TransactionManager.h"
#include "UserLogin.h"
#include  "UserRegister.h"




TransactionManager::TransactionManager()
{
	m_actions[CMD_LOGIN] = new UserLogin;
	m_actions[CMD_REGISTER] = new UserRegister;
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