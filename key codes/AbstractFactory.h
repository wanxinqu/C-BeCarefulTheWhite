// AbstractFactory.h: interface for the AbstractFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTFACTORY_H__8E73600F_15AA_484C_912D_787D8CD22333__INCLUDED_)
#define AFX_ABSTRACTFACTORY_H__8E73600F_15AA_484C_912D_787D8CD22333__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "KeyDlg.h"
#include "SetInform.h"

class AbstractFactory  
{
public:
	SetInform SI;
	AbstractFactory();
	virtual ~AbstractFactory();
	virtual void CreatePoint4()=0;
	virtual void CreateSpecialEfficiency()=0;

};

#endif // !defined(AFX_ABSTRACTFACTORY_H__8E73600F_15AA_484C_912D_787D8CD22333__INCLUDED_)
