// ZhuTi.cpp : implementation file
//

#include "stdafx.h"
#include "±ð²È°×¿é.h"
#include "ZhuTi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZhuTi dialog


CZhuTi::CZhuTi(CWnd* pParent /*=NULL*/)
	: CDialog(CZhuTi::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZhuTi)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CZhuTi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZhuTi)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZhuTi, CDialog)
	//{{AFX_MSG_MAP(CZhuTi)
	ON_BN_CLICKED(IDC_BUTTON1, OnSetBlack)
	ON_BN_CLICKED(IDC_BUTTON2, OnSetBlue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZhuTi message handlers

void CZhuTi::OnSetBlack() 
{
	selectzhuti = 0;
	CDialog::OnOK();
	// TODO: Add your control notification handler code here
	
}

void CZhuTi::OnSetBlue() 
{
	selectzhuti = 1;
	// TODO: Add your	control notification handler code here
	CDialog::OnOK();
	
}
