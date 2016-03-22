#ifndef _SHARED_SERVER_SESSION_H_
#define _SHARED_SERVER_SESSION_H_

#include "JUtil.h"
#include "Socket.h"
#include "MD5.h"
#include "Idea.h"
#include "SharedPack.h"
#include <memory>
using namespace PUBLIC;



//struct RequestHead
//{
//	unsigned short cmd;
//	unsigned short len;
//};
//
//struct ResponseHead
//{
//	unsigned short cmd;
//	unsigned short len;
//	unsigned short cnt;
//	unsigned short seq;
//	unsigned short error_code;
//	char error_msg[30];
//};
//
//struct RequestPack
//{
//	RequestHead head;
//	char buf[1];
//};
//
//struct ResponsePack
//{
//	ResponseHead head;
//	char buf[1];
//};

class SharedServerSession
{
public:
	SharedServerSession(std::auto_ptr<Socket>& socket);
	~SharedServerSession();

	bool IsDead() const { return isDead_; }
	void Kill() { isDead_ = true; }
	void Process();
	uint16 GetCmd() const { return requestPack_->head.cmd; }
	RequestPack* GetRequestPack() const { return requestPack_; }
	void Send(const char* buf, size_t len);
	void Recv();
	void DoAction();


private:
	bool isDead_;
	std::auto_ptr<Socket> socket_;
	char buffer_[2048];
	RequestPack* requestPack_;
};


#endif // _SHARED_SERVER_SESSION_H_