// MyPoint.cpp: implementation of the MyPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "±ð²È°×¿é.h"
#include "MyPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyPoint::MyPoint()
{

}

MyPoint::~MyPoint()
{

}

void MyPoint::InitPoint()
{
	pt[0].x = 0;
	pt[0].y = 520;
	pt[1].x = 0;
	pt[1].y = 390;
	pt[2].x = 0;
	pt[2].y = 260;
	pt[3].x = 0;
	pt[3].y = 130;
}


POINTS* MyPoint::GetPoint()
{
	return pt;
}