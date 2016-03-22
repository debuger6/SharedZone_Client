#pragma once
#include "Transaction.h"
namespace CMD
{
	class GetResource :
		public Transaction
	{
	public:
		GetResource();
		~GetResource();
	public:
		virtual void Execute(SharedSession& session);
		
	};
}


