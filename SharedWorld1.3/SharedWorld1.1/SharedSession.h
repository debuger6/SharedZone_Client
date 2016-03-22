#ifndef _Shared_SESSION_H_
#define _Shared_SESSION_H_

#include "Socket.h"
#include "JInStream.h"
#include "JOutStream.h"
#include "MD5.h"
#include "Idea.h"
#include "SharedPack.h"
#include <map>
#include <list>
#include <vector>
#include <string>
#include <memory>
using namespace std;

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

class SharedSession  
{
public:
	SharedSession();
	~SharedSession();

	void SetResponse(const string& k, const string& v);
	const string& GetResponse(const string& k);

	void SetAttribute(const string& k, const string& v);
	const string& GetAttribute(const string& k);

	void Send(const char* buf, size_t len);
	void Recv();
	void Recv2();
	void Recv1();
	void Clear();

	void SetErrorCode(int16 errorCode)
	{
		errorCode_ = errorCode;
	}

	int16 GetErrorCode() const
	{
		return errorCode_;
	}

	void SetErrorMsg(const string& errorMsg)
	{
		errorMsg_ = errorMsg;
	}

	const string& GetErrorMsg() const
	{
		return errorMsg_;
	}

	uint16 GetCmd() const
	{
		return cmd_;
	}

	void SetCmd(uint16 cmd)
	{
		cmd_ = cmd;
	}

	void AddActiveUsers(const string& user)
	{
		activeUsers_.push_back(user);
	}

	vector<string>& GetActiveUsers()
	{
		return activeUsers_;
	}

	const char* GetBuffer()
	{
		return buffer_;
	}

	uint32 GetLen_()
	{
		return strlen;
	}
	

	ResponsePack* GetResponsePack() const { return responsePack_; }
	

private:
	
	std::auto_ptr<Socket> socket_;
	char buffer_[70000];				// 接收缓冲区
	char buffer1_[2048];
	ResponsePack* responsePack_;
	uint32* len_;
	uint32 strlen;
	uint16 cmd_;					// 请求命令
	map<string,string> request_;	// 请求数据
	map<string,string> response_;	// 应答数据
	vector<string> activeUsers_;      //
	
	int16 errorCode_;
	string errorMsg_;
};

#endif // _Shared_SESSION_H_
