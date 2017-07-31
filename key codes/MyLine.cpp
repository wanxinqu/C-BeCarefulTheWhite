// MyLine.cpp: implementation of the MyLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "��Ȱ׿�.h"
#include "MyLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyLine::MyLine()
{

}

MyLine::~MyLine()
{

}


void MyLine::InitLine(POINTS* pt)
{
	for (int i=0;i<4;i++)
	{
		start[i] = pt[i];
		end[i] = start[i];
		end[i].x = start[i].x + 400;
	}
	for (i=4;i<7;i++)
	{
		start[i].x = end[i].x = 100*(i-3);
		start[i].y = 0;
		end[i].y = 520;
	}
}


void MyLine::PaintLine(CDC *pDC)
{
	CPen pen1;
	CPen *oldPen;
	pen1.CreatePen(PS_SOLID,2,RGB(0,0,0));//��������
	oldPen = pDC->SelectObject(&pen1);//������ѡ���豸������������ɵĻ���
	for (int i=0;i<7;i++)
	{
		pDC->MoveTo(start[i].x,start[i].y);//�������
		pDC->LineTo(end[i].x,end[i].y);//�ߵ��յ�
	}
	
	pDC->SelectObject(oldPen);//����ǰ�Ļ���ѡ���豸������


//	ReleaseDC(pDC);
}