// TotalView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "TotalView.h"


// CTotalView

IMPLEMENT_DYNCREATE(CTotalView, CView)

CTotalView::CTotalView()
{

}

CTotalView::~CTotalView()
{
}

BEGIN_MESSAGE_MAP(CTotalView, CView)
END_MESSAGE_MAP()


// CTotalView 绘图

void CTotalView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CTotalView 诊断

#ifdef _DEBUG
void CTotalView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CTotalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTotalView 消息处理程序
