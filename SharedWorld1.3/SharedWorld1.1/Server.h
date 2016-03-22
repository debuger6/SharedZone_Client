#ifndef _SERVER_H_
#define _SERVER_H_
#include "Singleton.h"
#include "SharedSession.h"
#include "SharedWorld1.1Dlg.h"
using namespace PUBLIC;

class Server
{
	friend class Singleton<Server>;
public:
	int Start();
	
private:
	Server();
	Server(const Server& rhs);
	~Server();
	SharedSession* session_;
};

#endif // _SERVER_H_