#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "SharedSession.h"
#include "SystemConfig.h"
#include "Singleton.h"


using namespace PUBLIC;

class Client
{
	friend class Singleton<Client>;
public:
	const string& GetServerIp() const
	{
		return serverIp_;
	}

	unsigned short GetPort() const
	{
		return port_;
	}

	SharedSession* GetSharedSession()
	{
		return ss_;
	}
private:
	Client();
	Client(const Client& rhs);
	~Client();

	SystemConfig config_;

	string serverIp_;
	unsigned short port_;

	SharedSession* ss_;
};

#endif // _CLIENT_H_
