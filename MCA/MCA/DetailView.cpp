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
void CDetailView::DrawAxis(CDC &MemDC, LPTSTR TitleForX, LPTSTR TitleForY)
{
    //选择画坐标轴的画笔
    CPen PenForDrawAxis(PS_SOLID, 1, RGB(255,251,13));
    MemDC.SelectObject(PenForDrawAxis);
 
    //绘制X轴
    MemDC.MoveTo(60, 220);
    MemDC.LineTo(520, 220);
    //绘制箭头
    MemDC.LineTo(510, 223);
    MemDC.LineTo(510, 217);
    MemDC.LineTo(520, 220);
 
    //绘制Y轴
    MemDC.MoveTo(60, 220);
    MemDC.LineTo(60, 30);
    //绘制箭头
    MemDC.LineTo(57, 40);
    MemDC.LineTo(63, 40);
    MemDC.LineTo(60, 30);
 
    //设置文本的颜色
    COLORREF OldColor = MemDC.SetTextColor(RGB(255, 255, 0));
 
    //绘制标注
    MemDC.TextOut(480, 230, TitleForX);
    MemDC.TextOut(40, 10, TitleForY);
 
    //还原文本颜色
    MemDC.SetTextColor(OldColor);
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
	CRect rect; 
	GetClientRect(&rect); 
    CDC *pDC = GetDC();
	CDC MemDC;
    MemDC.CreateCompatibleDC(NULL); 
    CBitmap MemBitmap;
    MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(),rect.Height());
	MemDC.SelectObject(&MemBitmap); 

	//画背景颜色 
	
	MemDC.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(85,85,85));
	//DrawAxis(MemDC, _T("time(s)"), _T("length(kbit)"));

	
	//dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(85,85,85)); //紫色背景
	
	
	
	//设置曲线颜色 
	CPen pen;
	
	CPen* oldpen = MemDC.SelectObject(&pen);
	//画曲线 
	DrawAxis(MemDC, _T("time(s)"), _T("length(kbit)"));
	pen.CreatePen(PS_SOLID,2,RGB(255,251,13));
	MemDC.MoveTo(1,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[0]);
	for (int i=0;i<512;i++)
	{ 
		MemDC.LineTo(i+1,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[i]); } 
	//释放资源 
	if(((CMCADoc*)m_pDocument)->lbtn_beg<Cursor_Pos){
		MemDC.FillSolidRect(((CMCADoc*)m_pDocument)->lbtn_beg,0,Cursor_Pos-((CMCADoc*)m_pDocument)->lbtn_beg,rect.Height(),RGB(0,255,255));}
	pDC->BitBlt(0, 0,rect.Width(),rect.Height(), &MemDC, 0, 0, SRCCOPY); 

	MemDC.SelectObject(oldpen); 
	pen.DeleteObject();
	ReleaseDC(pDC);

	
	

}

void CDetailView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序;代码和/或调用默认值
	Cursor_Pos = ((CMCADoc*)m_pDocument)->lbtn_beg;
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
	
		
	((CMCADoc*)m_pDocument) ->cha = point.x;
	
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
	pen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	CPen* oldpen = pDC->SelectObject(&pen);	   

	CRect rect;
	GetClientRect(&rect);
	
    //pDC->SetROP2(R2_XORPEN);   //擦除
   // pDC->MoveTo(m_nSel,0);
    //pDC->LineTo(m_nSel,rect.Height());

    pDC->MoveTo(nX,0);         //绘制光标
    pDC->LineTo(nX,rect.Height());

    m_nSel = nX;
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	}
	
		 
	
	CView::OnMouseMove(nFlags, point);

}
