#pragma once
#include "Transaction.h"
namespace CMD
{
	class DownLoadFile :
		public Transaction
	{
	public:
		DownLoadFile();
		~DownLoadFile();
	public:
		virtual void Execute(SharedSession& session);
	};
}


