#ifndef _SHARED_PACK_H_
#define _SHARED_PACK_H_

#define CMD_LOGIN					0x01
#define CMD_REGISTER				0x02
#define CMD_ACTIVEUSERS 			0x03
#define CMD_WITHDRAW				0x04
#define CMD_TRANSFER				0x05
#define CMD_BALANCE_INQUIRY			0x06
#define CMD_CHANGE_PASSWORD			0x07
#define CMD_DAY_BILL				0x08
#define CMD_HISTORY_BILL			0x09
#define CMD_ACCOUNT_HISTORY_BILL	0x0A
#define CMD_CLOSE_ACCOUNT			0x0B
#define CMD_NEW_ACCOUNT             0X10
#define CMD_SEND_CONTENT			0X11
#define CMD_SEND_REBACK				0x12
#define CMD_UPLOAD_DIR_RESOURCE		0x13
#define CMD_UPLOAD_FILE_RESOURCE	0x14
#define CMD_GET_RESOURCE			0x15
#define CMD_DOWN_LOAD_RESOURCE		0x16
struct RequestHead
{
	unsigned short cmd;
	unsigned short len;
};

struct ResponseHead
{
	unsigned short cmd;
	unsigned short len;
	unsigned short cnt;
	unsigned short seq;
	unsigned short error_code;
	char error_msg[30];
};

struct RequestPack
{
	RequestHead head;
	char buf[1];
};

struct ResponsePack
{
	ResponseHead head;
	char buf[1];
};


#endif