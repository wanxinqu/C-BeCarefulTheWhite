// Classics.h: interface for the Classics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSICS_H__44FD80EE_5E58_4B1A_A9D3_623E75916340__INCLUDED_)
#define AFX_CLASSICS_H__44FD80EE_5E58_4B1A_A9D3_623E75916340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractFactory.h"

class Classics : public AbstractFactory  
{
public:
	Classics();
	virtual ~Classics();

	virtual void CreatePoint4();
	virtual void CreateSpecialEfficiency(){}
};

#endif // !defined(AFX_CLASSICS_H__44FD80EE_5E58_4B1A_A9D3_623E75916340__INCLUDED_)
