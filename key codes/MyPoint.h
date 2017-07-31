// MyPoint.h: interface for the MyPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPOINT_H__15E6A5C3_5FDF_4262_ADE6_A8D61EA3C174__INCLUDED_)
#define AFX_MYPOINT_H__15E6A5C3_5FDF_4262_ADE6_A8D61EA3C174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MyPoint  
{
public:
	MyPoint();
	virtual ~MyPoint();

	virtual void SetPoint()=0;
	void InitPoint();
	POINTS* GetPoint();
	
private:
	POINTS pt[4];

};

#endif // !defined(AFX_MYPOINT_H__15E6A5C3_5FDF_4262_ADE6_A8D61EA3C174__INCLUDED_)
