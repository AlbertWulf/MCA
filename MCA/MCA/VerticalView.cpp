// VerticalView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "VerticalView.h"
#include "MCADoc.h"

// CVerticalView

IMPLEMENT_DYNCREATE(CVerticalView, CView)

CVerticalView::CVerticalView()
{

}

CVerticalView::~CVerticalView()
{
}

BEGIN_MESSAGE_MAP(CVerticalView, CView)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CVerticalView 绘图

void CVerticalView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	CPaintDC dc(this);
	//画背景颜色 
	CRect rect; 
	GetClientRect(&rect); 
	
	
	dc.FillSolidRect(0,0,20,20,RGB(0,255,0)); //紫色背景
	//CDC *pDC = GetDC();
	CString strText; 
	for(int i =0;i<17;i++){
	strText.Format(_T("%3d "), 64*i); 
		//CDC  * pDC = GetDC();
	pDC->TextOutW(0,i*20,strText);
	}
	//dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,121,100)); //紫色背景
	// TODO: 在此添加绘制代码
}


// CVerticalView 诊断

#ifdef _DEBUG
void CVerticalView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CVerticalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVerticalView 消息处理程序


void CVerticalView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC *pDC = GetDC();
	//画背景颜色 
	CRect rect; 
	GetClientRect(&rect); 
	
	
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(178,105,135)); //紫色背景
	//CDC *pDC = GetDC();
	CString strText; 
	for(int i =0;i<6;i++){
	strText.Format(_T("%3d "), 50*i*((CMCADoc*)m_pDocument)->mult); 
		//CDC  * pDC = GetDC();
	pDC->TextOutW(0,rect.Height()-i*50-58,strText);
	}
}
