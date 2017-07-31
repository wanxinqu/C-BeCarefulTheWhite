// SetInform.h: interface for the SetInform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETINFORM_H__AE6EF4D1_C37E_4013_971F_10A87CE85D45__INCLUDED_)
#define AFX_SETINFORM_H__AE6EF4D1_C37E_4013_971F_10A87CE85D45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SetInform  
{
private:
	int nowtime;
	int alltime;
	int blocknum;

	
public:
	bool zhangai;
	bool texiao;
	void setNowtime(int _i);
	int getNowtime();
	void setalltime(int _i);
	int getalltime();
	void setblocknum(int _i);
	int getblocknum();
	
	SetInform();
	virtual ~SetInform();


//	friend class CMyView;

};

#endif // !defined(AFX_SETINFORM_H__AE6EF4D1_C37E_4013_971F_10A87CE85D45__INCLUDED_)
