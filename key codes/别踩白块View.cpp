// ��Ȱ׿�View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "��Ȱ׿�.h"

#include "��Ȱ׿�Doc.h"
#include "��Ȱ׿�View.h"
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
	int x;     // ����x������
	int y;     // ����y������
	int flag;  // ��ɫ��־;0��ʾ�ס�1��ʾ�ڡ�2��ʾ�ҡ�3��ʾ�ơ�4��ʾ�̡�5��ʾ��ʼ
	int lock;  // ������־��0��ʾ������1��ʾ������ֻ������һ���ĺ�ɫ��������ɹ��󣬲��ܽ�����һ�εĺ�ɫ����
}Web[5][4];



struct key
{
	CString name;  // ����������
	int flag;      // ��Ӧ��������1��2��3��4�ֱ��Ӧһ��������������
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

		
		for (i=0;i<5;i++)   //�ع�����
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

					if (p->m_count%10==0) //�������
					{
						CDC* pDC = p->GetDC();

						p->cleanwindow(pDC);
						Sleep(200);

						p->cleanwindow(pDC);
						Sleep(200);

						p->cleanwindow(pDC);
						Sleep(200);
						
					}
					
					if (Web[i][m].flag==0&&lucky==0)//�ڹ�
					{
						Web[i][m].flag=10;
					}
					else if (Web[i][m].flag==0&&lucky==3)//���
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
				//�ڹ� �������
		
			}		
		}
       
		
		for (i=0;i<5;i++)   //�ڿ鵽�׵�û�� �������
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

	AfxGetApp()->m_pMainWnd->SetWindowPos(NULL,400,100,420,582,NULL);     // �������ڴ�С
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

	CDC *pDC=GetDC();//CDC�Ǹ�ɶ��
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
	for(i=0;i<5;i++)                 // ��
	{
		for(j=0;j<4;j++)             // ��
		{
			if (4==i)
			{
				Web[i][j].x=100*j;       // ����ĺ�����
				Web[i][j].y=-130;       // �����������
				Web[i][j].flag=0;        // ���з���ȫΪ��ɫ
				Web[i][j].lock=0;
			}
			else
			{
				Web[i][j].x=100*j;       // ����ĺ�����
				Web[i][j].y=130*i;       // �����������
				Web[i][j].flag=0;        // ���з���ȫΪ��ɫ
				Web[i][j].lock=0;        // ���з���ȫΪ����״̬
			
			}
			if(3==i)                 // �����з���ȫΪ��ɫ
			{
				Web[i][j].flag=3;
				Web[i][j].lock=0;
			}
			
		}
		if(3!=i)                     // Ϊÿһ���������һ����ɫ����λ��
		{
			x=rand()%4;
			Web[i][x].flag=1;
			if(2==i)
				Web[i][x].flag=5;	//��ʼ
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
	if (ChoosePage==0)  //ҳ��1
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
		int i,j,x,y,f;  //f������ɫ
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
			
			//Ӧ��д��Line������
			///////////////////////////////////////
			CommonPoint commonpoint;
			MyPoint* mypoint = &commonpoint;
			mypoint->InitPoint();
			/////////////////////////////////////////////

			if (point.y>100&&point.y<=180)			//����ģʽ 25
			{//�ҵ����λ�ö�Ӧ��ģʽ�� ���ñ��� Ȼ�������Ϸ���棨else��
				abfactory->SI.setblocknum(25);
				abfactory->SI.texiao = false;
				abfactory->SI.zhangai = false;

				classics_max_count = abfactory->SI.getblocknum();
			}
			else if(point.y>180) //����ģʽ 50��
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
		else if (point.x<200&&point.y>260) //��ģʽ
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

		else if (point.x>200&&point.y<=260)  //�ֻ�ģʽ
		{
			StreetModel street;
			AbstractFactory* abfactory = &street;
			if (point.y>100&&point.y<=180)			//����ģʽ 25
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

		else if (point.x>200&&point.y>260)    //����
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
				AfxMessageBox("�����ϷΨһ��һ������,����ֻ��Ҫ���ϲ��ź�ɫ����ǰ������,�ܼ򵥰�?������ս������!��Ϸ������ģʽ:����ģʽ,�������ٶȵ����յ�;�ֻ�ģʽ,���������ö��ٷ־͵ö��ٷ�,û���κ�����,��Ҳ�������ս�Ե�һ��ģʽ;��ģʽ,�ڹ涨ʱ�������ڿ������߼���");

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
		gamemain(point.x,point.y);   //ˢ��һ��ҳ��
		
		CFormView::OnLButtonDown(nFlags, point);
	}
}
/*
void CMyView::startweb(int x,int y)
{
/*	int i,j;
	for(i=3;i>0;i--)                                    // ����������һ��;���һ����ʧ����һ�г��ָ��£�����������ɫ�����λ�ã�������һ�����ƣ����Ա��ֲ���
	{
		for(j=0;j<4;j++)
		{
			Web[i][j].flag=Web[i-1][j].flag;
			Web[i][j].lock=Web[i-1][j].lock;
		}
	}
	for(j=0;j<4;j++)                                    // �����µ�һ��
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
		for(i=0;i<4;i++)             // ��ȡ������ķ����λ�� ����m��n
		{
			for(j=0;j<4;j++)
			{
				if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))
				{
					m=i;
					n=j;
				}
			}
			//		if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))    �д���	
		}
		i=m;
		j=n;  //���ݵ��λ�ò�ͬ�ֱ���
		if(5==Web[i][j].flag)       // ���е��ǿ�ʼ����
		{
			SetTimer(1,50,NULL);
			startweb(i,j);
		}
		else if(1==Web[i][j].flag)  // ���е��Ǻ�ɫ����
		{
			blackweb(i,j);

		}
		else if(0==Web[i][j].flag)  // ���е��ǰ�ɫ���� 
		{
			KillTimer(1);
			whiteweb(0,0);
		}
		gameover();                 // �ж���Ϸ����
		paintpicture();             // �ػ���Ϸ����
		m_time = m_time-0.05;
		counttime();                // ��ʾ���һ�ε�ʱ��

	}

	else if (model==2&&LockThread==0)			//���߳�
	{
		
		Thread = CreateThread(0,0,ThreadProc,(LPVOID)this,0,&ThreadID);
		LockThread = 1;
		m_count++;
	}
	else if (model==2&&LockThread==1)
	{	
		int i,j,m,n;
		for(i=0;i<5;i++)             // ��ȡ������ķ����λ�� ����m��n
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
		j=n;  //���ݵ��λ�ò�ͬ�ֱ���
		if(5==Web[i][j].flag)       // ���е��ǿ�ʼ����
		{
			startweb(i,j);
		}

		else if(1==Web[i][j].flag)  // ���е��Ǻ�ɫ����
		{
			blackweb(i,j);
			
		}
		else if(0==Web[i][j].flag)  // ���е��ǰ�ɫ���� 
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

		gameover();                 // �ж���Ϸ����
		
	}

	else if (model==3)
	{
		int i,j,m,n;
		for(i=0;i<4;i++)             // ��ȡ������ķ����λ�� ����m��n
		{
			for(j=0;j<4;j++)
			{
				if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))
				{
					m=i;
					n=j;
				}
			}
			//		if((Web[i][j].x<x&&x<Web[i][j].x+100)&&(Web[i][j].y<y&&y<Web[i][j].y+130))    �д���	
		}
		i=m;
		j=n;  //���ݵ��λ�ò�ͬ�ֱ���
		if(5==Web[i][j].flag)       // ���е��ǿ�ʼ����
		{
			SetTimer(1,50,NULL);
			startweb(i,j);
		}
		else if(1==Web[i][j].flag)  // ���е��Ǻ�ɫ����
		{
			blackweb(i,j);
			
		}
		else if(0==Web[i][j].flag)  // ���е��ǰ�ɫ���� 
		{
			KillTimer(1);
			whiteweb(0,0);
		}
		gameover();                 // �ж���Ϸ����
		paintpicture();             // �ػ���Ϸ����
		m_time = m_time-0.05;
		counttime();                // ��ʾ���һ�ε�ʱ��

	}
	
}

void CMyView::startweb(int ii,int jj)
{
	switch(model)
	{
	case 1:
		{
			m_count++;
			Web[ii][jj].flag=2;         // ����ɫ�����ɻ�ɫ
			Web[ii][jj].lock=1;         // ���������
			int i,j,x;
			for(i=3;i>0;i--)            // ����������һ��;���һ����ʧ����һ�г��ָ��£�����������ɫ�����λ�ã�������һ�����ƣ����Ա��ֲ���
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=Web[i-1][j].flag;
					Web[i][j].lock=Web[i-1][j].lock;
				}
			}
			for(j=0;j<4;j++)            // ������һ�� 
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
			Web[ii][jj].flag=2;         // ����ɫ�����ɻ�ɫ
			break;
			
		}
	case 3:
		{
			m_count++;
			Web[ii][jj].flag=2;         // ����ɫ�����ɻ�ɫ
			Web[ii][jj].lock=1;         // ���������
			int i,j,x;
			for(i=3;i>0;i--)            // ����������һ��;���һ����ʧ����һ�г��ָ��£�����������ɫ�����λ�ã�������һ�����ƣ����Ա��ֲ���
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=Web[i-1][j].flag;
					Web[i][j].lock=Web[i-1][j].lock;
				}
			}
			for(j=0;j<4;j++)            // ������һ�� 
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
			if(2!=Web[(ii)+1][j].flag)  // ֻ����һ�еĺ�ɫ����(�������ɻ�ɫ��)��������ܵ����һ��
				n++;
			if(4==n)
				return;
			m_count++;
			Web[ii][jj].flag=2;                                 // ��ɫ�����ɻ�ɫ
			Web[ii][jj].lock=1;                                 // ����ɫ�������
			for(i=3;i>0;i--)                                    // ����������һ��;���һ����ʧ����һ�г��ָ��£�����������ɫ�����λ�ã�������һ�����ƣ����Ա��ֲ���
			{
				for(j=0;j<4;j++)
				{
					Web[i][j].flag=Web[i-1][j].flag;
					Web[i][j].lock=Web[i-1][j].lock;
				}
			}
			for(j=0;j<4;j++)                                    // �����µ�һ��
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
			Web[ii][jj].flag=2;         // ����ɫ�����ɻ�ɫ
			
			break;
		}
	case 3:
		{
			int i,j,x,n=0;
			for(j=0;j<4;j++)
				if(2!=Web[(ii)+1][j].flag)  // ֻ����һ�еĺ�ɫ����(�������ɻ�ɫ��)��������ܵ����һ��
					n++;
				if(4==n)
					return;
				m_count++;
				Web[ii][jj].flag=2;                                 // ��ɫ�����ɻ�ɫ
				Web[ii][jj].lock=1;                                 // ����ɫ�������
				for(i=3;i>0;i--)                                    // ����������һ��;���һ����ʧ����һ�г��ָ��£�����������ɫ�����λ�ã�������һ�����ƣ����Ա��ֲ���
				{
					for(j=0;j<4;j++)
					{
						Web[i][j].flag=Web[i-1][j].flag;
						Web[i][j].lock=Web[i-1][j].lock;
					}
				}
				for(j=0;j<4;j++)                                    // �����µ�һ��
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
			if(classics_max_count-2<=m_count)         // ��Ϸ׼������������ɫ����
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
				AfxMessageBox("��ϲ��!\n˳�������Ϸ!\n��ʱ:"+s+"��");
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
				AfxMessageBox("��ϲ��!\n�涨ʱ��������"+s+"��");

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
			AfxMessageBox("��Ϸ����!!\n���ź�~~\n��������!");
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
			
			AfxMessageBox("��Ϸ����!!\n�㹲�߹���"+s+"��!");
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
			AfxMessageBox("��Ϸ����!!\n���ź�~~\n��������!");
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
