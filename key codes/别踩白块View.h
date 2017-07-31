// 别踩白块View.h : interface of the CMyView class
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
	int ChoosePage;  //标记是页面1 还是页面2
	CBitmap bitmap[12];  //前五个为源程序的5个图 6 7 8 9 分别为 经典 街机 禅 更多
	CDC pcd[12];
	int m_count;
	float m_time;
	int jiejistyle;
	int zhuti;

	int classics_max_count;
	float Zen_max_time;
	int model;//1 经典模式 2街机模式 3禅模式
	
public:
	void initwindow();             // 初始化窗口
	void initdata();               // 初始化数据
	void loadbitmap();             // 初始化位图
	void paintpicture();           // 画游戏画面
	void gamemain(int x,int y);    // 游戏的主题部分
	void startweb(int ii,int jj);  // 点中开始方格
	void blackweb(int ii,int jj);  // 点中黑色方格
	void whiteweb(int ii,int jj);    // 点中白色方格
	void gameover();               // 游戏完成结束
	void counttime();              // 计时并显示
	void keydefault();             // 默认按键初始化
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

#ifndef _DEBUG  // debug version in 别踩白块View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__94F1DCF9_B294_4AEA_9A93_8BA5C441F539__INCLUDED_)
