// SetInform.cpp: implementation of the SetInform class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "±ð²È°×¿é.h"
#include "SetInform.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SetInform::SetInform()
{

}

SetInform::~SetInform()
{

}

int SetInform::getblocknum()
{
	return blocknum;
}

void SetInform::setblocknum(int _i)
{
	blocknum = _i;
}
