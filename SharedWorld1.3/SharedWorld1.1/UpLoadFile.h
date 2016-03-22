#pragma once
#include "Transaction.h"
namespace CMD
{
	class UpLoadFile :
		public Transaction
	{
	public:
		UpLoadFile();
		~UpLoadFile();
	public:
		virtual void Execute(SharedSession& session);
		void SendFile(const char* buf, uint16 len, SharedSession& session, FILE *fp, int32 flag);
	};
}


