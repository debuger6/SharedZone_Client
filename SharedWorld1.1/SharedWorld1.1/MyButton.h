#pragma once


// MyButton

class MyButton : public CMFCButton
{
	DECLARE_DYNAMIC(MyButton)

public:
	MyButton();
	virtual ~MyButton();

protected:
	DECLARE_MESSAGE_MAP()
};


