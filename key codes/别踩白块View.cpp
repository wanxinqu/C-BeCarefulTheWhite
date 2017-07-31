// 别踩白块View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "别踩白块.h"

#include "别踩白块Doc.h"
#include "别踩白块View.h"
#include "AbstractFactory.h"
#include "Classics.h"
#include "StreetModel.h"
#include "MyPoint.h"
#include "CommonPoint.h"
#include "MyLine.h"
#include "ZhuTi.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
struct web
{
	int x;     // 方格x轴坐标
	int y;     // 方格y轴坐标
	int flag;  // 颜色标志;0表示白、1表示黑、2表示灰、3表示黄、4表示绿、5表示开始
	int lock;  // 解锁标志；0表示锁定，1表示解锁；只有在上一级的黑色方格解锁成功后，才能解锁下一次的黑色方格
}Web[5][4];



struct key
{
	CString name;  // 按键的名称
	int flag;      // 对应的列数；1、2、3、4分别对应一、二、三、四列
}Key[4];

HANDLE Thread;
DWORD ThreadID;
CDC* pmyDC;
int Speed;
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CFormView)

BEGIN_MESSAGE_MAP(CMyView, CFormView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_RETRY, OnRetry)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_SETKEY, OnSetkey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction


DWORD WINAPI CMyView::ThreadProc(LPVOID argv)
{
	int i = 0;
	int j = 0;
	CMyView* p = (CMyView*)argv;
	int m,n,lucky;		
	int Jiecount=4;
	while(1)
	{
		for (i=0;i<5;i++)
		{
			for (j=0;j<4;j++)
			{
				Web[i][j].y += Speed;
			
			}
		}

		
		for (i=0;i<5;i++)   //回滚问题
		{
			if(Web[i][0].y>516)
			{
				Jiecount++;
				for (j=0;j<4;j++)
				{
					Web[i][j].y = -130;
					Web[i][j].flag=0;
				
				}
				m=rand()%4;
				Web[i][m].flag=1;


				
				if (p->jiejistyle==1)
				{
					m = rand()%4;
					lucky = rand()%6;
					//	j = Web[n][m].flag;

					if (p->m_count%10==0) //闪电大招
					{
						CDC* pDC = p->GetDC();

						p->cleanwindow(pDC);
						Sleep(200);

						p->cleanwindow(pDC);
						Sleep(200);

						p->cleanwindow(pDC);
						Sleep(200);
						
					}
					
					if (Web[i][m].flag==0&&lucky==0)//乌龟
					{
						Web[i][m].flag=10;
					}
					else if (Web[i][m].flag==0&&lucky==3)//火箭
					{
						Web[i][m].flag=11;
					}
					
				}
				else if (p->jiejistyle==0)
				{
					if (Jiecount==15)
					{
						Speed+=1;
						Jiecount = 0;
					}
				}
				//乌龟 火箭问题
		
			}		
		}
       
		
		for (i=0;i<5;i++)   //黑块到底但没有 点击问题
		{
			for (j=0;j<4;j++)
			{
				if (Web[i][j].y>455&&Web[i][j].flag==1)
				{
					p->errorblockshan(i,j);
						for (int m=0;m<5;m++){
							for (int n=0;n<4;n++){
						Web[m][n].flag=3;}}

						p->paintpicture();
						TerminateThread(Thread,NULL);
				}
			}
		}


		Sleep(10);

		p->paintpicture();
	}
}

CMyView::CMyView()
	: CFormView(CMyView::IDD)
{
	//{{AFX_DATA_INIT(CMyView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here



}

CMyView::~CMyView()
{
}

void CMyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	AfxGetApp()->m_pMainWnd->SetWindowPos(NULL,400,100,420,582,NULL);     // 调整窗口大小
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

void CMyView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class	
	initwindow();
	keydefault();
	initdata();
	loadbitmap();
	paintpicture();
}

void CMyView::initwindow()
{
	ChoosePage = 0;
	LockThread = 0;
	Speed = 1;

	CDC *pDC=GetDC();//CDC是干啥的
	pmyDC = pDC;
	CRect rt;
	pDC->GetClipBox(&rt);
	CBrush brush=RGB(0,255,0);
	CBrush *oldbrush=pDC->SelectObject(&brush);
	pDC->Rectangle(0,0,rt.Width(),rt.Height());
	pDC->Rectangle(0,0,9999,9999);
	pDC->SelectObject(oldbrush);
	ReleaseDC(pDC);
}

void CMyView::initdata()
{
	int i,j,x;
	m_count=0;
	m_time=0.0;
//	srand(time(NULL));
	for(i=0;i<5;i++)                 // 行
	{
		for(j=0;j<4;j++)             // 列
		{
			if (4==i)
			{
				Web[i][j].x=100*j;       // 方格的横坐标
				Web[i][j].y=-130;       // 方格的纵坐标
				Web[i][j].flag=0;        // 所有方格全为白色
				Web[i][j].lock=0;
			}
			else
			{
				Web[i][j].x=100*j;       // 方格的横坐标
				Web[i][j].y=130*i;       // 方格的纵坐标
				Web[i][j].flag=0;        // 所有方格全为白色
				Web[i][j].lock=0;        // 所有方格全为锁定状态
			
			}
			if(3==i)                 // 第四行方格全为黄色
			{
				Web[i][j].flag=3;
				Web[i][j].lock=0;
			}
			
		}
		if(3!=i)                     // 为每一行随机分配一个黑色方格位置
		{
			x=rand()%4;
			Web[i][x].flag=1;
			if(2==i)
				Web[i][x].flag=5;	//开始
		}
	}
/*
	int a = Web[4][0].flag;
	int b = Web[4][1].flag;
	int c = Web[4][2].flag;
	int d = Web[4][3].flag;*/
}

void CMyView::loadbitmap()
{
	int i;
	CDC *pDC=GetDC();
	for(i=0;i<12;i++)
	{
		pcd[i].CreateCompatibleDC(pDC);
		switch(i)
		{
		case 0:bitmap[i].LoadBitmap(IDB_white);pcd[i].SelectObject(bitmap[i]);break;
		case 1:bitmap[i].LoadBitmap(IDB_black);pcd[i].SelectObject(bitmap[i]);break;
		case 2:bitmap[i].LoadBitmap(IDB_grey);pcd[i].SelectObject(bitmap[i]);break;
		case 3:bitmap[i].LoadBitmap(IDB_yellow);pcd[i].SelectObject(bitmap[i]);break;
		case 4:bitmap[i].LoadBitmap(IDB_green);pcd[i].SelectObject(bitmap[i]);break;
		case 5:bitmap[i].LoadBitmap(IDB_start);pcd[i].SelectObject(bitmap[i]);break;


		case 6:bitmap[i].LoadBitmap(IDB_jingdian);pcd[i].SelectObject(bitmap[i]);break;
		case 7:bitmap[i].LoadBitmap(IDB_jieji);pcd[i].SelectObject(bitmap[i]);break;
		case 8:bitmap[i].LoadBitmap(IDB_chan);pcd[i].SelectObject(bitmap[i]);break;
		case 9:bitmap[i].LoadBitmap(IDB_gengduo);pcd[i].SelectObject(bitmap[i]);break;
		
		case 10:bitmap[i].LoadBitmap(IDB_WuGui);pcd[i].SelectObject(bitmap[i]);break;
		case 11:bitmap[i].LoadBitmap(IDB_HuoJian);pcd[i].SelectObject(bitmap[i]);break;
		
		}
	}


	ReleaseDC(pDC);
}

void CMyView::paintpicture()
{
	if (ChoosePage==0)  //页面1
	{
		CDC *pDC=GetDC();
		pDC->BitBlt(0,0,200,260,&pcd[6],0,0,SRCCOPY);
		pDC->BitBlt(200,0,200,260,&pcd[7],0,0,SRCCOPY);
	
		pDC->BitBlt(0,260,200,260,&pcd[8],0,0,SRCCOPY);
	
		pDC->BitBlt(200,260,200,260,&pcd[9],0,0,SRCCOPY);

		ReleaseDC(pDC);
	}
	else
	{

		CDC *pDC=GetDC();
		int i,j,x,y,f;  //f代表颜色
		for(i=0;i<5;i++)
		{
			for(j=0;j<4;j++)
			{
				x=Web[i][j].x;
				y=Web[i][j].y;
				f=Web[i][j].flag;
				pDC->BitBlt(x,y,100,130,&pcd[f],0,0,SRCCOPY);
			}
		}
		ReleaseDC(pDC);		
	}

}

void CMyView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (ChoosePage==0)
	{
		
		if (point.x<200&&point.y<=260)
		{	
			Classics classics;
			AbstractFactory* abfactory = &classics;

			model = 1;
			
			//应该写在Line类里面
			///////////////////////////////////////
			CommonPoint commonpoint;
			MyPoint* mypoint = &commonpoint;
			mypoint->InitPoint();
			/////////////////////////////////////////////

			if (point.y>100&&point.y<=180)			//经典模式 25
			{//找到点击位置对应的模式后 设置变量 然后进入游戏界面（else）
				abfactory->SI.setblocknum(25);
				abfactory->SI.texiao = false;
				abfactory->SI.zhangai = false;

				classics_max_count = abfactory->SI.getblocknum();
			}
			else if(point.y>180) //经典模式 50块
			{
				abfactory->SI.setblocknum(50);
				abfactory->SI.texiao = false;
				abfactory->SI.zhangai = false;

				classics_max_count = abfactory->SI.getblocknum();	
			}
			else
			{
				return;
			}
		}
		else if (point.x<200&&point.y>260) //禅模式
		{
			model = 3;
			m_count = 0;
			if (point.y>360&&point.y<440)
			{
				Zen_max_time = 15;

			}

			else if(point.y>=440)
			{
				Zen_max_time = 30;

			}

			else
			{
				return;
			}		
		}

		else if (point.x>200&&point.y<=260)  //街机模式
		{
			StreetModel street;
			AbstractFactory* abfactory = &street;
			if (point.y>100&&point.y<=180)			//经典模式 25
			{
				jiejistyle = 0;
			}
			else if(point.y>180)
			{
				jiejistyle = 1;
			}

			else
			{
				return;
			}
			
			
			model = 2;

		}

		else if (point.x>200&&point.y>260)    //更多
		{
			if (point.y<=440&&point.y>360)
			{
				CZhuTi zhutiDlg;
				zhutiDlg.DoModal();
				zhuti = zhutiDlg.selectzhuti;
				
				if (zhuti==1)
				{
					CBitmap bitmap;
					CBitmap bitmap1;
					bitmap.LoadBitmap(IDB_blue);
					pcd[1].SelectObject(bitmap);
					bitmap1.LoadBitmap(IDB_start2);
					pcd[5].SelectObject(bitmap1);
					
				}
				if (zhuti==0)
				{
					CBitmap bitmap;
					CBitmap bitmap1;
					bitmap.LoadBitmap(IDB_black);
					pcd[1].SelectObject(bitmap);
					bitmap1.LoadBitmap(IDB_start);
					pcd[5].SelectObject(bitmap1);
					
				}
				ChoosePage = 0;
				
				return;
			} 
			else if(point.y>440)
			{
				AfxMessageBox("这个游戏唯一的一个规则,我们只需要不断踩着黑色方块前进即可,很简单吧?快来挑战看看吧!游戏有三个模式:经典模式,以最快的速度到达终点;街机模式,你有能力得多少分就得多少分,没有任何限制,这也是最具挑战性的一个模式;禅模式,在规定时间内秒内看你能走几步");

				ChoosePage = 0;
				return;
			}

			else
			{
				return;
			}
		}
		else
		{
			exit(0);
		}

		ChoosePage=1;

		paintpicture();
	}

	else
	{
		gamemain(point.x,point.y);   //刷新一下页面
		
		CFormView::OnLButtonDown(nFlags, point);
	}
}
/*
void CMyView::startweb(int x,int y)
{
/*	int i,j;
	for(i=3;i>0;i--)                                    // 将方格都下移一行;最底一行消失，第一行出现更新，并随机分配黑色方格的位置，其它行一次下移，属性保持不变
	{
		for(j=0;j<4;j++)
		{
			Web[i][j].flag=Web[i-1][j].flag;
			Web[i][j].lock=Web[i-1][j].lock;
		}
	}
	for(j=0;j<4;j++)                                    // 生成新的一行
	{
		Web[0][j].flag=0;
		Web[0][j].lock=0;
	}
	//	srand(time(NULL));
	x=rand()%4;
	Web[0][x].flag=1;
	
}*/

void CMyView::gamemain(int x,int y)
{
	if (model==1)
	{
		int i,j,m,n;
		for(i=0;i<4;i++)             // 获取鼠标点击的方格的位置 放入m、n
		{
			for(j=0;j<4;j++)
			{
				if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))
				{
					m=i;
					n=j;
				}
			}
			//		if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))    有错误	
		}
		i=m;
		j=n;  //根据点击位置不同分别处理
		if(5==Web[i][j].flag)       // 点中的是开始方格
		{
			SetTimer(1,50,NULL);
			startweb(i,j);
		}
		else if(1==Web[i][j].flag)  // 点中的是黑色方格
		{
			blackweb(i,j);

		}
		else if(0==Web[i][j].flag)  // 点中的是白色方格 
		{
			KillTimer(1);
			whiteweb(0,0);
		}
		gameover();                 // 判断游戏结束
		paintpicture();             // 重画游戏画面
		m_time = m_time-0.05;
		counttime();                // 显示最后一次的时间

	}

	else if (model==2&&LockThread==0)			//多线程
	{
		
		Thread = CreateThread(0,0,ThreadProc,(LPVOID)this,0,&ThreadID);
		LockThread = 1;
		m_count++;
	}
	else if (model==2&&LockThread==1)
	{	
		int i,j,m,n;
		for(i=0;i<5;i++)             // 获取鼠标点击的方格的位置 放入m、n
		{
			for(j=0;j<4;j++)
			{
				if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))
				{
					m=i;
					n=j;
				}
			}
		}
		i=m;
		j=n;  //根据点击位置不同分别处理
		if(5==Web[i][j].flag)       // 点中的是开始方格
		{
			startweb(i,j);
		}

		else if(1==Web[i][j].flag)  // 点中的是黑色方格
		{
			blackweb(i,j);
			
		}
		else if(0==Web[i][j].flag)  // 点中的是白色方格 
		{
			whiteweb(i,j);
			paintpicture();
		}
		else if (10==Web[i][j].flag)
		{
			setspeed(10);
		}
		else if (11==Web[i][j].flag)
		{
			setspeed(11);
		}

		gameover();                 // 判断游戏结束
		
	}

	else if (model==3)
	{
		int i,j,m,n;
		for(i=0;i<4;i++)             // 获取鼠标点击的方格的位置 放入m、n
		{
			for(j=0;j<4;j++)
			{
				if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))
				{
					m=i;
					n=j;
				}
			}
			//		if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))    有错误	
		}
		i=m;
		j=n;  //根据点击位置不同分别处理
		if(5==Web[i][j].flag)       // 点中的是开始方格
		{
			SetTimer(1,50,NULL);
			startweb(i,j);
		}
		else if(1==Web[i][j].flag)  // 点中的是黑色方格
		{
			blackweb(i,j);
			
		}
		else if(0==Web[i][j].flag)  // 点中的是白色方格 
		{
			KillTimer(1);
			whiteweb(0,0);
		}
		gameover();                 // 判断游戏结束
		paintpicture();             // 重画游戏画面
		m_time = m_time-0.05;
		counttime();                // 显示最后一次的时间

	}
	
}

void CMyView::startweb(int ii,int jj)
{
	switch(model)
	{
	case 1:
		{
			m_count++;
			Web[ii][jj].flag=2;         // 将黑色方块变成灰色
			Web[ii][jj].lock=1;         // 将方块解锁
			int i,j,x;
			for(i=3;i>0;i--)            // 将方格都下移一行;最底一行消失，第一行出现更新，并随机分配黑色方格的位置，其它行一次下移，属性保持不变
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=Web[i-1][j].flag;
					Web[i][j].lock=Web[i-1][j].lock;
				}
			}
			for(j=0;j<4;j++)            // 新生成一行 
			{
				Web[0][j].flag=0;
				Web[0][j].lock=0;
			}
			//	srand(time(NULL));
			x=rand()%4;
			Web[0][x].flag=1;
			break;
		}
	case 2:
		{
			Web[ii][jj].flag=2;         // 将黑色方块变成灰色
			break;
			
		}
	case 3:
		{
			m_count++;
			Web[ii][jj].flag=2;         // 将黑色方块变成灰色
			Web[ii][jj].lock=1;         // 将方块解锁
			int i,j,x;
			for(i=3;i>0;i--)            // 将方格都下移一行;最底一行消失，第一行出现更新，并随机分配黑色方格的位置，其它行一次下移，属性保持不变
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=Web[i-1][j].flag;
					Web[i][j].lock=Web[i-1][j].lock;
				}
			}
			for(j=0;j<4;j++)            // 新生成一行 
			{
				Web[0][j].flag=0;
				Web[0][j].lock=0;
			}
			//	srand(time(NULL));
			x=rand()%4;
			Web[0][x].flag=1;
			break;
		}
	default:
		{
			break;
		}
	}
	
}

void CMyView::blackweb(int ii,int jj)
{
	switch(model)
	{
	case 1:
		{
			int i,j,x,n=0;
			for(j=0;j<4;j++)
			if(2!=Web[(ii)+1][j].flag)  // 只有上一行的黑色方格(解锁后变成灰色了)解锁后才能点击下一个
				n++;
			if(4==n)
				return;
			m_count++;
			Web[ii][jj].flag=2;                                 // 黑色方格变成灰色
			Web[ii][jj].lock=1;                                 // 将灰色方格解锁
			for(i=3;i>0;i--)                                    // 将方格都下移一行;最底一行消失，第一行出现更新，并随机分配黑色方格的位置，其它行一次下移，属性保持不变
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=Web[i-1][j].flag;
					Web[i][j].lock=Web[i-1][j].lock;
				}
			}
			for(j=0;j<4;j++)                                    // 生成新的一行
			{
				Web[0][j].flag=0;				
				Web[0][j].lock=0;
			}
			//	srand(time(NULL));
			x=rand()%4;
			Web[0][x].flag=1;
	
			break;
		}
	case 2:
		{
			m_count++;
			Web[ii][jj].flag=2;         // 将黑色方块变成灰色
			
			break;
		}
	case 3:
		{
			int i,j,x,n=0;
			for(j=0;j<4;j++)
				if(2!=Web[(ii)+1][j].flag)  // 只有上一行的黑色方格(解锁后变成灰色了)解锁后才能点击下一个
					n++;
				if(4==n)
					return;
				m_count++;
				Web[ii][jj].flag=2;                                 // 黑色方格变成灰色
				Web[ii][jj].lock=1;                                 // 将灰色方格解锁
				for(i=3;i>0;i--)                                    // 将方格都下移一行;最底一行消失，第一行出现更新，并随机分配黑色方格的位置，其它行一次下移，属性保持不变
				{
					for(j=0;j<4;j++)
					{
						Web[i][j].flag=Web[i-1][j].flag;
						Web[i][j].lock=Web[i-1][j].lock;
					}
				}
				for(j=0;j<4;j++)                                    // 生成新的一行
				{
					Web[0][j].flag=0;				
					Web[0][j].lock=0;
				}
				//	srand(time(NULL));
				x=rand()%4;
				Web[0][x].flag=1;
				
			break;
		}
	default:
		{
			
		}
	}
}

void CMyView::setspeed(int i)
{
	if (i==10&&i>2)
	{
		Speed -= 1;
	}
	else if(i==11)
	{
		Speed += 1;
	}
}

void CMyView::gameover()
{
	switch(model)
	{
	case 1:
		{
			if(classics_max_count-2<=m_count)         // 游戏准备结束；画绿色方格
			{
				int j;
				for(j=0;j<4;j++)
				{
					Web[0][j].flag=4;
					Web[0][j].lock=0;
				}
			}
			if(classics_max_count==m_count)
			{
				KillTimer(1);
				CString s;
				s.Format("%.3f",m_time);
				AfxMessageBox("恭喜你!\n顺利完成游戏!\n用时:"+s+"秒");
			}
			break;
		}
	case 3:
		{
			if (m_time>=Zen_max_time)
			{
				KillTimer(1);
				CString s;
				s.Format("%d",m_count);
				AfxMessageBox("恭喜你!\n规定时间内走完"+s+"步");

			}
			break;
		}
	default:
		{
			break;
		}
	}
	
}

void CMyView::whiteweb(int ii,int jj)
{
	switch(model)
	{
	case 1:
		{
			AfxMessageBox("游戏结束!!\n很遗憾~~\n你点错方格了!");
			int i,j;
			for(i=0;i<5;i++)
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=3;
					Web[i][j].lock=0;
				}
			}
			paintpicture();
			break;
		}
	case 2:
		{
			TerminateThread(Thread,NULL);
			errorblockshan(ii,jj);
			
			CString s;
			s.Format("%d",m_count);
			
			AfxMessageBox("游戏结束!!\n你共走过了"+s+"块!");
			int i,j;
			for(i=0;i<5;i++)
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=3;
					Web[i][j].lock=0;
				}
			}
//			paintpicture();
		
			break;
		}
	case 3:
		{
			AfxMessageBox("游戏结束!!\n很遗憾~~\n你点错方格了!");
			int i,j;
			for(i=0;i<5;i++)
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=3;
					Web[i][j].lock=0;
				}
			}
			paintpicture();
			break;
		}
	default:
		{
			break;
		}
	}
	
}


void CMyView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:counttime();break;
	}

	if (model==3&&m_time>=Zen_max_time)
	{
		gameover();
	}

	CFormView::OnTimer(nIDEvent);
}

void CMyView::counttime()
{
	CString s;
	s.Format("%.3f",m_time);
	s=s+"s";
	CDC *pDC=GetDC();
	pDC->TextOut(190,5,s);
	ReleaseDC(pDC);

	m_time=m_time+0.05f;
}

void CMyView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	int i,j;
	switch(nChar)
	{/*
	case VK_NUMPAD1:
		{
			gamemain(10,270);
			break;
		}
	case VK_NUMPAD2:
		{
			gamemain(110,270);
			break;
		}
	case VK_NUMPAD3:
		{
			gamemain(210,270);
			break;
		}
	case VK_NUMPAD4:
		{
			gamemain(310,270);
			break;
		}
	case 'Q':
		{
			gamemain(10,270);
			break;
		}
	case 'W':
		{
			gamemain(110,270);
			break;
		}
	case 'E':
		{
			gamemain(210,270);
			break;
		}
	case 'R':
		{
			gamemain(310,270);
			break;
		}
	case 'G':
		{
			m_count=40;
			break;
		}*/
////////////////////////////////////////////////////////////
	case 'A':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="a"||Key[i].name=="A")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'B':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="b"||Key[i].name=="B")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'C':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="c"||Key[i].name=="C")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'D':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="d"||Key[i].name=="D")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'E':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="e"||Key[i].name=="E")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'F':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="f"||Key[i].name=="F")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'G':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="g"||Key[i].name=="G")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'H':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="h"||Key[i].name=="H")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'I':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="i"||Key[i].name=="I")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'J':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="j"||Key[i].name=="J")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'K':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="k"||Key[i].name=="K")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'L':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="l"||Key[i].name=="L")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'M':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="m"||Key[i].name=="M")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'N':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="n"||Key[i].name=="N")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'O':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="o"||Key[i].name=="O")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'P':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="p"||Key[i].name=="P")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'Q':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="q"||Key[i].name=="Q")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'R':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="r"||Key[i].name=="R")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'S':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="s"||Key[i].name=="S")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'T':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="t"||Key[i].name=="T")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'U':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="u"||Key[i].name=="U")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
				break;
		}
	case 'V':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="v"||Key[i].name=="V")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'W':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="w"||Key[i].name=="W")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'X':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="x"||Key[i].name=="X")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'Y':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="y"||Key[i].name=="Y")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case 'Z':
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="z"||Key[i].name=="Z")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD0:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="0")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD1:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="1")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD2:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="2")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD3:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="3")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD4:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="4")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD5:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="5")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD6:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="6")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD7:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="7")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD8:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="8")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	case VK_NUMPAD9:
		{
			for(i=0;i<4;i++)
				if(Key[i].name=="9")
				{
					switch(Key[i].flag)
					{
					case 1:gamemain(10,270);break;
					case 2:gamemain(110,270);break;
					case 3:gamemain(210,270);break;
					case 4:gamemain(310,270);break;
					}
				}
			break;
		}
	}
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyView::OnRetry() 
{
	// TODO: Add your command handler code here
	initwindow();
	initdata();
	paintpicture();
}

void CMyView::OnExit() 
{
	// TODO: Add your command handler code here
	exit(0);
}

void CMyView::keydefault()
{
	Key[0].name="q";
	Key[0].flag=1;
	Key[1].name="w";
	Key[1].flag=2;
	Key[2].name="e";
	Key[2].flag=3;
	Key[3].name="r";
	Key[3].flag=4;
}

void CMyView::OnSetkey() 
{
	// TODO: Add your command handler code here
	CKeyDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		Key[0].name=dlg.m_1;
		Key[1].name=dlg.m_2;
		Key[2].name=dlg.m_3;
		Key[3].name=dlg.m_4;
	}
}

void CMyView::errorblockshan(int ii,int jj)
{
	int i=0;
	for (i=0;i<10;i++)
	{
		Web[ii][jj].flag = (i%2);
		paintpicture();
		Sleep(60);
	}
	
	Sleep(200);
	
	
}
void CMyView::cleanwindow(CDC *pDC)
{
	CRect rt;
	pDC->GetClipBox(&rt);
	if (rand()%2==0)
	{
		CBrush brush=RGB(255,255,255);
		pDC->SelectObject(&brush);
		pDC->Rectangle(0,0,400,520);
	}
	else
	{
		CBrush brush=RGB(0,0,0);
		pDC->SelectObject(&brush);
		pDC->Rectangle(0,0,400,520);
	}
	

	

}
