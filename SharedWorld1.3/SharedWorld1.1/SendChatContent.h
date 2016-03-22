#pragma once


#include "Transaction.h"

namespace CMD
{

	// 
	class SendChatContent : public Transaction
	{
	public:
		virtual void Execute(SharedSession& session);
	};

}





