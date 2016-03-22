#ifndef _SHARED_THREAD_H_
#define _SHARED_THREAD_H_

#include "JThread.h"
#include "Socket.h"

#include <memory>

using namespace PUBLIC;

class SharedThread : public JThread
{
public:
	SharedThread(std::auto_ptr<Socket>& socket);
	~SharedThread();

	void Run();

	std::auto_ptr<Socket> socket_;
};

#endif // _SHARED_THREAD_H_