#pragma once
#define NORMAL   0
#define PASSWD   1

// CMyEdit

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	void setType(int type);
private:
	int type;
	CString initString;
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


