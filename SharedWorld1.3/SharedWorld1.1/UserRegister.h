#pragma once
#include "Transaction.h"
namespace CMD
{
	class UserRegister :
		public Transaction
	{
	public:
		UserRegister();
		~UserRegister();
	public:
		virtual void Execute(SharedSession& session);
	};
}


