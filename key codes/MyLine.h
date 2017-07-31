// MyLine.h: interface for the MyLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLINE_H__CD063DBD_6B2A_4451_B6FE_564F75726DE4__INCLUDED_)
#define AFX_MYLINE_H__CD063DBD_6B2A_4451_B6FE_564F75726DE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MyPoint.h"

class MyLine  
{
public:
	
	MyLine();
	virtual ~MyLine();

	void InitLine(POINTS* pt);
	void PaintLine(CDC *pDC);



protected:
private:
	POINTS start[7];			//0-3为横线，4-6为竖线
	POINTS end[7];

};

#endif // !defined(AFX_MYLINE_H__CD063DBD_6B2A_4451_B6FE_564F75726DE4__INCLUDED_)
