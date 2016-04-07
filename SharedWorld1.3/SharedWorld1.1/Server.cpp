#include "stdafx.h"
#include "Server.h"
#include "SharedThread.h"
#include "SharedWorld1.1.h"
#include "Socket.h"
#include "Logging.h"
#include "Client.h"

#include <memory>
#include <iostream>
#include <sstream>

Server::Server()
{
	session_ = Singleton<Client>::Instance().GetSharedSession();
}

Server::~Server()
{
	Socket::Cleanup();
}

int Server::Start()
{
	while (1)
	{
		//::AfxMessageBox("server is starting",MB_OK, 0);
		session_->Recv();
		JInStream jis((const char*)session_->GetResponsePack(), session_->GetResponsePack()->head.len + sizeof(ResponseHead));
		uint16 cmd = session_->GetResponsePack()->head.cmd;
		
		jis.Skip(4);
		uint16 cnt;
		uint16 seq;
		int16 error_code;
		jis >> cnt >> seq >> error_code;
		char error_msg[31];
		jis.ReadBytes(error_msg, 30);

		session_->SetErrorCode(error_code);
		session_->SetErrorMsg(error_msg);
		if (error_code == 0)
		{
			//有用户登录，更新用户列表

			if (cmd == (uint16)CMD_NEW_ACCOUNT)
			{
				session_->GetActiveUsers().clear();
				string username;
				jis >> username;				
				while (username != "end")
				{
					session_->AddActiveUsers(username);
					jis >> username;
				}
				theApp.setActiveUsers(session_->GetActiveUsers());
				theApp.dlg->InitUserList();
			}

			else if (cmd == (uint16)CMD_SEND_REBACK)
			{
				//::AfxMessageBox("发送成功", MB_OK, 0);
			}

			else if (cmd == CMD_SEND_CONTENT)
			{
				string username;
				jis >> username;
				string content;
				jis >> content;
				theApp.dlg->SetChatEditText(username.c_str(), content.c_str());
			}

			else if (cmd == CMD_REGISTER)
			{
				::AfxMessageBox("注册成功");
			}

			else if (cmd = CMD_GET_RESOURCE)
			{
				vector<CString> files;
				string fileName;
				jis >> fileName;
				while (fileName != "end")
				{
					files.push_back(fileName.c_str());
					jis >> fileName;
				}
				theApp.dlg->SetFiles(files);
				theApp.dlg->ShowFileTree();
			}



			
		}
		else if (error_code == 1)
		{
			if (cmd == CMD_REGISTER)
				::AfxMessageBox("该用户已存在");
		}
		else
		{
			throw exception("Server.cpp#62:出错");
		}
		
	
		
	}
	return 0;
}