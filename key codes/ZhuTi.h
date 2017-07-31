#if !defined(AFX_ZHUTI_H__118C6063_E13D_44BD_B01C_045831F86215__INCLUDED_)
#define AFX_ZHUTI_H__118C6063_E13D_44BD_B01C_045831F86215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZhuTi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZhuTi dialog

class CZhuTi : public CDialog
{
// Construction
public:
	CZhuTi(CWnd* pParent = NULL);   // standard constructor
	int selectzhuti;
// Dialog Data
	//{{AFX_DATA(CZhuTi)
	enum { IDD = IDD_ZHUTI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZhuTi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZhuTi)
	afx_msg void OnSetBlack();
	afx_msg void OnSetBlue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZHUTI_H__118C6063_E13D_44BD_B01C_045831F86215__INCLUDED_)
