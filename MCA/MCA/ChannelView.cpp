// ChannelView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "ChannelView.h"


// CChannelView

IMPLEMENT_DYNCREATE(CChannelView, CView)

CChannelView::CChannelView()
{

}

CChannelView::~CChannelView()
{
}

BEGIN_MESSAGE_MAP(CChannelView, CView)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CChannelView 绘图

void CChannelView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	CPaintDC dc(this);
	//画背景颜色 
	CRect rect; 
	GetClientRect(&rect); 
	
	
	dc.FillSolidRect(0,0,200,20,RGB(255,0,0)); //紫色背景
	//CDC *pDC = GetDC();
	CString strText; 
	for(int i =0;i<17;i++){
	strText.Format(_T("%3d "), 64*i); 
		//CDC  * pDC = GetDC();
	pDC->TextOutW(64*i,0,strText);
	}
	//dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,121,100)); //紫色背景
	// TODO: 在此添加绘制代码
}


// CChannelView 诊断

#ifdef _DEBUG
void CChannelView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CChannelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChannelView 消息处理程序


void CChannelView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC *pDC = GetDC();
	//画背景颜色 
	CRect rect; 
	GetClientRect(&rect); 
	
	
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(178,105,135)); //紫色背景
	//CDC *pDC = GetDC();
	CString strText; 
	for(int i =0;i<17;i++){
	strText.Format(_T("%3d "), 64*i); 
		//CDC  * pDC = GetDC();
	pDC->TextOutW(64*i-2,0,strText);
	}
	//dc.FillSolidRect(0,0,rect.Width(),rect
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CView::OnPaint()
}
