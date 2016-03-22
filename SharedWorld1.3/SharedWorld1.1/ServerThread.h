#pragma once
#include "JThread.h"
using namespace PUBLIC;
class ServerThread : public JThread
{
public:
	ServerThread();
	~ServerThread();
	void Run();
};

