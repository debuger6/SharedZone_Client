#ifndef _TRANSACTION_MANAGER_H_
#define _TRANSACTION_MANAGER_H_

#include "Singleton.h"
#include "SharedSession.h"
#include "SharedServerSession.h"
#include "Transaction.h"
#include <map>
#include <string>
using namespace std;

using namespace CMD;

class TransactionManager
{
	friend class Singleton<TransactionManager>;
public:
	bool DoAction(SharedSession& session);
	bool DoAction(SharedServerSession& session);

private:
	map<uint16, Transaction*> m_actions;
	TransactionManager();
	TransactionManager(const TransactionManager& rhs);
	~TransactionManager();

};

#endif // _TRANSACTION_MANAGER_H_
