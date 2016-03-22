#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "SharedSession.h"
#include "SharedServerSession.h"

namespace CMD
{

// √¸¡Óª˘¿‡
class Transaction
{
public:
	virtual void Execute(SharedSession& session) = 0;
	virtual void Execute(SharedServerSession& session) {}
	virtual ~Transaction() {};
};

}

#endif // _TRANSACTION_H_
