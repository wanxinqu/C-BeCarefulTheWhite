// ��Ȱ׿�View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__94F1DCF9_B294_4AEA_9A93_8BA5C441F539__INCLUDED_)
#define AFX_VIEW_H__94F1DCF9_B294_4AEA_9A93_8BA5C441F539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
#include "KeyDlg.h"
#include "SetInform.h"
#include "AbstractFactory.h"


#include <time.h>
/////////////////////////////////////////////////////////////////////////////


class CMyView : public CFormView
{
public:
	int LockThread;
	int ChoosePage;  //�����ҳ��1 ����ҳ��2
	CBitmap bitmap[12];  //ǰ���ΪԴ�����5��ͼ 6 7 8 9 �ֱ�Ϊ ���� �ֻ� �� ����
	CDC pcd[12];
	int m_count;
	float m_time;
	int jiejistyle;
	int zhuti;

	int classics_max_count;
	float Zen_max_time;
	int model;//1 ����ģʽ 2�ֻ�ģʽ 3��ģʽ
	
public:
	void initwindow();             // ��ʼ������
	void initdata();               // ��ʼ������
	void loadbitmap();             // ��ʼ��λͼ
	void paintpicture();           // ����Ϸ����
	void gamemain(int x,int y);    // ��Ϸ�����ⲿ��
	void startweb(int ii,int jj);  // ���п�ʼ����
	void blackweb(int ii,int jj);  // ���к�ɫ����
	void whiteweb(int ii,int jj);    // ���а�ɫ����
	void gameover();               // ��Ϸ��ɽ���
	void counttime();              // ��ʱ����ʾ
	void keydefault();             // Ĭ�ϰ�����ʼ��
	void cleanwindow(CDC *pDC);



	static DWORD WINAPI ThreadProc(LPVOID argv);
	void errorblockshan(int ii,int jj);
	void setspeed(int i);
//	void setMyWeb(int x,int y);
protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

public:
	//{{AFX_DATA(CMyView)
	enum{ IDD = IDD_MY_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CMyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRetry();
	afx_msg void OnExit();
	afx_msg void OnSetkey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ��Ȱ׿�View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__94F1DCF9_B294_4AEA_9A93_8BA5C441F539__INCLUDED_)
