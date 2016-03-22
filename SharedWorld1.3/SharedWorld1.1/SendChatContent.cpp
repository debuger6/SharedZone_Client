#include "stdafx.h"
#include "SendChatContent.h"
#include "CharSetConvert.h"
#include "Logging.h"
#include "JUtil.h"

using namespace PUBLIC;
using namespace CMD;

void SendChatContent::Execute(SharedSession& session)
{
	JOutStream jos;

	// 包头命令
	uint16 cmd = CMD_SEND_CONTENT;
	jos << cmd;

	// 预留两个字节包头len（包体+包尾长度）
	size_t lengthPos = jos.Length();
	jos.Skip(2);

	// 发送者用户名
	string username; 
	CharSetConvert::MultiToUtf8(session.GetAttribute("username"), username);
	jos << username;
	int a = username.length();
	// 发送的内容
	string content;
	/*CharSetConvert::MultiToUtf8(session.GetAttribute("sendContent"), content);
	jos << content;*/
	jos << session.GetAttribute("sendContent");
	// 包头len
	size_t tailPos = jos.Length();
	jos.Reposition(lengthPos);
	jos << static_cast<uint16>(tailPos + 8 - sizeof(RequestHead)); // 包体长度 + 包尾长度

	// 包尾
	jos.Reposition(tailPos);
	// 计算包尾
	unsigned char hash[16];
	MD5 md5;
	md5.MD5Make(hash, (const unsigned char*)jos.Data(), jos.Length());
	for (int i = 0; i<8; ++i)
	{
		hash[i] = hash[i] ^ hash[i + 8];
		hash[i] = hash[i] ^ ((cmd >> (i % 2)) & 0xff);
	}
	jos.WriteBytes(hash, 8);


	session.Send(jos.Data(), jos.Length());	// 发送请求包
}


