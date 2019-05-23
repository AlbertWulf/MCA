// DetailView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "DetailView.h"
#include "MCADOc.h"


// CDetailView

IMPLEMENT_DYNCREATE(CDetailView, CView)

CDetailView::CDetailView()
{

}

CDetailView::~CDetailView()
{
}

BEGIN_MESSAGE_MAP(CDetailView, CView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()


// CDetailView 绘图

void CDetailView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CDetailView 诊断

#ifdef _DEBUG
void CDetailView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDetailView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDetailView 消息处理程序


void CDetailView::OnPaint()
{
	CPaintDC dc(this);
	//画背景颜色 
	CRect rect; 
	GetClientRect(&rect); 
	
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(139,35,134)); //紫色背景
	
	
	
	//设置曲线颜色 
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen* oldpen = dc.SelectObject(&pen);
	//画曲线 
	dc.MoveTo(1,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[0]);
	for (int i=0;i<512;i++)
	{ 
		dc.LineTo(i+1,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[i]); } 
	//释放资源 
	dc.SelectObject(oldpen); 
	pen.DeleteObject();

}

void CDetailView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序;代码和/或调用默认值
	m_RBMouseClick = TRUE;
	CView::OnRButtonDblClk(nFlags, point);
}

void CDetailView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	((CMCADoc*)m_pDocument) ->lbtn_beg = point.x;
	m_bMouseDown = TRUE;
	CView::OnLButtonDown(nFlags, point);
}


void CDetailView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	((CMCADoc*)m_pDocument) ->lbtn_end = point.x;
	
	m_bMouseDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void CDetailView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC  * pDC = GetDC();
	
		
		
	
	if (m_bMouseDown) 
	{   
		sumroi++;
		Cursor_Pos = point.x;
		int nX = point.x; 
		int nY = ((CMCADoc*)m_pDocument) -> m_Dot[nX];
		CString strText; 
		strText.Format(_T("道址%3d幅值%2d "), nX, nY); 
		//CDC  * pDC = GetDC();
		pDC->TextOutW(10,80,strText);
		CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen* oldpen = pDC->SelectObject(&pen);	   

	CRect rect;
	GetClientRect(&rect);
	
    //pDC->SetROP2(R2_XORPEN);   //擦除
    pDC->MoveTo(m_nSel,0);
    pDC->LineTo(m_nSel,rect.Height());

    pDC->MoveTo(nX,0);         //绘制光标
    pDC->LineTo(nX,rect.Height());

    m_nSel = nX;
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	}
	
		 
	
	CView::OnMouseMove(nFlags, point);

}
